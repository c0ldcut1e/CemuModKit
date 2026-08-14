#pragma once

#include "../cut.h"
#include "memheap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*MEMAllocFromDefaultHeapFn)(uint32_t size);
typedef void *(*MEMAllocFromDefaultHeapExFn)(uint32_t size, int alignment);
typedef void (*MEMFreeToDefaultHeapFn)(void *ptr);

extern MEMAllocFromDefaultHeapFn MEMAllocFromDefaultHeap;
extern MEMAllocFromDefaultHeapExFn MEMAllocFromDefaultHeapEx;
extern MEMFreeToDefaultHeapFn MEMFreeToDefaultHeap;

#ifdef __cplusplus
}
#endif
