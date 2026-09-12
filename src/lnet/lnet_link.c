#include "lnet_link.h"
#include "lnet_session.h"
#include "lnet_sio.h"
#include <stdlib.h>

struct LNetLink
{
    LNetSession *session;
    LNetSio *sio;
    LNetRole role;
    int frameSlotIdx; /* production position of the next slot within this frame */
};

LNetLink *lnet_link_host(unsigned short port, int *err)
{
    LNetLink *l = (LNetLink *)calloc(1, sizeof(LNetLink));
    l->session = lnet_session_host(port, err);
    if (l->session == NULL)
    {
        free(l);
        return NULL;
    }
    l->role = LNET_ROLE_HOST;
    l->sio = lnet_sio_new(l->role);
    return l;
}

LNetLink *lnet_link_join(const char *host, unsigned short port, int *err)
{
    LNetLink *l = (LNetLink *)calloc(1, sizeof(LNetLink));
    l->session = lnet_session_join(host, port, err);
    if (l->session == NULL)
    {
        free(l);
        return NULL;
    }
    l->role = LNET_ROLE_CLIENT;
    l->sio = lnet_sio_new(l->role);
    return l;
}

/* Build a link over an already-connected, READY socket (e.g. the relay socket
 * once the server reports READY). Takes ownership of `sock`; HELLO + SLOT still
 * run on top, so lnet_link_poll() must be called until ready before exchange. */
LNetLink *lnet_link_open(LNetSock *sock, LNetRole role, int *err)
{
    LNetLink *l = (LNetLink *)calloc(1, sizeof(LNetLink));
    l->session = lnet_session_open(sock, role, err);
    if (l->session == NULL)
    {
        free(l);
        lnet_net_close(sock);
        return NULL;
    }
    l->role = role;
    l->sio = lnet_sio_new(l->role);
    return l;
}

void lnet_link_close(LNetLink *l)
{
    if (l == NULL)
        return;
    if (l->sio != NULL)
        lnet_sio_free(l->sio);
    if (l->session != NULL)
        lnet_session_close(l->session);
    free(l);
}

LNetRole lnet_link_role(const LNetLink *l)
{
    return l->role;
}

int lnet_link_live(const LNetLink *l)
{
    return l != NULL && l->session != NULL;
}

int lnet_link_poll(LNetLink *l, int *err)
{
    if (l == NULL || l->session == NULL)
    {
        if (err)
            *err = LNET_ERR_OK;
        return -1;
    }
    return lnet_session_poll(l->session, err);
}

int lnet_link_ready(const LNetLink *l)
{
    return l != NULL && l->session != NULL && lnet_session_is_ready(l->session);
}

int lnet_link_pump(LNetLink *l)
{
    int r;

    if (l == NULL || l->session == NULL)
        return -1;
    if (!lnet_session_is_ready(l->session))
        return -1;
    r = lnet_session_pump(l->session);
    if (r > 0)
        l->frameSlotIdx = 0; /* a new frame of slots starts now */
    return r;
}

/* How many peer slot values are sitting in the receive FIFO right now.
 *
 * Used by the handshake phase to decide how many slots it is safe to run: the
 * settle test in DoHandshake counts a slot that is neither a handshake word nor
 * 0xFFFF as "no player", so running slots the peer has not filled yet would
 * reset playerCount on every other slot and the handshake would never settle. */
int lnet_link_recv_available(LNetLink *l)
{
    if (l == NULL || l->session == NULL)
        return 0;
    return lnet_session_recv_available(l->session);
}

int lnet_link_slot(LNetLink *l, unsigned short mySend, unsigned short *peerSend, int *gotPeer, unsigned long long *recvView)
{
    unsigned short peer = 0xFFFF; /* floating bus when the peer's slot is absent */
    int got;

    if (l == NULL || l->session == NULL)
        return -1;
    if (!lnet_session_is_ready(l->session))
        return -1;

    /* Queue first: our own SEND is produced on the local clock and must never
     * be held back by the peer's arrival, or the two slot counters drift and
     * the CMD_LENGTH checksum window desynchronises. */
    lnet_session_send_slot(l->session, mySend);

    /* Take the peer's value for THIS frame position, not a blind FIFO pop: the
     * k-th consumed slot must be the k-th produced value or the checksum
     * sampling window permanently misaligns. A missing position reports 0 so
     * the caller fills 0xFFFF and marks the frame dirty instead. */
    got = lnet_session_recv_slot_at(l->session, l->frameSlotIdx, &peer);
    l->frameSlotIdx++;

    /* Commit on EVERY slot, including one where no peer value landed.
     *
     * DoRecv samples REG_SIOMLT_RECV once per slot (it does not test our own
     * echoed slot, which is only recvView's high half), so a missing peer value
     * does not corrupt the checksum directly. What it does break is the
     * pipeline: leaving the view stale froze the value the game read while the
     * slot counter kept running, so send-side and recv-side progress stopped
     * matching and the CMD_LENGTH boundary landed on the wrong slot. Advancing
     * with a defined fill value keeps both sides in phase; a genuinely lost
     * slot shows up as seqGap instead. */
    lnet_sio_commit(l->sio, mySend, peer);

    if (peerSend)
        *peerSend = peer;
    if (gotPeer)
        *gotPeer = got;
    if (recvView)
        *recvView = lnet_sio_recv_current(l->sio);
    return 1;
}

void lnet_link_stats(LNetLink *l, unsigned long *sent, unsigned long *recv,
                     unsigned long *sendOverrun, unsigned long *recvOverrun,
                     unsigned long *seqGap, unsigned long *framesDropped,
                     unsigned long *fillFrames)
{
    if (l == NULL || l->session == NULL)
        return;
    lnet_session_stats(l->session, sent, recv, sendOverrun, recvOverrun, seqGap,
                       framesDropped, fillFrames);
}

int lnet_link_frame(LNetLink *l, const unsigned short *myFrame, unsigned short *peerFrame)
{
    if (l == NULL || l->session == NULL)
        return -1;
    if (!lnet_session_is_ready(l->session))
        return -1;
    return lnet_session_exchange_frame(l->session, myFrame, peerFrame);
}