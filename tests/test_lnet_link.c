/*
 * LAN link transport - end-to-end host/client test.
 *
 * Spins up a HOST transport and a CLIENT transport over real loopback TCP,
 * runs an 8-slot SIO exchange through lnet_link_slot(), and verifies:
 *   - each side hears the peer's SEND for the same slot,
 *   - each side composes the identical 4-player RECV view
 *     (host SEND @ slot 0, client SEND @ slot 1).
 */
#include "lnet_link.h"

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
#include <sched.h>
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

#define PORT 45679u
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

static unsigned short g_hostPeer[ROUND];
static unsigned long long g_hostRecv[ROUND];
static unsigned short g_clientPeer[ROUND];
static unsigned long long g_clientRecv[ROUND];
static int g_hostOk = 1;
static int g_clientOk = 1;

static THREAD_RET host_main(void *arg)
{
    int k;
    int err;
    unsigned long long recvView;
    LNetLink *l;
    (void)arg;
    l = lnet_link_host(PORT, &err);
    if (l == NULL)
    {
        g_hostOk = 0;
        printf("FAIL: host could not open transport (err=%d)\n", err);
        return 0;
    }
    CHECK(lnet_link_role(l) == LNET_ROLE_HOST, "host role is HOST");
    while (!lnet_link_ready(l))
    {
        if (lnet_link_poll(l, &err) < 0)
        {
            printf("FAIL: host setup failed (err=%d)\n", err);
            g_hostOk = 0;
            break;
        }
        sched_yield();
    }
    for (k = 0; k < ROUND; k++)
    {
        if (!lnet_link_slot(l, g_hSend[k], &g_hostPeer[k], &recvView))
        {
            printf("FAIL: host slot %d failed\n", k);
            g_hostOk = 0;
            break;
        }
        g_hostRecv[k] = recvView;
    }
    lnet_link_close(l);
    return 0;
}

static THREAD_RET client_main(void *arg)
{
    int k;
    int err;
    unsigned long long recvView;
    LNetLink *l;
    (void)arg;
    l = lnet_link_join("127.0.0.1", PORT, &err);
    if (l == NULL)
    {
        g_clientOk = 0;
        printf("FAIL: client could not open transport (err=%d)\n", err);
        return 0;
    }
    CHECK(lnet_link_role(l) == LNET_ROLE_CLIENT, "client role is CLIENT");
    while (!lnet_link_ready(l))
    {
        if (lnet_link_poll(l, &err) < 0)
        {
            g_clientOk = 0;
            printf("FAIL: client link setup failed (err=%d)\n", err);
            break;
        }
        sched_yield();
    }
    for (k = 0; k < ROUND; k++)
    {
        if (!lnet_link_slot(l, g_cSend[k], &g_clientPeer[k], &recvView))
        {
            printf("FAIL: client slot %d failed\n", k);
            g_clientOk = 0;
            break;
        }
        g_clientRecv[k] = recvView;
    }
    lnet_link_close(l);
    return 0;
}

int main(void)
{
    int k;
    (void)PORT;

    RUN_BOTH();

    CHECK(g_hostOk == 1, "host completed every slot");
    CHECK(g_clientOk == 1, "client completed every slot");

    for (k = 0; k < ROUND; k++)
    {
        unsigned long long expect = (unsigned long long)g_hSend[k] | ((unsigned long long)g_cSend[k] << 16);
        expect |= 0xFFFFFFFF00000000ULL; /* unused multi-SIO slots idle high */
        char msg[96];

        snprintf(msg, sizeof(msg), "host heard peer SEND slot %d", k);
        CHECK(g_hostPeer[k] == g_cSend[k], msg);
        snprintf(msg, sizeof(msg), "client heard peer SEND slot %d", k);
        CHECK(g_clientPeer[k] == g_hSend[k], msg);
        snprintf(msg, sizeof(msg), "host RECV slot %d == hostSEND|clientSEND<<16", k);
        CHECK(g_hostRecv[k] == expect, msg);
        snprintf(msg, sizeof(msg), "client RECV slot %d == hostSEND|clientSEND<<16", k);
        CHECK(g_clientRecv[k] == expect, msg);
        snprintf(msg, sizeof(msg), "slot %d RECV identical on both sides", k);
        CHECK(g_hostRecv[k] == g_clientRecv[k], msg);
    }

    printf("passed: %d / failed: %d\n", g_passed, g_failed);
    return g_failed == 0 ? 0 : 1;
}