/*
 * LAN link conduit - cross-platform TCP endpoints.
 * Windows uses Winsock2, POSIX uses BSD sockets.
 * Host compile on Linux for host tests; MinGW i686 for the PC game build.
 */
#ifndef LNET_NET_H
#define LNET_NET_H

#include <stddef.h>

typedef struct LNetSock LNetSock;

/* Error codes returned via int *err (0 = ok). */
#define LNET_ERR_OK      0
#define LNET_ERR_SOCKET  1
#define LNET_ERR_BIND    2
#define LNET_ERR_LISTEN  3
#define LNET_ERR_CONNECT 4
#define LNET_ERR_ACCEPT  5
#define LNET_ERR_SEND    6
#define LNET_ERR_RECV    7
#define LNET_ERR_CLOSED  8
#define LNET_ERR_AGAIN   9 /* operation in progress / would block */

/* Start listening on the given port. Returns a listener socket. */
LNetSock *lnet_net_listen(unsigned short port, int *err);

/* Block until a peer connects. Returns a connected socket. */
LNetSock *lnet_net_accept(LNetSock *listener, int *err);

/* Non-blocking accept. Returns a connected socket if a peer is waiting,
 * NULL otherwise. When no peer is pending the socket is still listening and
 * *err is set to LNET_ERR_AGAIN (poll again later). */
LNetSock *lnet_net_accept_nb(LNetSock *listener, int *err);

/* Connect to host:port. Returns a connected socket. */
LNetSock *lnet_net_connect(const char *host, unsigned short port, int *err);

/* Non-blocking connect. Returns a connected socket if the connection is
 * already established, NULL otherwise. When still in progress the socket is
 * returned separately via *out (caller should retry with *out on later
 * polls), and *err is set to LNET_ERR_AGAIN. Setup failures return NULL with
 * *out == NULL and *err set to the specific error. */
LNetSock *lnet_net_connect_nb(const char *host, unsigned short port, LNetSock **out, int *err);

/* Send exactly n bytes. Returns 1 on success, 0 on error/closed. */
int lnet_net_send_all(LNetSock *s, const void *data, size_t n, int *err);

/* Receive exactly n bytes. Returns 1 on success, 0 on closed/error. */
int lnet_net_recv_all(LNetSock *s, void *data, size_t n, int *err);

/* Non-blocking check whether data is currently readable on s (no bytes are
 * consumed). Returns >0 if readable, 0 if not, <0 on error. Used to poll for
 * relay READY without freezing the game frame loop. */
int lnet_net_readable(LNetSock *s);

/* Non-blocking send: select-gated single socket op that never blocks the
 * caller. Returns 1 if bytes were moved, 0 if the socket would block (poll
 * again later; *sent holds how many bytes were already written), -1 on error. */
int lnet_net_send_nb(LNetSock *s, const void *data, size_t n, size_t *sent, int *err);

/* Non-blocking recv: select-gated single socket op that never blocks the
 * caller. Returns 1 if bytes arrived, 0 if nothing is ready yet (*got holds
 * how many bytes were already read), -1 on error/closed. */
int lnet_net_recv_nb(LNetSock *s, void *data, size_t n, size_t *got, int *err);

/* Close and free a socket. Passing NULL is a no-op. */
void lnet_net_close(LNetSock *s);

#endif /* LNET_NET_H */