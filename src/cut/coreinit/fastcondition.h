#pragma once

#include "../cut.h"
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSFastCondition OSFastCondition;
typedef struct OSFastMutex OSFastMutex;

#define OS_FAST_CONDITION_TAG 0x664E6456u

struct OSFastCondition
{
    uint32_t tag;
    const char *name;
    CUT_UNKNOWN_BYTES(4);
    OSThreadQueue queue;
};
CUT_CHECK_OFFSET(OSFastCondition, 0x00, tag);
CUT_CHECK_OFFSET(OSFastCondition, 0x04, name);
CUT_CHECK_OFFSET(OSFastCondition, 0x0c, queue);
CUT_CHECK_SIZE(OSFastCondition, 0x1c);

CUT_IMPORT void (*OSFastCond_Init)(OSFastCondition *condition, const char *name);

CUT_IMPORT void (*OSFastCond_Wait)(OSFastCondition *condition, OSFastMutex *mutex);

CUT_IMPORT void (*OSFastCond_Signal)(OSFastCondition *condition);

#ifdef __cplusplus
}
#endif
