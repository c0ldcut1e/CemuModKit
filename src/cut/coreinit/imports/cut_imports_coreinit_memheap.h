#pragma once

#include "../memdefaultheap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMemheap
{
    MEMHeapHandle (*MEMGetBaseHeapHandle)(MEMBaseHeapType type);
} ImportsCoreInitMemheap;

#ifdef __cplusplus
}
#endif
