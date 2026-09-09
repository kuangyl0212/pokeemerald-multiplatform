#include "lnet_link.h"
#include "lnet_session.h"
#include "lnet_sio.h"
#include <stdlib.h>

struct LNetLink
{
    LNetSession *session;
    LNetSio *sio;
    LNetRole role;
};

LNetLink *lnet_link_host(unsigned short port, int *err)
{
    LNetLink *l = (LNetLink *)calloc(1, sizeof(LNetLink));
    l->session = lnet_session_host(port, err);
    if (l->session == NULL)
    {
        free(l);
        return NULL;
    }
    l->role = LNET_ROLE_HOST;
    l->sio = lnet_sio_new(l->role);
    return l;
}

LNetLink *lnet_link_join(const char *host, unsigned short port, int *err)
{
    LNetLink *l = (LNetLink *)calloc(1, sizeof(LNetLink));
    l->session = lnet_session_join(host, port, err);
    if (l->session == NULL)
    {
        free(l);
        return NULL;
    }
    l->role = LNET_ROLE_CLIENT;
    l->sio = lnet_sio_new(l->role);
    return l;
}

void lnet_link_close(LNetLink *l)
{
    if (l == NULL)
        return;
    if (l->sio != NULL)
        lnet_sio_free(l->sio);
    if (l->session != NULL)
        lnet_session_close(l->session);
    free(l);
}

LNetRole lnet_link_role(const LNetLink *l)
{
    return l->role;
}

int lnet_link_live(const LNetLink *l)
{
    return l != NULL && l->session != NULL;
}

int lnet_link_poll(LNetLink *l, int *err)
{
    if (l == NULL || l->session == NULL)
    {
        if (err)
            *err = LNET_ERR_OK;
        return -1;
    }
    return lnet_session_poll(l->session, err);
}

int lnet_link_ready(const LNetLink *l)
{
    return l != NULL && l->session != NULL && lnet_session_is_ready(l->session);
}

int lnet_link_slot(LNetLink *l, unsigned short mySend, unsigned short *peerSend, unsigned long long *recvView)
{
    int r;

    if (l == NULL || l->session == NULL)
        return 0;
    if (!lnet_session_is_ready(l->session))
        return 0;
    r = lnet_session_exchange(l->session, mySend, peerSend);
    if (r != 1)
        return 0; /* -1: peer gone/error -> link failed */
    /* RECV must reflect the just-completed slot; commit then expose it. */
    lnet_sio_commit(l->sio, mySend, *peerSend);
    *recvView = lnet_sio_recv_current(l->sio);
    return 1;
}