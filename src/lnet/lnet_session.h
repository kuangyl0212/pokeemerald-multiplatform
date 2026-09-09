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
 * Exchange one SIO slot value with the peer.
 * Pass your own CURRENT per-slot SEND value; on success *peerVal receives the
 * peer's SEND for the same slot. Blocks until the full 3-byte slot has been
 * written and read (the whole atomic transfer). Returns 1 on success, -1 on a
 * permanent/protocol error or a peer that closed.
 */
int lnet_session_exchange(LNetSession *s, unsigned short myVal, unsigned short *peerVal);

#endif /* LNET_SESSION_H */