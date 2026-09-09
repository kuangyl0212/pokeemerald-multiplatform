/*
 * LAN link conduit - internet relay client.
 *
 * Instead of one player listening and the other dialing a direct host:port,
 * both players connect out to a shared relay server. The host asks the server
 * to CREATE a room and receives a room code it can share out-of-band; the guest
 * asks to JOIN by that code. When the room is full the relay server sends both
 * sides a READY line and thereafter transparently pipes bytes between them,
 * so the game's own HELLO / SLOT session protocol runs unmodified on top.
 *
 * Control-phase wire format is newline-delimited plaintext:
 *   client -> server: CREATE <roomName> <version>\n   (host)
 *                  or: JOIN   <roomCode> <version>\n  (guest)
 *   server -> client: ROOM <code>\n
 *                  or: READY\n      (room full -> both switch to relay)
 *                  or: ERR <reason>\n
 * Everything after CREATE/JOIN completes and READY is received is raw game bytes.
 */
#include "lnet_relay.h"
#include "lnet_net.h"

#include <stdio.h>
#include <string.h>

/* Every packet (line / log) is tiny; clamp to a sane control frame. */
#define RELAY_LINE_MAX 256

/* Write `fmt` as one line to the socket. Returns 1 on success. */
static int send_line(LNetSock *s, const char *fmt, const char *a, const char *b)
{
    char line[RELAY_LINE_MAX];
    int n;

    n = snprintf(line, sizeof(line), fmt, a, b);
    if (n < 0 || (size_t)n >= sizeof(line))
        return 0;
    return lnet_net_send_all(s, (const unsigned char *)line, (size_t)n, NULL);
}

/* Read one '\n'-terminated line (without the terminator). Returns 1 on
 * success, 0 on transport/protocol error or an over-long line. */
static int recv_line(LNetSock *s, char *out, size_t cap, int *err)
{
    size_t n = 0;

    while (1)
    {
        unsigned char c;
        if (n + 1 >= cap)
            return 0;
        if (!lnet_net_recv_all(s, &c, 1, err))
            return 0;
        if (c == '\n')
        {
            out[n] = '\0';
            return 1;
        }
        out[n++] = (char)c;
    }
}

static int looks_like_err(const char *line)
{
    return strncmp(line, "ERR ", 4) == 0;
}

LNetSock *lnet_relay_connect_create(const char *server, unsigned short port,
                                    const char *roomName, const char *version,
                                    char *roomId, size_t roomIdLen, int *err)
{
    LNetSock *s;
    char line[RELAY_LINE_MAX];

    if (err)
        *err = 0;

    s = lnet_net_connect(server, port, err);
    if (s == NULL)
        return NULL;

    if (!send_line(s, "CREATE %s %s\n", roomName ? roomName : "-", version))
        goto fail;
    if (!recv_line(s, line, sizeof(line), err))
        goto fail;
    if (looks_like_err(line))
        goto fail;
    if (strncmp(line, "ROOM ", 5) != 0)
        goto fail;
    if (roomId && roomIdLen)
    {
        (void)strncpy(roomId, line + 5, roomIdLen - 1);
        roomId[roomIdLen - 1] = '\0';
    }

    return s;

fail:
    if (err && *err == 0)
        *err = -1;
    lnet_net_close(s);
    return NULL;
}

int lnet_relay_wait_ready(LNetSock *sock, int *err)
{
    char line[RELAY_LINE_MAX];

    if (!recv_line(sock, line, sizeof(line), err))
        return 0;
    if (looks_like_err(line) || strcmp(line, "READY") != 0)
    {
        if (err && *err == 0)
            *err = -1;
        return 0;
    }
    return 1;
}

int lnet_relay_poll_ready(LNetSock *sock, int *err)
{
    char line[RELAY_LINE_MAX];

    if (lnet_net_readable(sock) <= 0)
        return 0; /* nothing available yet, keep waiting */
    /* Data arrived: consume one control line. The server sends its tiny
     * READY line in one write; a blocking line read here is effectively
     * atomic on loopback/LAN and can only stall a single frame. */
    if (!recv_line(sock, line, sizeof(line), err))
        return -1;
    if (looks_like_err(line) || strcmp(line, "READY") != 0)
    {
        if (err && *err == 0)
            *err = -1;
        return -1;
    }
    return 1;
}

LNetSock *lnet_relay_create(const char *server, unsigned short port,
                            const char *roomName, const char *version,
                            char *roomId, size_t roomIdLen, int *err)
{
    LNetSock *s = lnet_relay_connect_create(server, port, roomName, version,
                                            roomId, roomIdLen, err);
    if (s == NULL)
        return NULL;
    if (!lnet_relay_wait_ready(s, err))
    {
        lnet_net_close(s);
        return NULL;
    }
    return s;
}

LNetSock *lnet_relay_connect_join(const char *server, unsigned short port,
                                  const char *roomId, const char *version, int *err)
{
    LNetSock *s;

    if (err)
        *err = 0;

    s = lnet_net_connect(server, port, err);
    if (s == NULL)
        return NULL;

    if (!send_line(s, "JOIN %s %s\n", roomId ? roomId : "-", version))
    {
        if (err && *err == 0)
            *err = -1;
        lnet_net_close(s);
        return NULL;
    }
    /* JOIN accepted by the socket write; READY is still outstanding and must be
     * polled via lnet_relay_poll_ready(). A room-name/version reject will surface
     * as an ERR line through that poll and fail cleanly. */
    return s;
}

LNetSock *lnet_relay_join(const char *server, unsigned short port,
                          const char *roomId, const char *version, int *err)
{
    LNetSock *s;
    char line[RELAY_LINE_MAX];

    if (err)
        *err = 0;

    s = lnet_net_connect(server, port, err);
    if (s == NULL)
        return NULL;

    if (!send_line(s, "JOIN %s %s\n", roomId ? roomId : "-", version))
        goto fail;
    if (!recv_line(s, line, sizeof(line), err))
        goto fail;
    if (looks_like_err(line) || strcmp(line, "READY") != 0)
        goto fail;

    return s;

fail:
    if (err && *err == 0)
        *err = -1;
    lnet_net_close(s);
    return NULL;
}