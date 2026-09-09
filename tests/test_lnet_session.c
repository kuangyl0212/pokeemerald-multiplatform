/*
 * LAN link conduit - end-to-end host test.
 *
 * Spins up a HOST session and a CLIENT session on real loopback TCP, runs an
 * 8-slot SIO round over lnet_session_exchange(), and verifies:
 *   - role negotiation (host == master, client == slave)
 *   - each side receives exactly the peer's SEND values, in order
 *   - both sides compose an identical multi-player RECV (lnet_sio), matching the
 *     GBA one-slot pipeline: recv[k] == hostSend[k-1] | clientSend[k-1]<<16.
 */
#include "lnet_session.h"
#include "lnet_sio.h"

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
static HANDLE g_ht, g_ct;
#define RUN_BOTH()                                  \
    do                                              \
    {                                               \
        g_ht = CreateThread(NULL, 0, host_main, NULL, 0, NULL); \
        g_ct = CreateThread(NULL, 0, client_main, NULL, 0, NULL); \
        WaitForSingleObject(g_ht, INFINITE);        \
        WaitForSingleObject(g_ct, INFINITE);        \
    } while (0)
#define THREAD_RET DWORD WINAPI
#else
#include <pthread.h>
#define RUN_BOTH()                              \
    do                                          \
    {                                           \
        pthread_t t1, t2;                       \
        pthread_create(&t1, NULL, host_main, NULL); \
        pthread_create(&t2, NULL, client_main, NULL); \
        pthread_join(t1, NULL);                 \
        pthread_join(t2, NULL);                 \
    } while (0)
#define THREAD_RET void *
#endif

#define PORT 45678u
#define ROUND 8

static int g_passed = 0;
static int g_failed = 0;

#define CHECK(cond, msg)                                            \
    do                                                              \
    {                                                               \
        if (cond)                                                   \
        {                                                           \
            g_passed++;                                             \
        }                                                           \
        else                                                        \
        {                                                           \
            g_failed++;                                             \
            printf("FAIL: %s (%s:%d)\n", msg, __FILE__, __LINE__);  \
        }                                                           \
    } while (0)

static const unsigned short g_hSend[ROUND] = {0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888};
static const unsigned short g_cSend[ROUND] = {0xAAAA, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 0x1234, 0x9ABC};
static unsigned long long g_hostRecv[ROUND];
static unsigned long long g_clientRecv[ROUND];
static int g_hostFail = 0;
static int g_clientFail = 0;

static THREAD_RET host_main(void *arg)
{
    int k;
    unsigned short peer;
    int err;
    LNetSession *s;
    LNetSio *sio;
    (void)arg;
    s = lnet_session_host(PORT, &err);
    if (s == NULL)
    {
        g_hostFail = 1;
        return 0;
    }
    /* lnet_session_host does NOT block to accept; poll until ready. */
    while (!lnet_session_is_ready(s))
    {
        if (lnet_session_poll(s, &err) < 0)
        {
            g_hostFail = 1;
            break;
        }
        sched_yield();
    }
    CHECK(lnet_session_role(s) == LNET_ROLE_HOST, "host role is HOST");
    sio = lnet_sio_new(LNET_ROLE_HOST);
    for (k = 0; k < ROUND; k++)
    {
        g_hostRecv[k] = lnet_sio_recv_current(sio);
        if (lnet_session_exchange(s, g_hSend[k], &peer) != 1 || peer != g_cSend[k])
        {
            g_hostFail = 1;
            break;
        }
        lnet_sio_commit(sio, g_hSend[k], peer);
    }
    CHECK(g_hostRecv[0] == 0xFFFFFFFF00000000ULL, "host recv[0] starts idle (0xFFFF high slots)");
    lnet_sio_free(sio);
    lnet_session_close(s);
    return 0;
}

static THREAD_RET client_main(void *arg)
{
    int k;
    unsigned short peer;
    int err;
    LNetSession *s;
    LNetSio *sio;
    (void)arg;
    s = lnet_session_join("127.0.0.1", PORT, &err);
    if (s == NULL)
    {
        g_clientFail = 1;
        return 0;
    }
    /* lnet_session_join does NOT block to connect; poll until ready. */
    while (!lnet_session_is_ready(s))
    {
        if (lnet_session_poll(s, &err) < 0)
        {
            g_clientFail = 1;
            break;
        }
        sched_yield();
    }
    CHECK(lnet_session_role(s) == LNET_ROLE_CLIENT, "client role is CLIENT");
    sio = lnet_sio_new(LNET_ROLE_CLIENT);
    for (k = 0; k < ROUND; k++)
    {
        g_clientRecv[k] = lnet_sio_recv_current(sio);
        if (lnet_session_exchange(s, g_cSend[k], &peer) != 1 || peer != g_hSend[k])
        {
            g_clientFail = 1;
            break;
        }
        lnet_sio_commit(sio, g_cSend[k], peer);
    }
    CHECK(g_clientRecv[0] == 0xFFFFFFFF00000000ULL, "client recv[0] starts idle (0xFFFF high slots)");
    lnet_sio_free(sio);
    lnet_session_close(s);
    return 0;
}

int main(void)
{
    int k;
    (void)PORT;

    RUN_BOTH();

    CHECK(g_hostFail == 0, "host completed every slot");
    CHECK(g_clientFail == 0, "client completed every slot");

    for (k = 0; k + 1 < ROUND; k++)
    {
        unsigned long long expect;
        char msg[96];
        expect = (unsigned long long)g_hSend[k] | ((unsigned long long)g_cSend[k] << 16);
        expect |= 0xFFFFFFFF00000000ULL;
        snprintf(msg, sizeof(msg), "recv[%d] host == host[k]|client[k]<<16", k + 1);
        CHECK(g_hostRecv[k + 1] == expect, msg);
        snprintf(msg, sizeof(msg), "recv[%d] client == host[k]|client[k]<<16", k + 1);
        CHECK(g_clientRecv[k + 1] == expect, msg);
        snprintf(msg, sizeof(msg), "recv[%d] host == client", k + 1);
        CHECK(g_hostRecv[k + 1] == g_clientRecv[k + 1], msg);
    }

    printf("passed: %d / failed: %d\n", g_passed, g_failed);
    return g_failed == 0 ? 0 : 1;
}