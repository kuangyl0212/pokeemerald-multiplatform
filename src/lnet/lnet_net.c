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
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
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

static void set_nonblock(int fd)
{
#ifdef _WIN32
    u_long nb = 1;
    ioctlsocket(fd, FIONBIO, &nb);
#else
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#endif
}

static void set_block(int fd)
{
#ifdef _WIN32
    u_long nb = 0;
    ioctlsocket(fd, FIONBIO, &nb);
#else
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
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

LNetSock *lnet_net_accept_nb(LNetSock *listener, int *err)
{
    if (err)
        *err = LNET_ERR_OK;
    {
        fd_set rfds;
        struct timeval tv;
        int ready;

        FD_ZERO(&rfds);
        FD_SET(listener->fd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
#ifdef _WIN32
        ready = select(0, &rfds, NULL, NULL, &tv);
#else
        ready = select(listener->fd + 1, &rfds, NULL, NULL, &tv);
#endif
        if (ready <= 0)
        {
            if (err)
                *err = LNET_ERR_AGAIN;
            return NULL;
        }
        return lnet_net_accept(listener, err);
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

LNetSock *lnet_net_connect_nb(const char *host, unsigned short port, LNetSock **out, int *err)
{
    int fd;
    struct sockaddr_in a;
    struct hostent *he;
    LNetSock *inProgress = (out != NULL) ? *out : NULL;

    if (err)
        *err = LNET_ERR_OK;
    /* If `out` already carries an in-progress socket, resume its connect
     * instead of starting a brand-new one. */
    if (inProgress != NULL && inProgress->fd >= 0)
    {
        fd_set wfds;
        struct timeval tv;
        LNetSock *c = inProgress;
        fd = c->fd;
        FD_ZERO(&wfds);
        FD_SET(fd, &wfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
#ifdef _WIN32
        if (select(0, NULL, &wfds, NULL, &tv) > 0)
#else
        if (select(fd + 1, NULL, &wfds, NULL, &tv) > 0)
#endif
        {
            int soerr = 0;
            socklen_t len = sizeof(soerr);
            getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&soerr, &len);
            if (soerr != 0)
            {
                if (err)
                    *err = LNET_ERR_CONNECT;
#ifdef _WIN32
                closesocket(fd);
#else
                close(fd);
#endif
                free(c);
                if (out)
                    *out = NULL;
                return NULL;
            }
            set_nodelay(fd);
            set_block(fd);
            if (out)
                *out = NULL;
            return c;
        }
        if (err)
            *err = LNET_ERR_AGAIN;
        return NULL;
    }

#ifdef _WIN32
    winsock_init();
#endif
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        if (err)
            *err = LNET_ERR_SOCKET;
        return NULL;
    }
    set_nonblock(fd);
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
#ifdef _WIN32
        if (WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != WSAEINPROGRESS)
        {
            if (err)
                *err = LNET_ERR_CONNECT;
            closesocket(fd);
            return NULL;
        }
#else
        if (errno != EINPROGRESS && errno != EWOULDBLOCK)
        {
            if (err)
                *err = LNET_ERR_CONNECT;
            close(fd);
            return NULL;
        }
#endif
        {
            LNetSock *c = (LNetSock *)calloc(1, sizeof(LNetSock));
            c->fd = fd;
            if (out)
                *out = c;
            if (err)
                *err = LNET_ERR_AGAIN;
            return NULL;
        }
    }
    set_nodelay(fd);
    set_block(fd);
    {
        LNetSock *s = (LNetSock *)calloc(1, sizeof(LNetSock));
        s->fd = fd;
        return s;
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
        written = send(s->fd, p, left, MSG_NOSIGNAL);
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

/* Select-gated single send. Sockets may be blocking or non-blocking; this
 * never blocks because we only write when the fd is writable. Returns bytes
 * actually moved via *sent so callers can resume partial writes. */
int lnet_net_send_nb(LNetSock *s, const void *data, size_t n, size_t *sent, int *err)
{
    ssize_t r;
    fd_set wfds;
    struct timeval tv;

    if (err)
        *err = LNET_ERR_OK;
    FD_ZERO(&wfds);
    FD_SET(s->fd, &wfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
#ifdef _WIN32
    if (select(0, NULL, &wfds, NULL, &tv) <= 0)
#else
    if (select(s->fd + 1, NULL, &wfds, NULL, &tv) <= 0)
#endif
    {
        if (sent)
            *sent = 0;
        if (err)
            *err = LNET_ERR_AGAIN;
        return 0;
    }
#ifdef _WIN32
    r = send(s->fd, (const char *)data, (int)n, 0);
#else
    r = send(s->fd, (const char *)data, n, MSG_NOSIGNAL);
#endif
    if (r < 0)
    {
#ifdef _WIN32
        int e = WSAGetLastError();
        if (e == WSAEWOULDBLOCK || e == WSAEINPROGRESS)
        {
            if (sent)
                *sent = 0;
            if (err)
                *err = LNET_ERR_AGAIN;
            return 0;
        }
#else
        if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINPROGRESS)
        {
            if (sent)
                *sent = 0;
            if (err)
                *err = LNET_ERR_AGAIN;
            return 0;
        }
#endif
        if (sent)
            *sent = 0;
        if (err)
            *err = LNET_ERR_SEND;
        return -1;
    }
    if (r == 0)
    {
        if (sent)
            *sent = 0;
        if (err)
            *err = LNET_ERR_CLOSED;
        return -1;
    }
    if (sent)
        *sent = (size_t)r;
    return 1;
}

/* Select-gated single recv. Only reads when the fd is readable, so a peer that
 * connects but never (or only partially) sends the HELLO cannot block the game
 * loop; it just yields AGAIN until more data (or an EOF/error) arrives. */
int lnet_net_recv_nb(LNetSock *s, void *data, size_t n, size_t *got, int *err)
{
    ssize_t r;
    fd_set rfds;
    struct timeval tv;

    if (err)
        *err = LNET_ERR_OK;
    FD_ZERO(&rfds);
    FD_SET(s->fd, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
#ifdef _WIN32
    if (select(0, &rfds, NULL, NULL, &tv) <= 0)
#else
    if (select(s->fd + 1, &rfds, NULL, NULL, &tv) <= 0)
#endif
    {
        if (got)
            *got = 0;
        if (err)
            *err = LNET_ERR_AGAIN;
        return 0;
    }
#ifdef _WIN32
    r = recv(s->fd, (char *)data, (int)n, 0);
#else
    r = recv(s->fd, (char *)data, n, 0);
#endif
    if (r < 0)
    {
#ifdef _WIN32
        int e = WSAGetLastError();
        if (e == WSAEWOULDBLOCK || e == WSAEINPROGRESS)
        {
            if (got)
                *got = 0;
            if (err)
                *err = LNET_ERR_AGAIN;
            return 0;
        }
#else
        if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINPROGRESS)
        {
            if (got)
                *got = 0;
            if (err)
                *err = LNET_ERR_AGAIN;
            return 0;
        }
#endif
        if (got)
            *got = 0;
        if (err)
            *err = LNET_ERR_RECV;
        return -1;
    }
    if (r == 0)
    {
        if (got)
            *got = 0;
        if (err)
            *err = LNET_ERR_CLOSED;
        return -1;
    }
    if (got)
        *got = (size_t)r;
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