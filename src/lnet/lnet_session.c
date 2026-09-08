/*
 * LAN link conduit - session implementation.
 *
 * Wire format: every message is 3 bytes: [u8 kind][u16 value (big-endian)].
 *   kind 0x10 = HELLO carrying the sender's role (0 host / 1 client)
 *   kind 0x20 = SLOT carrying one 16-bit slot value
 */
#include "lnet_session.h"

#include <stdlib.h>
#include <string.h>

#define MSG_HELLO 0x10
#define MSG_SLOT  0x20

/* Non-blocking handshake phases. The HELLO exchange is driven a few bytes at a
 * time from poll(): the peer is allowed to connect but then send nothing (a
 * stale/semidead connection), and the game loop must never block on it. */
#define HS_STEP_FIRST  1 /* host: send host HELLO; client: recv peer HELLO */
#define HS_STEP_SECOND 2 /* host: recv client HELLO; client: send own HELLO */

struct LNetSession
{
    LNetSock *sock;
    LNetSock *listener; /* host: still-listening accept socket while connecting */
    LNetSock *pending;  /* client: in-progress nonblocking connect socket */
    LNetRole role;
    int alive;
    int connecting; /* 1 while host accept / client connect not yet completed */
    int helloDone;  /* HELLO role handshake finished */
    char host[128];  /* client: connect target */
    unsigned short port;
    /* non-blocking HELLO handshake progress */
    int hsStep;
    unsigned char hsOut[3];
    int hsOutSent;
    unsigned char hsIn[3];
    int hsInGot;
    /* non-blocking SLOT exchange progress (partial send/recv of one 3-byte slot) */
    unsigned char slotOut[3];
    int slotOutSent;
    unsigned char slotIn[3];
    int slotInGot;
};

/* Send our HELLO message without blocking. Returns 1 once all 3 bytes are
 * written, 0 while still writing (poll again), -1 on a permanent error. */
static int hs_send_hello(LNetSession *s, LNetRole role, int *err)
{
    size_t adv = 0;
    int r;

    if (s->hsOutSent == 0)
    {
        s->hsOut[0] = MSG_HELLO;
        s->hsOut[1] = 0;
        s->hsOut[2] = (unsigned char)role;
    }
    r = lnet_net_send_nb(s->sock, s->hsOut + s->hsOutSent,
                         sizeof(s->hsOut) - (size_t)s->hsOutSent, &adv, err);
    if (r < 0)
        return -1;
    if (r == 0 || adv == 0)
    {
        if (err)
            *err = LNET_ERR_AGAIN;
        return 0;
    }
    s->hsOutSent += (int)adv;
    if (s->hsOutSent < (int)sizeof(s->hsOut))
    {
        if (err)
            *err = LNET_ERR_AGAIN;
        return 0;
    }
    return 1;
}

/* Receive the peer's HELLO message without blocking. Returns 1 once all 3 bytes
 * are validated, 0 while still waiting (poll again), -1 on an error or a peer
 * that failed the role check. */
static int hs_recv_hello(LNetSession *s, LNetRole wantPeer, int *err)
{
    size_t adv = 0;
    int r;

    r = lnet_net_recv_nb(s->sock, s->hsIn + s->hsInGot,
                         sizeof(s->hsIn) - (size_t)s->hsInGot, &adv, err);
    if (r < 0)
        return -1;
    if (r == 0 || adv == 0)
    {
        if (err)
            *err = LNET_ERR_AGAIN;
        return 0;
    }
    s->hsInGot += (int)adv;
    if (s->hsInGot < (int)sizeof(s->hsIn))
    {
        if (err)
            *err = LNET_ERR_AGAIN;
        return 0;
    }
    if (s->hsIn[0] != MSG_HELLO || s->hsIn[2] != (unsigned char)wantPeer)
    {
        if (err)
            *err = LNET_ERR_RECV;
        return -1;
    }
    return 1;
}

LNetSession *lnet_session_host(unsigned short port, int *err)
{
    LNetSock *listener;
    LNetSession *s;

    if (err)
        *err = LNET_ERR_OK;
    listener = lnet_net_listen(port, err);
    if (listener == NULL)
        return NULL;

    s = (LNetSession *)calloc(1, sizeof(LNetSession));
    s->listener = listener;
    s->role = LNET_ROLE_HOST;
    s->alive = 1;
    s->connecting = 1;
    return s;
}

LNetSession *lnet_session_join(const char *host, unsigned short port, int *err)
{
    LNetSession *s;

    if (err)
        *err = LNET_ERR_OK;
    s = (LNetSession *)calloc(1, sizeof(LNetSession));
    s->role = LNET_ROLE_CLIENT;
    s->alive = 1;
    s->connecting = 1;
    (void)strncpy(s->host, host, sizeof(s->host) - 1);
    s->host[sizeof(s->host) - 1] = '\0';
    s->port = port;
    return s;
}

/* Drive connection establishment for a pending session. Returns 1 when the
 * HELLO handshake is complete (the session is ready for exchange), 0 while
 * still connecting (poll again later), or -1 on a permanent error. */
