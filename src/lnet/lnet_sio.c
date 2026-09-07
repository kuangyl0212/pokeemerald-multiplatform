#include "lnet_sio.h"
#include <stdlib.h>

struct LNetSio
{
    LNetRole role;
    unsigned short myPrev;
    unsigned short peerPrev;
};

LNetSio *lnet_sio_new(LNetRole role)
{
    LNetSio *s = (LNetSio *)calloc(1, sizeof(LNetSio));
    s->role = role;
    return s;
}

void lnet_sio_free(LNetSio *s) { free(s); }
LNetRole lnet_sio_role(const LNetSio *s) { return s->role; }

/*
 * Both players present an identical 4-slot RECV: slot0 = host SEND,
 * slot1 = client SEND, delayed by one slot (holds the previous commit).
 */
unsigned long long lnet_sio_recv_current(const LNetSio *s)
{
    if (s->role == LNET_ROLE_HOST)
        return (unsigned long long)s->myPrev | ((unsigned long long)s->peerPrev << 16);
    else
        return (unsigned long long)s->peerPrev | ((unsigned long long)s->myPrev << 16);
}

void lnet_sio_commit(LNetSio *s, unsigned short mySend, unsigned short peerSend)
{
    s->myPrev = mySend;
    s->peerPrev = peerSend;
}