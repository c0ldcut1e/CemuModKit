#pragma once

#include "../cut.h"
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSFastMutex OSFastMutex;
typedef struct OSFastMutexLink OSFastMutexLink;
typedef struct OSFastCondition OSFastCondition;

struct OSFastMutexLink
{
    OSFastMutex *next;
    OSFastMutex *prev;
};
CUT_CHECK_OFFSET(OSFastMutexLink, 0x00, next);
CUT_CHECK_OFFSET(OSFastMutexLink, 0x04, prev);
CUT_CHECK_SIZE(OSFastMutexLink, 0x08);

#define OS_FAST_MUTEX_TAG 0x664D7458u

struct OSFastMutex
{
    uint32_t tag;
    const char *name;
    CUT_UNKNOWN_BYTES(4);
    OSThreadSimpleQueue queue;
    OSFastMutexLink link;
    CUT_UNKNOWN_BYTES(16);
};
CUT_CHECK_OFFSET(OSFastMutex, 0x00, tag);
CUT_CHECK_OFFSET(OSFastMutex, 0x04, name);
CUT_CHECK_OFFSET(OSFastMutex, 0x0c, queue);
CUT_CHECK_OFFSET(OSFastMutex, 0x14, link);
CUT_CHECK_SIZE(OSFastMutex, 0x2c);

CUT_IMPORT void (*OSFastMutex_Init)(OSFastMutex *mutex, const char *name);

CUT_IMPORT void (*OSFastMutex_Lock)(OSFastMutex *mutex);

CUT_IMPORT void (*OSFastMutex_Unlock)(OSFastMutex *mutex);

CUT_IMPORT BOOL (*OSFastMutex_TryLock)(OSFastMutex *mutex);

#ifdef __cplusplus
}
#endif
