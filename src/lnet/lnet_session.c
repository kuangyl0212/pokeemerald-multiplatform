/*
 * LAN link conduit - session implementation.
 *
 * Wire format, every message is 5 bytes: [u8 kind][u8 pos][u8 seq][u16 val BE].
 *   kind 0x10 = HELLO carrying the sender's role (0 host / 1 client). The pos
 *               and seq bytes are unused (0) and the value is the role.
 *   kind 0x20 = SLOT carrying one 16-bit slot value, the production position
 *               within the sender's frame (0..8) and the frame sequence number
 *               the sender had reached (0..255, wrapping).
 *
 * The transport is NOT lock-step any more. The game layer (link.c's DoRecv /
 * DoSend / SendRecvDone) is a *per-slot* state machine whose sendCmdIndex and
 * recvCmdIndex are jointly cleared by SendRecvDone once recvCmdIndex reaches
 * CMD_LENGTH. Both peers must therefore advance a slot exactly the same number
 * of times and in the same phase; a single slot lost to "wait for the peer"
 * permanently offsets the sendCmdIndex == 0 checksum sampling window and the
 * link dies with LINK_STAT_ERROR_CHECKSUM.
 *
 * So send and recv are two independent FIFO streams instead of one in-flight
 * slot per round trip: we always run our own 9 slots per frame on the local
 * clock, shipping whatever we have, and consume peer slots as they arrive. A
 * slot whose peer value has not landed yet is filled with 0xFFFF by the caller
 * rather than stalling the slot counter.
 *
 * The pos byte is the frame alignment anchor: the receiver reassembles the
 * peer's slots into complete 9-slot frames and presents them atomically, so
 * the k-th consumed slot is always the k-th produced value (see
 * lnet_session_recv_slot_at). The seq byte is the loss anchor: it lets the
 * receiver notice a dropped or reordered message (seqGap) and resynchronise
 * on the newest value instead of silently pairing a stale peer slot with a
 * fresh local one.
 */
#include "lnet_session.h"

#include <stdlib.h>
#include <string.h>

#define MSG_HELLO 0x10
#define MSG_SLOT  0x20

/* SLOT message is 5 bytes on the wire: kind, pos, seq, value hi, value lo. */
#define XFER_MSG_BYTES 5

/*
 * Reassembled-frame queue capacity, in frames. The engine consumes exactly one
 * frame per game frame, so 8 gives ample slack for bursty relay delivery while
 * staying bounded.
 */
#define LNET_FRAME_QUEUE_CAP 8

/*
 * Slot FIFO capacity, in slots. Sized well above one game frame worth of slots
 * (9 per frame, and a full 8-slot command frame flushes every 9 slots) so a
 * short burst - or a relay hop that delivers a whole batch at once - is
 * absorbed instead of dropped, while still bounded so a peer that stops
 * reading cannot make us grow without limit.
 */
#define XFER_FIFO_SLOTS 256
#define XFER_FIFO_MASK  (XFER_FIFO_SLOTS - 1)

/* Frame exchange: one command frame = CMD_LENGTH (8) u16 values = 16 bytes. */
#define LNET_FRAME_SLOTS 8
#define LNET_FRAME_BYTES (LNET_FRAME_SLOTS * 2)

/* Non-blocking handshake phases. The HELLO exchange is driven a few bytes at a
 * time from poll(): the peer is allowed to connect but then send nothing (a
 * stale/semidead connection), and the game loop must never block on it. */
#define HS_STEP_FIRST  1 /* host: send host HELLO; client: recv peer HELLO */
#define HS_STEP_SECOND 2 /* host: recv client HELLO; client: send own HELLO */

