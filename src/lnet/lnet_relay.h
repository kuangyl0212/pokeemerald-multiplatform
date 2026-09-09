/*
 * LAN link conduit - internet relay client.
 *
 * Both players connect out to a shared relay server instead of dialing each
 * other directly. The host creates a room and is handed a room code; the guest
 * joins by that code. Once the room is full the server relays bytes between the
 * two, so the caller can hand the returned socket straight to lnet_link_open().
 */
#ifndef LNET_RELAY_H
#define LNET_RELAY_H

#include "lnet_net.h"

/*
 * Connect to the relay server as the HOST and create a room. Sends
 * CREATE roomName version, waits for the server to assign ROOM <code>
 * (copied into roomId), then RETURNS immediately without waiting for the
 * room to fill -- so the host can show the room code to the player without
 * stalling the game frame loop. Call lnet_relay_wait_ready() later to block
 * until a guest has joined. On success *err == 0 and the returned socket is
 * owned by the caller.
 */
LNetSock *lnet_relay_connect_create(const char *server, unsigned short port,
                                    const char *roomName, const char *version,
                                    char *roomId, size_t roomIdLen, int *err);

/*
 * One-shot convenience wrapper (kept for compatibility): CREATE a room and
 * block until it is full. Equivalent to lnet_relay_connect_create() followed
 * by lnet_relay_wait_ready(); the returned socket is relay-ready.
 */
LNetSock *lnet_relay_create(const char *server, unsigned short port,
                            const char *roomName, const char *version,
                            char *roomId, size_t roomIdLen, int *err);

/*
 * Block until the relay server flips this room to relay mode (READY), i.e.
 * until the room is full. Returns 1 on success, 0 on error/transport close.
 */
int lnet_relay_wait_ready(LNetSock *sock, int *err);

/*
 * Non-blocking single-probe variant: check whether READY has arrived for sock.
 * Returns 1 when READY was consumed (the room is full), 0 when still waiting
 * (nothing read), or -1 on a protocol/transport error. Poll this once per game
 * frame -- e.g. while a host shows its room code after lnet_relay_connect_create
 * -- so the frame loop is never blocked waiting for a guest to join.
 */
int lnet_relay_poll_ready(LNetSock *sock, int *err);

/*
 * Guest variant of the two-phase flow: connect, send JOIN roomId version, and
 * return immediately WITHOUT waiting for READY (the room may not be full yet, or
 * the host may still be opening it). The caller checks READY later via
 * lnet_relay_poll_ready(), so the client never blocks the game loop. Returns the
 * pending socket on success (READY still outstanding), NULL on reject (unknown
 * room, bad version) / transport failure.
 */
LNetSock *lnet_relay_connect_join(const char *server, unsigned short port,
                                  const char *roomId, const char *version, int *err);

/*
 * Connect to the relay server as the GUEST: send JOIN roomId version and block
 * until the server flips the room to relay mode (READY). On failure *err is set
 * to a nonzero value and NULL is returned.
 */
LNetSock *lnet_relay_join(const char *server, unsigned short port,
                          const char *roomId, const char *version, int *err);

#endif /* LNET_RELAY_H */