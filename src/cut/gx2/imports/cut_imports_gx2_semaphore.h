#pragma once

#include "../semaphore.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Semaphore
{
    void (*GX2SetSemaphore)(GX2Semaphore *semaphore, GX2SemaphoreAction action);
} ImportsGX2Semaphore;

#ifdef __cplusplus
}
#endif