typedef struct
{
    unsigned char pos; /* production position within the sender's frame (0..8) */
    unsigned char seq;
    unsigned short val;
} XferSlot;

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

    /* ---- outbound FIFO: slots our game produced, not yet on the socket ---- */
    XferSlot tx[XFER_FIFO_SLOTS];
    int txHead;
    int txTail;
    int txCount;
    unsigned char txWire[XFER_MSG_BYTES]; /* message currently being written out */
    int txWireLen;
    int txWirePos;
    unsigned char txSeq; /* seq stamped on the next message we build */
    int prodPos;         /* production position stamped on the next slot we queue */

    /* ---- inbound FIFO: whole peer slots parsed off the socket ------------ */
    XferSlot rx[XFER_FIFO_SLOTS];
    int rxHead;
    int rxTail;
    int rxCount;
    unsigned char rxBuf[XFER_MSG_BYTES]; /* reassembly for partial arrivals */
    int rxBufPos;
    unsigned char expectedSeq; /* seq the peer's next message should carry */

    /* ---- frame reassembly: peer slots grouped into complete 9-slot frames - */
    XferSlot curFrame[9];      /* frame currently being reassembled */
    unsigned curFrameMask;     /* bit i = production position i has arrived */
    XferSlot frameQueue[LNET_FRAME_QUEUE_CAP][9]; /* completed frames */
    int fqHead;
    int fqCount;
    unsigned long framesDropped; /* diagnostics: incomplete frames discarded */

    /* ---- staged frame: the complete frame currently being consumed -------- */
    unsigned short staged[9];
    int stagedIsFill; /* 1 = no complete peer frame: present fill (0xFFFF) */
    int stagedIdx;    /* diagnostics: how many slots were consumed */
    int stagedLoaded; /* staged[] holds a popped frame for this pump cycle */
    unsigned long fillFrames; /* diagnostics: fill frames presented */

    /* Frame exchange buffers (non-blocking partial send/recv) */
    unsigned char frameSendBuf[LNET_FRAME_BYTES];
    int frameSendLen;   /* bytes filled in frameSendBuf (0 or LNET_FRAME_BYTES) */
    int frameSendPos;   /* bytes already sent */
    unsigned char frameRecvBuf[LNET_FRAME_BYTES];
    int frameRecvPos;   /* bytes already received */
    unsigned short peerLast[LNET_FRAME_SLOTS]; /* last received peer frame */

    /* Diagnostics, exported through lnet_session_stats(). */
    unsigned long sent;
    unsigned long recv;
    unsigned long sendOverrun; /* slots dropped because the tx FIFO was full */
    unsigned long recvOverrun; /* slots dropped because the rx FIFO was full */
    unsigned long seqGap;      /* messages whose seq was not the expected one */
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

/* Wrap an already-connected, READY transport socket as a session. Only the
 * HELLO role handshake is still outstanding; lnet_session_poll() advances it. */
