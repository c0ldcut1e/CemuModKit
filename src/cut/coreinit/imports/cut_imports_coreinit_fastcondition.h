#pragma once

#include "../fastcondition.h"
#include "../fastmutex.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitFastCondition
{
    void (*OSFastCond_Init)(OSFastCondition *condition, const char *name);
    void (*OSFastCond_Wait)(OSFastCondition *condition, OSFastMutex *mutex);
    void (*OSFastCond_Signal)(OSFastCondition *condition);
} ImportsCoreInitFastCondition;

#ifdef __cplusplus
}
#endif
