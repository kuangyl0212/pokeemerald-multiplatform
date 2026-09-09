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

/* Start listening on the given port. Returns a listener socket. */
LNetSock *lnet_net_listen(unsigned short port, int *err);

/* Block until a peer connects. Returns a connected socket. */
LNetSock *lnet_net_accept(LNetSock *listener, int *err);

/* Connect to host:port. Returns a connected socket. */
LNetSock *lnet_net_connect(const char *host, unsigned short port, int *err);

/* Send exactly n bytes. Returns 1 on success, 0 on error/closed. */
int lnet_net_send_all(LNetSock *s, const void *data, size_t n, int *err);

/* Receive exactly n bytes. Returns 1 on success, 0 on closed/error. */
int lnet_net_recv_all(LNetSock *s, void *data, size_t n, int *err);

/* Close and free a socket. Passing NULL is a no-op. */
void lnet_net_close(LNetSock *s);

#endif /* LNET_NET_H */