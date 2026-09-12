/*
 * LAN link transport - drives the game's existing SIO serial engine over a
 * LAN TCP session.  Each 16-bit slot transaction:
 *
 *   - takes this player's REG_SIOMLT_SEND (what we transmit this slot),
 *   - queues it for the peer and picks up the peer's SEND for the same slot,
 *   - composes the 4-slot RECV the SIO would deliver on every device
 *     (host @ slot 0, client @ slot 1), identical on both sides.
 *
 * The slot transaction is non-blocking and independent of the peer's timing;
 * lnet_link_pump() moves the actual bytes once per frame.
 */
#ifndef LNET_LINK_H
#define LNET_LINK_H

#include "lnet_session.h"

typedef struct LNetLink LNetLink;

/* Open a link transport as the host (listens+accepts) or as a client (connects).
 * err is LNET_ERR_OK (0) on success, or LNET_ERR_* on failure. */
LNetLink *lnet_link_host(unsigned short port, int *err);
LNetLink *lnet_link_join(const char *host, unsigned short port, int *err);

/*
 * Build a link over an already-connected, READY transport socket (e.g. the
 * relay socket after the server reported READY). `sock` is owned by the link.
 * The HELLO role handshake is still driven by lnet_link_poll() before exchange.
 */
LNetLink *lnet_link_open(LNetSock *sock, LNetRole role, int *err);

void lnet_link_close(LNetLink *l);

LNetRole lnet_link_role(const LNetLink *l);
int lnet_link_live(const LNetLink *l);

/*
 * Advance connection establishment (call every game frame while connecting).
 * Returns 1 once the session is ready for exchange, 0 while still connecting,
 * -1 on a permanent error. Safe to call on a live/ready link.
 */
int lnet_link_poll(LNetLink *l, int *err);

/* 1 once the link is connected and the HELLO handshake is complete. */
int lnet_link_ready(const LNetLink *l);

/*
 * Move bytes for this frame: drain the peer's slots in, push ours out.
 * Call once per frame before the slot loop. Returns 1 normally, -1 on a fatal
 * error / a peer that closed.
 */
int lnet_link_pump(LNetLink *l);

/*
 * Submit this slot's SEND value and collect the peer's, without ever waiting.
 *
 * `mySend` is queued for the wire unconditionally. If a peer slot has already
 * arrived it is written to *peerSend and *gotPeer is set to 1; otherwise
 * *peerSend gets 0xFFFF (the floating bus a silent peer presents) and *gotPeer
 * is 0 so the caller can tell a real value from a fill.
 *
 * Every call commits and therefore advances the presented RECV view, even when
 * the peer's data has not landed: the local slot counter has to advance at the
 * peer's rate, and a frozen RECV view is what made the two ends drift apart.
 *
 * Never returns 0 ("try again later") - that is the lock-step contract this
 * replaced. Returns 1 normally, -1 on a fatal error.
 */
int lnet_link_slot(LNetLink *l, unsigned short mySend, unsigned short *peerSend, int *gotPeer, unsigned long long *recvView);

/*
 * How many peer slot values are queued for us right now.
 *
 * Diagnostic only. An earlier revision used this to throttle the handshake to
 * the peer's arrival rate (slots = min(9, recv_available())), which deadlocked:
 * receiving requires having sent first, so at avail==0 the budget collapsed to
 * zero slots, nothing was ever sent and both peers waited on each other
 * forever. The handshake now runs the same fixed nine slots as the established
 * state and fills a missing peer slot with 0xFFFF instead.
 */
int lnet_link_recv_available(LNetLink *l);

/*
 * Read the transport counters (see lnet_session_stats). Any pointer may be
 * NULL. Used by link.c's frame diagnostics to tell a dropped slot apart from a
 * dead peer. `framesDropped`/`fillFrames` report frame-level alignment health
 * (incomplete frames discarded / frames presented as 0xFFFF fill).
 */
void lnet_link_stats(LNetLink *l, unsigned long *sent, unsigned long *recv,
                     unsigned long *sendOverrun, unsigned long *recvOverrun,
                     unsigned long *seqGap, unsigned long *framesDropped,
                     unsigned long *fillFrames);

/*
 * Exchange an entire command frame (8 x u16) with the peer in one non-blocking
 * call. Sends myFrame[8] and fills peerFrame[8] with the peer's frame.
 * Returns 1 on success, 0 if the peer's frame is not ready (peerFrame gets the
 * last received frame), -1 on error/peer gone.
 */
int lnet_link_frame(LNetLink *l, const unsigned short *myFrame, unsigned short *peerFrame);

#endif /* LNET_LINK_H */