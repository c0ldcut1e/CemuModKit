#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSpinLock OSSpinLock;

struct CUT_ALIGNAS(16) OSSpinLock
{
    uint32_t owner;
    CUT_UNKNOWN_BYTES(0x4);
    uint32_t recursion;
    CUT_UNKNOWN_BYTES(0x4);
};
CUT_CHECK_OFFSET(OSSpinLock, 0x0, owner);
CUT_CHECK_OFFSET(OSSpinLock, 0x8, recursion);
CUT_CHECK_SIZE(OSSpinLock, 0x10);

CUT_IMPORT void (*OSInitSpinLock)(OSSpinLock *spinlock);

CUT_IMPORT BOOL (*OSUninterruptibleSpinLock_Acquire)(OSSpinLock *spinlock);

CUT_IMPORT BOOL (*OSUninterruptibleSpinLock_Release)(OSSpinLock *spinlock);

#ifdef __cplusplus
}
#endif
