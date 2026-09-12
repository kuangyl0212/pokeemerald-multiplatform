/*
 * LAN link conduit - bidirectional slot session between two game instances.
 *
 * One instance is the HOST (link master, player slot 0); the other is the
 * CLIENT (link slave, player slot 1). After a short HELLO role handshake the
 * two sides exchange 16-bit SIO slot values.
 *
 * The exchange is deliberately NOT lock-step. The game's serial engine is a
 * per-slot state machine whose slot counters must advance identically on both
 * peers, so waiting for the peer before running a slot is fatal; instead each
 * side queues the slots it produces (send FIFO) and consumes the peer's as
 * they arrive (recv FIFO), with lnet_session_pump() moving the bytes once per
 * frame. lnet_session_exchange() survives only as a thin adapter over that.
 */
#ifndef LNET_SESSION_H
#define LNET_SESSION_H

#include "lnet_net.h"

typedef enum
{
    LNET_ROLE_HOST = 0, /* link master, player id 0 */
    LNET_ROLE_CLIENT = 1 /* link slave, player id 1 */
} LNetRole;

typedef struct LNetSession LNetSession;

/*
 * Bind and listen on `port`, then block until a client connects.
 * On success *err == LNET_ERR_OK and the returned session is the HOST.
 */
LNetSession *lnet_session_host(unsigned short port, int *err);

/*
 * Connect to host:port. On success the returned session is the CLIENT.
 */
LNetSession *lnet_session_join(const char *host, unsigned short port, int *err);

/*
 * Build a session over an already-connected, READY transport socket (e.g. the
 * relay socket after the server reported READY to both peers). The socket's
 * transport is established, so only the HELLO role handshake remains: drive it
 * with lnet_session_poll() before lnet_session_exchange(). `sock` is owned by
 * this session and is closed by lnet_session_close().
 */
LNetSession *lnet_session_open(LNetSock *sock, LNetRole role, int *err);

void lnet_session_close(LNetSession *s);

LNetRole lnet_session_role(const LNetSession *s);

/*
 * Drive connection establishment for a session created with
 * lnet_session_host()/lnet_session_join(). Both return a pending session that
 * does not block the caller. Call this repeatedly (e.g. every game frame) to
 * accept/connect and complete the HELLO handshake. Returns 1 when ready for
 * exchange, 0 while still connecting, -1 on a permanent error.
 */
int lnet_session_poll(LNetSession *s, int *err);

/* 1 once the session is connected and the HELLO handshake is complete. */
int lnet_session_is_ready(const LNetSession *s);

/*
 * Queue one slot value produced by the local game this slot. Never blocks and
 * never fails: if the outbound FIFO is full the oldest queued slot is dropped
 * (sendOverrun++), because stalling the caller's slot counter would desync it
 * from the peer and break the checksum window - a lost slot is recoverable, a
 * lost slot boundary is not.
 */
void lnet_session_send_slot(LNetSession *s, unsigned short myVal);

/*
 * Pop the next peer slot that has fully arrived. Returns 1 and writes *peerVal,
 * or 0 when nothing is queued (*peerVal is left untouched so the caller can
 * keep its 0xFFFF fill). Never blocks.
 */
int lnet_session_recv_slot(LNetSession *s, unsigned short *peerVal);

/*
 * Take this frame's posInFrame-th (0..8) peer slot value. The peer stamps every
 * SLOT message with its production position within its frame, and pump()
 * reassembles complete 9-slot frames from those positions, so the k-th slot the
 * local engine consumes is always paired with the k-th value the peer produced
 * - the alignment the checksum sampling window requires. Blind FIFO pops cannot
 * guarantee that: any dropped or extra slot shifts both streams permanently.
 *
 * Frames are presented atomically: if the next complete peer frame has not
 * arrived yet, the whole frame is presented as fill - returns 0 (the caller
 * should use 0xFFFF) and does NOT consume a later frame's early slots. Returns
 * 1 with the real value written to *val otherwise. Must be called with rising
 * posInFrame within one frame (0,1,2...); pump() resets the staged frame.
 */
int lnet_session_recv_slot_at(LNetSession *s, int posInFrame, unsigned short *val);

/*
 * How many peer slot values are queued for us right now. Used by the handshake
 * phase to bound the number of slots it runs (see lnet_link_recv_available).
 */
int lnet_session_recv_available(const LNetSession *s);

/*
 * Read everything the socket has to offer into the recv FIFO and write as much
 * of the send FIFO as the socket accepts. Non-blocking; call once per frame.
 * Handles partial arrivals (a 5-byte SLOT message may span calls) and partial
 * sends (resumes mid-message). Returns 1 normally, -1 on a fatal error, in
 * which case the session is marked dead.
 */
int lnet_session_pump(LNetSession *s);

/*
 * Compatibility adapter for callers that still exchange one value per call.
 * Sends myVal, pumps the transport once, then reports whatever peer slot is
 * already queued. Returns 1 with *peerVal valid, 0 if the peer's data has not
 * arrived (*peerVal untouched) and -1 on error. It never waits.
 */
int lnet_session_exchange(LNetSession *s, unsigned short myVal, unsigned short *peerVal);

/*
 * Exchange an entire command frame (8 x u16 = 16 bytes) with the peer in one
 * non-blocking call. Sends myFrame[8] and fills peerFrame[8] with the peer's
 * frame. Returns 1 on success (peerFrame is valid), 0 if the peer's frame is
 * not ready yet (peerFrame is filled with the last received frame), -1 on a
 * permanent error or peer that closed.
 */
int lnet_session_exchange_frame(LNetSession *s, const unsigned short *myFrame, unsigned short *peerFrame);

/*
 * Read the transport counters. Any out pointer may be NULL. `sent`/`recv` are
 * slots moved over the wire; `sendOverrun`/`recvOverrun` are slots dropped by
 * the FIFOs and `seqGap` counts peer messages whose frame sequence number was
 * not the expected one, i.e. slots that never arrived. `framesDropped` counts
 * incomplete frames that had to be discarded (peer stream lost alignment);
 * `fillFrames` counts frames presented as 0xFFFF fill to the engine.
 */
void lnet_session_stats(LNetSession *s, unsigned long *sent, unsigned long *recv,
                        unsigned long *sendOverrun, unsigned long *recvOverrun,
                        unsigned long *seqGap, unsigned long *framesDropped,
                        unsigned long *fillFrames);

#endif /* LNET_SESSION_H */
