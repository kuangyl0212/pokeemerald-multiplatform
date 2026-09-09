/*
 * LAN link conduit - bidirectional session between two game instances.
 *
 * One instance is the HOST (link master, player slot 0); the other is the
 * CLIENT (link slave, player slot 1). After a short HELLO role handshake the
 * two sides exchange 16-bit slot values with lnet_session_exchange(), which
 * implements the master-driven SIO multi-player per-transfer swap.
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

void lnet_session_close(LNetSession *s);

LNetRole lnet_session_role(const LNetSession *s);

/*
 * Exchange one SIO slot value with the peer.
 * Pass your OWN current per-slot SEND value; on success *peerVal receives the
 * peer's SEND for the same slot. Blocks until the peer also calls this.
 * Returns 1 on success, 0 if the peer closed, -1 on protocol/transport error.
 */
int lnet_session_exchange(LNetSession *s, unsigned short myVal, unsigned short *peerVal);

#endif /* LNET_SESSION_H */