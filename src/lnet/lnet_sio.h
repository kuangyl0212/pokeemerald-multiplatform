/*
 * LAN link conduit - 2-player virtual SIO transfer engine.
 *
 * Mirrors the GBA multi-player serial-link exchange so the game layer can keep
 * driving the original link.c state machine while the transport is a LAN TCP
 * session. Per transfer (one serial slot) each device holds exactly one 16-bit
 * SEND value. The hardware delivers, on every device, a 4-slot RECV whose
 * slot i holds device i's SEND. For two players the RECV identical on both
 * sides: slot0 = host SEND, slot1 = client SEND.
 *
 * Pipeline note (matches the GBA): a multi-SIO transfer takes exactly one
 * serial slot, and the RECV a device reads afterwards holds the SEND values
 * both sides drove *during that slot*. lnet_sio_recv_current() therefore
 * exposes the CURRENT slot's view, and lnet_sio_commit() is what advances it.
 *
 * The commit is the whole contract: it must run once per slot the game runs,
 * whether or not the peer's value for that slot has arrived yet. Committing
 * only on a completed round trip (the previous behaviour) left the view pinned
 * to a stale slot while the slot counters kept moving, which is what let the
 * two peers drift apart.
 */
#ifndef LNET_SIO_H
#define LNET_SIO_H

#include "lnet_session.h"

typedef struct LNetSio LNetSio;

LNetSio *lnet_sio_new(LNetRole role);
void lnet_sio_free(LNetSio *s);

LNetRole lnet_sio_role(const LNetSio *s);

/*
 * The 4-slot RECV (2 players -> slots 0 and 1) for the slot being run, i.e.
 * the values both sides drove during that same slot. Pass a 0xFFFF fill for a
 * peer value that has not arrived. Identical on both sides.
 */
unsigned long long lnet_sio_recv_current(const LNetSio *s);

/*
 * Commit the results of the just-ran serial slot: `mySend` is your own SEND
 * produced this slot, `peerSend` is the peer's SEND for the same slot (use
 * 0xFFFF if it has not arrived). Call this once per slot, unconditionally -
 * see the pipeline note above.
 */
void lnet_sio_commit(LNetSio *s, unsigned short mySend, unsigned short peerSend);

#endif /* LNET_SIO_H */