#pragma once

#include "../fastmutex.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitFastMutex
{
    void (*OSFastMutex_Init)(OSFastMutex *mutex, const char *name);
    void (*OSFastMutex_Lock)(OSFastMutex *mutex);
    void (*OSFastMutex_Unlock)(OSFastMutex *mutex);
    BOOL (*OSFastMutex_TryLock)(OSFastMutex *mutex);
} ImportsCoreInitFastMutex;

#ifdef __cplusplus
}
#endif