int lnet_session_poll(LNetSession *s, int *err)
{
    LNetSock *conn = NULL;
    int r;

    if (s == NULL)
        return -1;
    if (!s->alive)
        return -1;
    if (s->helloDone)
        return 1;
    if (err)
        *err = LNET_ERR_OK;

    /* 1) Connection phase: host accept / client connect. */
    if (s->sock == NULL)
    {
        if (s->role == LNET_ROLE_HOST)
        {
            if (s->listener == NULL)
                return -1;
            conn = lnet_net_accept_nb(s->listener, err);
            if (conn == NULL)
            {
                if (err && *err == LNET_ERR_AGAIN)
                    return 0; /* keep waiting for a client */
                return -1;
            }
            (void)lnet_net_close(s->listener);
            s->listener = NULL;
            s->sock = conn;
            s->hsStep = HS_STEP_FIRST;
            s->hsOutSent = 0;
            s->hsInGot = 0;
        }
        else
        {
            conn = lnet_net_connect_nb(s->host, s->port, &s->pending, err);
            if (conn == NULL)
            {
                if (err && *err == LNET_ERR_AGAIN)
                    return 0; /* connect still in progress */
                return -1;
            }
            s->pending = NULL;
            s->sock = conn;
            s->hsStep = HS_STEP_FIRST;
            s->hsOutSent = 0;
            s->hsInGot = 0;
        }
    }

    /* 2) Non-blocking HELLO handshake. Each step only makes progress when data
     * is actually ready, so a peer that connects but never answers cannot hang
     * the game loop. */
    if (s->hsStep == HS_STEP_FIRST)
    {
        if (s->role == LNET_ROLE_HOST)
            r = hs_send_hello(s, LNET_ROLE_HOST, err);
        else
            r = hs_recv_hello(s, LNET_ROLE_HOST, err);
        if (r <= 0)
            return r;
        s->hsStep = HS_STEP_SECOND;
    }
    if (s->hsStep == HS_STEP_SECOND)
    {
        if (s->role == LNET_ROLE_HOST)
            r = hs_recv_hello(s, LNET_ROLE_CLIENT, err);
        else
            r = hs_send_hello(s, LNET_ROLE_CLIENT, err);
        if (r <= 0)
            return r;
    }

    s->helloDone = 1;
    s->connecting = 0;
    return 1;
}

void lnet_session_close(LNetSession *s)
{
    if (s == NULL)
        return;
    s->alive = 0;
    lnet_net_close(s->sock);
    if (s->listener != NULL)
        lnet_net_close(s->listener);
    if (s->pending != NULL)
        lnet_net_close(s->pending);
    free(s);
}

LNetRole lnet_session_role(const LNetSession *s)
{
    return s->role;
}

int lnet_session_is_ready(const LNetSession *s)
{
    return s != NULL && s->helloDone && s->sock != NULL;
}

/*
 * Exchange one SIO slot value with the peer non-blockingly. Each call does at
 * most one select()-gated send and one select()-gated recv, so it never blocks
 * the game loop waiting for a slow peer. Partial I/O for the in-flight slot is
 * buffered across calls and resumed the next time exchange() is invoked.
 * Returns 1 when a full slot was exchanged (*peerVal is valid), 0 while the
 * slot is still in progress (call again later), and -1 on a permanent error or
 * a peer that closed - in which case the session is marked dead.
 */
int lnet_session_exchange(LNetSession *s, unsigned short myVal, unsigned short *peerVal)
{
    size_t adv;
    int err;
    int r;

    if (s == NULL || s->sock == NULL)
        return -1;
    if (s->slotOutSent == 0)
    {
        s->slotOut[0] = MSG_SLOT;
        s->slotOut[1] = (unsigned char)(myVal >> 8);
        s->slotOut[2] = (unsigned char)(myVal & 0xFF);
    }

    /* Send our slot first, resuming any partial send from a prior frame. */
    if (s->slotOutSent < 3)
    {
        r = lnet_net_send_nb(s->sock, s->slotOut + s->slotOutSent,
                             3 - s->slotOutSent, &adv, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        if (r == 0)
            return 0; /* peer not consuming yet; still alive, retry later */
        s->slotOutSent += (int)adv;
        if (s->slotOutSent < 3)
            return 0; /* partial send buffered, resume later */
    }

    /* Then read the peer's slot, resuming any partial recv. */
    if (s->slotInGot < 3)
    {
        r = lnet_net_recv_nb(s->sock, s->slotIn + s->slotInGot,
                             3 - s->slotInGot, &adv, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        if (r == 0)
            return 0; /* peer's slot not arrived yet; retry later */
        s->slotInGot += (int)adv;
        if (s->slotInGot < 3)
            return 0; /* partial recv buffered, resume later */
    }

    if (s->slotIn[0] != MSG_SLOT)
    {
        s->alive = 0;
        return -1;
    }
    if (peerVal)
        *peerVal = (unsigned short)(((unsigned short)s->slotIn[1] << 8) | s->slotIn[2]);
    s->slotOutSent = 0;
    s->slotInGot = 0;
    return 1;
}