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
 * Pipeline note (matches the GBA): the RECV presented for slot k contains the
 * SEND values produced by both sides during slot (k-1), i.e. a one-slot
 * delay. lnet_sio_recv_current() exposes that delayed view; lnet_sio_commit()
 * advances it with the values just produced.
 */
#ifndef LNET_SIO_H
#define LNET_SIO_H

#include "lnet_session.h"

typedef struct LNetSio LNetSio;

LNetSio *lnet_sio_new(LNetRole role);
void lnet_sio_free(LNetSio *s);

LNetRole lnet_sio_role(const LNetSio *s);

/*
 * The 4-slot RECV (2 players -> slots 0 and 1) the game must present this slot
 * before running its serial interrupt handler. Identical on both sides.
 */
unsigned long long lnet_sio_recv_current(const LNetSio *s);

/*
 * Commit the results of the just-ran serial slot: `mySend` is your own SEND
 * produced this slot, `peerSend` is the peer's SEND for the same slot. Returns
 * the value the peer should have delivered (== the peer's own SEND), which the
 * caller obtains from the transport.
 */
void lnet_sio_commit(LNetSio *s, unsigned short mySend, unsigned short peerSend);

#endif /* LNET_SIO_H */