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

struct LNetSession
{
    LNetSock *sock;
    LNetRole role;
    int alive;
};

static int write_hello(LNetSock *s, LNetRole role)
{
    unsigned char b[3];
    b[0] = MSG_HELLO;
    b[1] = 0;
    b[2] = (unsigned char)role;
    return lnet_net_send_all(s, b, sizeof(b), NULL);
}

static int read_hello(LNetSock *s, LNetRole *role)
{
    unsigned char b[3];
    int err;
    if (!lnet_net_recv_all(s, b, sizeof(b), &err))
        return 0;
    if (b[0] != MSG_HELLO)
        return -1;
    *role = (LNetRole)b[2];
    return 1;
}

LNetSession *lnet_session_host(unsigned short port, int *err)
{
    LNetSock *listener;
    LNetSock *conn;
    LNetSession *s;
    LNetRole peerRole;

    if (err)
        *err = LNET_ERR_OK;
    listener = lnet_net_listen(port, err);
    if (listener == NULL)
        return NULL;
    conn = lnet_net_accept(listener, err);
    lnet_net_close(listener);
    if (conn == NULL)
        return NULL;

    s = (LNetSession *)calloc(1, sizeof(LNetSession));
    s->sock = conn;
    s->role = LNET_ROLE_HOST;

    /* Host sends its role first, then confirms the peer is a client. */
    if (!write_hello(conn, LNET_ROLE_HOST))
    {
        lnet_session_close(s);
        if (err)
            *err = LNET_ERR_SEND;
        return NULL;
    }
    if (read_hello(conn, &peerRole) != 1 || peerRole != LNET_ROLE_CLIENT)
    {
        lnet_session_close(s);
        if (err)
            *err = LNET_ERR_RECV;
        return NULL;
    }
    return s;
}

LNetSession *lnet_session_join(const char *host, unsigned short port, int *err)
{
    LNetSock *conn;
    LNetSession *s;
    LNetRole peerRole;

    if (err)
        *err = LNET_ERR_OK;
    conn = lnet_net_connect(host, port, err);
    if (conn == NULL)
        return NULL;

    s = (LNetSession *)calloc(1, sizeof(LNetSession));
    s->sock = conn;
    s->role = LNET_ROLE_CLIENT;

    /* Client waits for the host HELLO, then sends its own. */
    if (read_hello(conn, &peerRole) != 1 || peerRole != LNET_ROLE_HOST)
    {
        lnet_session_close(s);
        if (err)
            *err = LNET_ERR_RECV;
        return NULL;
    }
    if (!write_hello(conn, LNET_ROLE_CLIENT))
    {
        lnet_session_close(s);
        if (err)
            *err = LNET_ERR_SEND;
        return NULL;
    }
    return s;
}

void lnet_session_close(LNetSession *s)
{
    if (s == NULL)
        return;
    s->alive = 0;
    lnet_net_close(s->sock);
    free(s);
}

LNetRole lnet_session_role(const LNetSession *s)
{
    return s->role;
}

int lnet_session_exchange(LNetSession *s, unsigned short myVal, unsigned short *peerVal)
{
    unsigned char out[3];
    unsigned char in[3];
    int err;

    out[0] = MSG_SLOT;
    out[1] = (unsigned char)(myVal >> 8);
    out[2] = (unsigned char)(myVal & 0xFF);

    /* Send first, then receive: TCP is full-duplex so this cannot deadlock. */
    if (!lnet_net_send_all(s->sock, out, sizeof(out), &err))
    {
        s->alive = 0;
        return 0;
    }
    if (!lnet_net_recv_all(s->sock, in, sizeof(in), &err))
    {
        s->alive = 0;
        return 0;
    }
    if (in[0] != MSG_SLOT)
    {
        s->alive = 0;
        return -1;
    }
    if (peerVal)
        *peerVal = (unsigned short)(((unsigned short)in[1] << 8) | in[2]);
    return 1;
}