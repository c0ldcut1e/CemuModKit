#include <malloc.h>

#include "../coreinit/memdefaultheap.h"

MEMAllocFromDefaultHeapFn MEMAllocFromDefaultHeap     = NULL;
MEMAllocFromDefaultHeapExFn MEMAllocFromDefaultHeapEx = NULL;
MEMFreeToDefaultHeapFn MEMFreeToDefaultHeap           = NULL;

void *__cut_alloc_from_defaultheap(uint32_t size) { return malloc(size); }

void *__cut_alloc_from_defaultheap_ex(uint32_t size, int alignment) { return memalign(alignment, size); }

void __cut_free_to_defaultheap(void *ptr) { free(ptr); }

void __init_cut_defaultheap(void)
{
    MEMAllocFromDefaultHeap   = __cut_alloc_from_defaultheap;
    MEMAllocFromDefaultHeapEx = __cut_alloc_from_defaultheap_ex;
    MEMFreeToDefaultHeap      = __cut_free_to_defaultheap;
}

void __fini_cut_defaultheap(void) {}