LNetSession *lnet_session_open(LNetSock *sock, LNetRole role, int *err)
{
    LNetSession *s;

    if (err)
        *err = LNET_ERR_OK;
    if (sock == NULL)
    {
        if (err)
            *err = LNET_ERR_SOCKET;
        return NULL;
    }

    s = (LNetSession *)calloc(1, sizeof(LNetSession));
    s->sock = sock; /* transport is already established */
    s->role = role;
    s->alive = 1;
    s->connecting = 0;
    s->hsStep = HS_STEP_FIRST;
    s->hsOutSent = 0;
    s->hsInGot = 0;
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
 * Queue one slot value produced by the local game this slot.
 *
 * Never blocks and never fails for flow-control reasons: the local slot
 * counter must keep advancing at exactly the rate the peer's does, so a
 * transport hiccup is absorbed by dropping the OLDEST queued slot (the game
 * layer tolerates a lost slot far better than a stalled slot counter) rather
 * than by asking the caller to try again. sendOverrun records the loss.
 */
void lnet_session_send_slot(LNetSession *s, unsigned short myVal)
{
    if (s == NULL || !s->alive)
        return;

    if (s->txCount == XFER_FIFO_SLOTS)
    {
        /* Full: discard the oldest and reuse its entry for the new slot. */
        s->txTail = (s->txTail + 1) & XFER_FIFO_MASK;
        s->txCount--;
        s->sendOverrun++;
    }

    s->tx[s->txHead].pos = (unsigned char)s->prodPos++;
    s->tx[s->txHead].seq = s->txSeq++;
    s->tx[s->txHead].val = myVal;
    s->txHead = (s->txHead + 1) & XFER_FIFO_MASK;
    s->txCount++;
}

/*
 * Pop the next peer slot that has fully arrived.
 * Returns 1 with *peerVal set, or 0 when nothing is queued (in which case
 * *peerVal is left untouched so the caller can keep its fallback value).
 */
int lnet_session_recv_slot(LNetSession *s, unsigned short *peerVal)
{
    if (s == NULL || s->rxCount == 0)
        return 0;

    if (peerVal)
        *peerVal = s->rx[s->rxTail].val;
    s->rxTail = (s->rxTail + 1) & XFER_FIFO_MASK;
    s->rxCount--;
    s->recv++;
    return 1;
}

/*
 * Take this frame's posInFrame-th (0..8) peer slot value.
 *
 * On the first call of a pump cycle (stagedLoaded == 0) the next complete peer
 * frame is popped off the frame queue into staged[]. If none has arrived the
 * frame is presented as fill and every position reports 0 - the engine fills
 * 0xFFFF itself and marks the frame dirty, which keeps both streams aligned
 * without ever pairing slot k of one peer frame with slot j of another.
 *
 * Returns 1 with the real value in *val, or 0 when this position carries no
 * real value this frame (*val untouched so the caller keeps its fill).
 */
int lnet_session_recv_slot_at(LNetSession *s, int posInFrame, unsigned short *val)
{
    if (s == NULL)
        return 0;

    if (s->stagedIdx == 0 && !s->stagedLoaded)
    {
        if (s->fqCount > 0)
        {
            int i;
            for (i = 0; i < 9; i++)
                s->staged[i] = s->frameQueue[s->fqHead][i].val;
            s->fqHead = (s->fqHead + 1) % LNET_FRAME_QUEUE_CAP;
            s->fqCount--;
            s->stagedIsFill = 0;
        }
        else
        {
            s->stagedIsFill = 1;
            s->fillFrames++;
        }
        s->stagedLoaded = 1;
    }

    if (s->stagedIsFill || posInFrame < 0 || posInFrame > 8)
        return 0;

    if (val)
        *val = s->staged[posInFrame];
    s->stagedIdx++;
    return 1;
}

/*
 * How many peer slot values are sitting in the rx FIFO right now.
 *
 * The handshake phase uses this to bound how many slots it runs: DoHandshake's
 * settle test treats a slot that is neither a handshake word nor 0xFFFF as "no
 * player" and zeroes playerCount, so running slots the peer has not filled yet
 * would reset the count on alternating slots and the handshake would never
 * converge.
 */
int lnet_session_recv_available(const LNetSession *s)
{
    if (s == NULL)
        return 0;
    return s->rxCount;
}

/*
 * Move bytes for this frame: drain everything the peer has sent into the rx
 * FIFO, then push as much of our tx FIFO onto the socket as it accepts.
 *
 * Receive runs FIRST and to exhaustion. The peer slots are the scarce resource
 * - the game needs one per slot it runs - while our own tx bytes are safe in
 * the FIFO and can wait for the next frame. Draining greedily also keeps the
 * socket's receive window open, so the peer's relay hop cannot back up.
 *
 * Non-blocking: returns 1 on success (possibly having moved nothing) and -1 on
 * a fatal error, in which case the session is marked dead.
 */
int lnet_session_pump(LNetSession *s)
{
    int err = LNET_ERR_OK;

    if (s == NULL || s->sock == NULL || !s->alive)
        return -1;

    /* New production/presentation cycle: slots queued after this point belong
     * to the frame now starting (pos 0..8), and the staged frame consumed via
     * recv_slot_at() must be re-selected on the first call. */
    s->prodPos = 0;
    s->stagedIdx = 0;
    s->stagedLoaded = 0;

    /* One lnet_net_recv_nb() call yields at most one packet's worth of bytes,
     * so loop until it reports "nothing more" - otherwise a batch delivery
     * (the relay forwarding a whole burst) would trickle in one call per
     * frame and the rx FIFO would never catch up with the local slot rate. */
    for (;;)
    {
        size_t got = 0;
        int r = lnet_net_recv_nb(s->sock, s->rxBuf + s->rxBufPos,
                                 sizeof(s->rxBuf) - (size_t)s->rxBufPos, &got, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        if (r == 0 || got == 0)
            break;

        s->rxBufPos += (int)got;
        if (s->rxBufPos < (int)sizeof(s->rxBuf))
            continue; /* message still incomplete: keep reading */

        s->rxBufPos = 0;
        if (s->rxBuf[0] == MSG_SLOT)
        {
            unsigned char pos = s->rxBuf[1];
            unsigned char seq = s->rxBuf[2];
            unsigned short val = (unsigned short)(((unsigned short)s->rxBuf[3] << 8) | s->rxBuf[4]);

            /* Sequence anchor: a seq that is not the one we expected means the
             * peer advanced without us seeing a message (loss/reorder). Count
             * it and resynchronise on what actually arrived instead of
             * erroring out - the game tolerates a hole, not a dead link. */
            if (seq != s->expectedSeq)
                s->seqGap++;
            s->expectedSeq = (unsigned char)(seq + 1);

            if (s->rxCount == XFER_FIFO_SLOTS)
            {
                /* Full: the game is not consuming slots. Keep the freshest
                 * data and drop the oldest, same policy as the tx side. */
                s->rxTail = (s->rxTail + 1) & XFER_FIFO_MASK;
                s->rxCount--;
                s->recvOverrun++;
            }
            s->rx[s->rxHead].pos = pos;
            s->rx[s->rxHead].seq = seq;
            s->rx[s->rxHead].val = val;
            s->rxHead = (s->rxHead + 1) & XFER_FIFO_MASK;
            s->rxCount++;

            /* Frame reassembly: group the peer's slots by their production
             * position into complete 9-slot frames so recv_slot_at() can
             * present them atomically. TCP is ordered, so a healthy stream is
             * 0,1,2..8; anything else is defensive bookkeeping only. */
            if (pos > 8)
            {
                s->framesDropped++;
            }
            else if (pos == 0)
            {
                if (s->curFrameMask != 0x1FF)
                    s->framesDropped++; /* previous frame never completed */
                s->curFrame[0].pos = pos;
                s->curFrame[0].seq = seq;
                s->curFrame[0].val = val;
                s->curFrameMask = 1u;
            }
            else
            {
                unsigned need = (1u << pos) - 1u; /* bits (pos-1)..0 */
                if ((s->curFrameMask & need) != need)
                {
                    s->framesDropped++; /* stream not contiguous: drop */
                }
                else
                {
                    s->curFrame[pos].pos = pos;
                    s->curFrame[pos].seq = seq;
                    s->curFrame[pos].val = val;
                    s->curFrameMask |= 1u << pos;
                    if (pos == 8)
                    {
                        int slot = (s->fqHead + s->fqCount) % LNET_FRAME_QUEUE_CAP;
                        if (s->fqCount == LNET_FRAME_QUEUE_CAP)
                        {
                            /* Full: drop the oldest complete frame. */
                            s->fqHead = (s->fqHead + 1) % LNET_FRAME_QUEUE_CAP;
                            s->fqCount--;
                            s->framesDropped++;
                        }
                        memcpy(s->frameQueue[slot], s->curFrame, sizeof(s->curFrame));
                        s->fqCount++;
                    }
                }
            }
        }
        /* Anything else is a stray/unknown message: the HELLO bytes belong to
         * the handshake path, which runs strictly before slot traffic, so a
         * non-SLOT tag here has no defined slot meaning and is skipped. */
    }

    /* Now push the tx FIFO out. Resume the partially written message first so a
     * slot is never duplicated or split across frames. */
    for (;;)
    {
        size_t adv = 0;
        int r;

        if (s->txWirePos >= s->txWireLen)
        {
            if (s->txCount == 0)
                break; /* nothing queued: done for this frame */
            s->txWire[0] = MSG_SLOT;
            s->txWire[1] = s->tx[s->txTail].pos;
            s->txWire[2] = s->tx[s->txTail].seq;
            s->txWire[3] = (unsigned char)(s->tx[s->txTail].val >> 8);
            s->txWire[4] = (unsigned char)(s->tx[s->txTail].val & 0xFF);
            s->txWireLen = XFER_MSG_BYTES;
            s->txWirePos = 0;
            /* The slot is only removed once its bytes are fully out, so a
             * partially sent message is retried verbatim next frame. */
        }

        r = lnet_net_send_nb(s->sock, s->txWire + s->txWirePos,
                             (size_t)(s->txWireLen - s->txWirePos), &adv, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        if (adv > 0)
            s->txWirePos += (int)adv;
        if (r == 0 || adv == 0)
            break; /* socket is full: leave the rest for the next frame */

        if (s->txWirePos >= s->txWireLen)
        {
            s->txTail = (s->txTail + 1) & XFER_FIFO_MASK;
            s->txCount--;
            s->sent++;
        }
    }

    return 1;
}

/*
 * Compatibility adapter over the FIFO transport, kept because a few call sites
 * still speak the old one-slot-per-call API.
 *
 * The original semantics ("0 means the peer's data is not ready, call again
 * until it is") are exactly what caused the lock-step stall this rework
 * removes: waiting for a slot before running it desynchronises the two slot
 * counters. So this adapter just reports what the FIFO happens to hold right
 * now and lets the caller decide - never does it block or wait.
 *
 * Returns 1 when a peer slot was available (*peerVal valid), 0 when the rx
 * FIFO is empty, -1 on a permanent error or a peer that closed.
 */
int lnet_session_exchange(LNetSession *s, unsigned short myVal, unsigned short *peerVal)
{
    if (s == NULL || s->sock == NULL)
        return -1;

    lnet_session_send_slot(s, myVal);
    if (lnet_session_pump(s) < 0)
        return -1;
    return lnet_session_recv_slot(s, peerVal);
}

/*
 * Exchange an entire command frame (8 x u16 = 16 bytes) with the peer.
 * Non-blocking: each call tries to flush the send buffer and read into the
 * recv buffer, advancing at most one send and one recv step. When a complete
 * frame arrives, peerFrame is filled and 1 is returned. If no new frame is
 * ready, peerFrame is filled with the last received frame and 0 is returned.
 * Returns -1 on a permanent error or peer that closed.
 *
 * No longer on the game's active path (the slot FIFO above is), but kept for
 * the same reason as lnet_session_exchange: callers still exist and must keep
 * linking.
 */
int lnet_session_exchange_frame(LNetSession *s, const unsigned short *myFrame, unsigned short *peerFrame)
{
    int err;
    size_t adv;
    int r;

    if (s == NULL || s->sock == NULL || !s->helloDone)
        return -1;

    /* 1. Try to flush any unsent bytes from the current send buffer. */
    if (s->frameSendPos < s->frameSendLen)
    {
        r = lnet_net_send_nb(s->sock, s->frameSendBuf + s->frameSendPos,
                             (size_t)(s->frameSendLen - s->frameSendPos), &adv, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        s->frameSendPos += (int)adv;
    }

    /* 2. If the previous frame was fully sent, load the new frame and try to
     *    start sending it immediately. */
    if (s->frameSendPos >= s->frameSendLen)
    {
        memcpy(s->frameSendBuf, myFrame, LNET_FRAME_BYTES);
        s->frameSendLen = LNET_FRAME_BYTES;
        s->frameSendPos = 0;
        r = lnet_net_send_nb(s->sock, s->frameSendBuf, LNET_FRAME_BYTES, &adv, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        s->frameSendPos = (int)adv;
    }

    /* 3. Try to receive peer frame bytes. */
    if (s->frameRecvPos < LNET_FRAME_BYTES)
    {
        r = lnet_net_recv_nb(s->sock, s->frameRecvBuf + s->frameRecvPos,
                             (size_t)(LNET_FRAME_BYTES - s->frameRecvPos), &adv, &err);
        if (r < 0)
        {
            s->alive = 0;
            return -1;
        }
        s->frameRecvPos += (int)adv;
    }

    /* 4. If we have a complete frame, deliver it. */
    if (s->frameRecvPos >= LNET_FRAME_BYTES)
    {
        memcpy(peerFrame, s->frameRecvBuf, LNET_FRAME_BYTES);
        memcpy(s->peerLast, s->frameRecvBuf, LNET_FRAME_BYTES);
        s->frameRecvPos = 0;
        return 1;
    }

    /* 5. No complete frame yet; return the last received frame. */
    memcpy(peerFrame, s->peerLast, LNET_FRAME_BYTES);
    return 0;
}

/*
 * Export the transport counters. Any out pointer may be NULL. `recv` and
 * `sent` count slots actually moved over the wire; the three loss counters are
 * what tells a caller whether a stall was a dropped slot or a dead peer.
 */
void lnet_session_stats(LNetSession *s, unsigned long *sent, unsigned long *recv,
                        unsigned long *sendOverrun, unsigned long *recvOverrun,
                        unsigned long *seqGap, unsigned long *framesDropped,
                        unsigned long *fillFrames)
{
    if (s == NULL)
        return;
    if (sent)
        *sent = s->sent;
    if (recv)
        *recv = s->recv;
    if (sendOverrun)
        *sendOverrun = s->sendOverrun;
    if (recvOverrun)
        *recvOverrun = s->recvOverrun;
    if (seqGap)
        *seqGap = s->seqGap;
    if (framesDropped)
        *framesDropped = s->framesDropped;
    if (fillFrames)
        *fillFrames = s->fillFrames;
}
