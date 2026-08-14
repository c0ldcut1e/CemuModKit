#pragma once

#include "../memexpheap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMemexpheap
{
    void *(*MEMAllocFromExpHeapEx)(MEMHeapHandle heap, uint32_t size, int alignment);
    MEMHeapHandle (*MEMCreateExpHeapEx)(void *heap, uint32_t size, uint16_t flags);
    void (*MEMFreeToExpHeap)(MEMHeapHandle heap, void *block);
    uint32_t (*MEMGetTotalFreeSizeForExpHeap)(MEMHeapHandle heap);
    uint32_t (*MEMGetAllocatableSizeForExpHeapEx)(MEMHeapHandle heap, int alignment);
    uint32_t (*MEMGetSizeForMBlockExpHeap)(const void *block);
    void (*MEMVisitAllocatedForExpHeap)(MEMHeapHandle heap, MEMExpHeapBlockVisitor callback, void *context);
} ImportsCoreInitMemexpheap;

#ifdef __cplusplus
}
#endif
