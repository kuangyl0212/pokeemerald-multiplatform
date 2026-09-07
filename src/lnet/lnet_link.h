/*
 * LAN link transport - drives the game's existing SIO serial engine over a
 * LAN TCP session.  Each 16-bit slot transaction:
 *
 *   - reads this player's REG_SIOMLT_SEND (what we transmit this slot),
 *   - echoes it to the peer and receives the peer's SEND for the same slot,
 *   - composes the 4-slot RECV the SIO would deliver on every device
 *     (host @ slot 0, client @ slot 1), identical on both sides.
 */
#ifndef LNET_LINK_H
#define LNET_LINK_H

#include "lnet_session.h"

typedef struct LNetLink LNetLink;

/* Open a link transport as the host (listens+accepts) or as a client (connects).
 * err is LNET_ERR_OK (0) on success, or LNET_ERR_* on failure. */
LNetLink *lnet_link_host(unsigned short port, int *err);
LNetLink *lnet_link_join(const char *host, unsigned short port, int *err);
void lnet_link_close(LNetLink *l);

LNetRole lnet_link_role(const LNetLink *l);
int lnet_link_live(const LNetLink *l);

/*
 * Perform one 16-bit SIO slot exchange.  Sends `mySend`, sets *peerSend to the
 * peer's value for the same slot, and writes *recvView to the 4-player RECV the
 * GBA would present (slot0 = host SEND, slot1 = client SEND, others 0).
 * Returns 1 on success, 0 if the transport has failed.
 */
int lnet_link_slot(LNetLink *l, unsigned short mySend, unsigned short *peerSend, unsigned long long *recvView);

#endif /* LNET_LINK_H */