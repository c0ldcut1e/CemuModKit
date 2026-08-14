#pragma once

#include "../mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMutex
{
    void (*OSInitMutex)(OSMutex *mutex);
    void (*OSInitMutexEx)(OSMutex *mutex, const char *name);
    void (*OSLockMutex)(OSMutex *mutex);
    BOOL (*OSTryLockMutex)(OSMutex *mutex);
    void (*OSUnlockMutex)(OSMutex *mutex);
} ImportsCoreInitMutex;

#ifdef __cplusplus
}
#endif
