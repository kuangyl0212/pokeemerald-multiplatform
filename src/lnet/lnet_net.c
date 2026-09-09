/*
 * LAN link conduit - TCP transport.
 */
#include "lnet_net.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
static int s_winsock_init = 0;
#endif

struct LNetSock
{
    int fd;
    int err; /* last error */
};

#ifdef _WIN32
static void winsock_init(void)
{
    if (!s_winsock_init)
    {
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
        s_winsock_init = 1;
    }
}
#endif

static void set_reuseaddr(int fd)
{
    int one = 1;
#ifdef _WIN32
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof(one));
#else
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
#endif
}

static void set_nodelay(int fd)
{
    int one = 1;
#ifdef _WIN32
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char *)&one, sizeof(one));
#else
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
#endif
}

LNetSock *lnet_net_listen(unsigned short port, int *err)
{
#ifdef _WIN32
    winsock_init();
#endif
    if (err)
        *err = LNET_ERR_OK;
    {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in a;
        if (fd < 0)
        {
            if (err)
                *err = LNET_ERR_SOCKET;
            return NULL;
        }
        memset(&a, 0, sizeof(a));
        a.sin_family = AF_INET;
        a.sin_port = htons(port);
        a.sin_addr.s_addr = htonl(INADDR_ANY);
        set_reuseaddr(fd);
        if (bind(fd, (struct sockaddr *)&a, sizeof(a)) < 0)
        {
            if (err)
                *err = LNET_ERR_BIND;
#ifdef _WIN32
            closesocket(fd);
#else
            close(fd);
#endif
            return NULL;
        }
        if (listen(fd, 1) < 0)
        {
            if (err)
                *err = LNET_ERR_LISTEN;
#ifdef _WIN32
            closesocket(fd);
#else
            close(fd);
#endif
            return NULL;
        }
        {
            LNetSock *s = (LNetSock *)calloc(1, sizeof(LNetSock));
            s->fd = fd;
            return s;
        }
    }
}

LNetSock *lnet_net_accept(LNetSock *listener, int *err)
{
    if (err)
        *err = LNET_ERR_OK;
    {
        int fd = accept(listener->fd, NULL, NULL);
        if (fd < 0)
        {
            if (err)
                *err = LNET_ERR_ACCEPT;
            return NULL;
        }
        set_nodelay(fd);
        {
            LNetSock *s = (LNetSock *)calloc(1, sizeof(LNetSock));
            s->fd = fd;
            return s;
        }
    }
}

LNetSock *lnet_net_connect(const char *host, unsigned short port, int *err)
{
#ifdef _WIN32
    winsock_init();
#endif
    if (err)
        *err = LNET_ERR_OK;
    {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in a;
        struct hostent *he;
        if (fd < 0)
        {
            if (err)
                *err = LNET_ERR_SOCKET;
            return NULL;
        }
        memset(&a, 0, sizeof(a));
        a.sin_family = AF_INET;
        a.sin_port = htons(port);
        he = gethostbyname(host);
        if (he != NULL && he->h_addrtype == AF_INET)
            memcpy(&a.sin_addr, he->h_addr_list[0], he->h_length);
        else
            a.sin_addr.s_addr = inet_addr(host);
        if (connect(fd, (struct sockaddr *)&a, sizeof(a)) < 0)
        {
            if (err)
                *err = LNET_ERR_CONNECT;
#ifdef _WIN32
            closesocket(fd);
#else
            close(fd);
#endif
            return NULL;
        }
        set_nodelay(fd);
        {
            LNetSock *s = (LNetSock *)calloc(1, sizeof(LNetSock));
            s->fd = fd;
            return s;
        }
    }
}

int lnet_net_send_all(LNetSock *s, const void *data, size_t n, int *err)
{
    const char *p = (const char *)data;
    size_t left = n;
    if (err)
        *err = LNET_ERR_OK;
    while (left > 0)
    {
        ssize_t written;
#ifdef _WIN32
        written = send(s->fd, p, (int)left, 0);
#else
        written = send(s->fd, p, left, 0);
#endif
        if (written <= 0)
        {
            if (err)
                *err = (written == 0) ? LNET_ERR_CLOSED : LNET_ERR_SEND;
            return 0;
        }
        p += written;
        left -= (size_t)written;
    }
    return 1;
}

int lnet_net_recv_all(LNetSock *s, void *data, size_t n, int *err)
{
    char *p = (char *)data;
    size_t left = n;
    if (err)
        *err = LNET_ERR_OK;
    while (left > 0)
    {
        ssize_t got;
#ifdef _WIN32
        got = recv(s->fd, p, (int)left, 0);
#else
        got = recv(s->fd, p, left, 0);
#endif
        if (got <= 0)
        {
            if (err)
                *err = (got == 0) ? LNET_ERR_CLOSED : LNET_ERR_RECV;
            return 0;
        }
        p += got;
        left -= (size_t)got;
    }
    return 1;
}

void lnet_net_close(LNetSock *s)
{
    if (s == NULL)
        return;
#ifdef _WIN32
    closesocket(s->fd);
#else
    close(s->fd);
#endif
    free(s);
}