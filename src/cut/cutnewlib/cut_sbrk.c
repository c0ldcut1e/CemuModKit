#include "../coreinit/atomic.h"
#include "../coreinit/memdefaultheap.h"
#include "../coreinit/memexpheap.h"
#include "../coreinit/memheap.h"
#include "cut_newlib.h"

static MEMHeapHandle sHeapHandle   = NULL;
static void *sHeapBase             = NULL;
static uint32_t sHeapMaxSize       = 0;
static volatile uint32_t sHeapSize = 0;

#define CUT_SBRK_HEAP_MAX_SIZE (64 * 1024 * 1024)
#define CUT_SBRK_HEAP_RESERVE  (32 * 1024 * 1024)

void *__cut_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    uint32_t newSize;
    uint32_t oldSize = sHeapSize;

    do
    {
        newSize = oldSize + incr;

        if (newSize > sHeapMaxSize)
        {
            r->_errno = ENOMEM;
            return (void *) -1;
        }
    } while (!OSCompareAndSwapAtomicEx(&sHeapSize, oldSize, newSize, &oldSize));

    return ((uint8_t *) sHeapBase) + oldSize;
}

void __init_cut_sbrk_heap(MEMHeapHandle heapHandle)
{
    if (sHeapBase)
    {
        // Already initialised
        return;
    }

    sHeapHandle = heapHandle;

    uint32_t allocatableSize = MEMGetAllocatableSizeForExpHeapEx(sHeapHandle, 4);
    if (allocatableSize > CUT_SBRK_HEAP_RESERVE)
    {
        sHeapMaxSize = allocatableSize - CUT_SBRK_HEAP_RESERVE;
    }
    else
    {
        sHeapMaxSize = allocatableSize / 2;
    }

    if (sHeapMaxSize > CUT_SBRK_HEAP_MAX_SIZE)
    {
        sHeapMaxSize = CUT_SBRK_HEAP_MAX_SIZE;
    }

    while (sHeapMaxSize >= (1024 * 1024))
    {
        sHeapBase = MEMAllocFromExpHeapEx(sHeapHandle, sHeapMaxSize, 4);
        if (sHeapBase)
        {
            break;
        }

        sHeapMaxSize /= 2;
    }

    if (!sHeapBase)
    {
        sHeapMaxSize = 0;
        return;
    }

    sHeapSize = 0;
}

void __fini_cut_sbrk_heap()
{
    if (!sHeapBase)
    {
        // Already finalised
        return;
    }

    if (sHeapHandle)
    {
        MEMFreeToExpHeap(sHeapHandle, sHeapBase);
    }

    sHeapBase    = NULL;
    sHeapSize    = 0;
    sHeapMaxSize = 0;
}
