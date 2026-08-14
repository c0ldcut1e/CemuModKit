#pragma once

#include "../atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitAtomic
{
    BOOL (*OSCompareAndSwapAtomicEx)(volatile uint32_t *ptr, uint32_t compare, uint32_t value, uint32_t *old);
} ImportsCoreInitAtomic;

#ifdef __cplusplus
}
#endif
