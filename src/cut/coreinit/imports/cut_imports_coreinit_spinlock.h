#pragma once

#include "../spinlock.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitSpinlock
{
    void (*OSInitSpinLock)(OSSpinLock *spinlock);
    BOOL (*OSUninterruptibleSpinLock_Acquire)(OSSpinLock *spinlock);
    BOOL (*OSUninterruptibleSpinLock_Release)(OSSpinLock *spinlock);
} ImportsCoreInitSpinlock;

#ifdef __cplusplus
}
#endif
