#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <sys/reent.h>

#include "../coreinit/memdefaultheap.h"
#include "../coreinit/memexpheap.h"
#include "../coreinit/memorymap.h"

void *__wrap__malloc_r(struct _reent *r, size_t size)
{
    void *ptr = MEMAllocFromDefaultHeapEx((uint32_t) size, 0x40);
    if (!ptr && r)
    {
        r->_errno = ENOMEM;
    }
    return ptr;
}

void __wrap__free_r(struct _reent *r, void *ptr)
{
    (void) r;
    if (!ptr)
    {
        return;
    }
    MEMFreeToDefaultHeap(ptr);
}

void *__wrap__calloc_r(struct _reent *r, size_t nmemb, size_t size)
{
    size_t total = nmemb * size;
    void *ptr    = __wrap__malloc_r(r, total);
    if (!ptr)
    {
        return 0;
    }
    __builtin_memset(ptr, 0, total);
    return ptr;
}

void *__wrap__realloc_r(struct _reent *r, void *ptr, size_t size)
{
    if (!ptr)
    {
        return __wrap__malloc_r(r, size);
    }

    if (size == 0)
    {
        __wrap__free_r(r, ptr);
        return 0;
    }

    void *new_ptr = __wrap__malloc_r(r, size);
    if (!new_ptr)
    {
        return 0;
    }

    size_t old_size = MEMGetSizeForMBlockExpHeap ? MEMGetSizeForMBlockExpHeap(ptr) : 0;
    if (old_size)
    {
        __builtin_memcpy(new_ptr, ptr, old_size < size ? old_size : size);
    }
    __wrap__free_r(r, ptr);
    return new_ptr;
}

void *__wrap__memalign_r(struct _reent *r, size_t align, size_t size)
{
    void *ptr = MEMAllocFromDefaultHeapEx((uint32_t) size, (int) align);
    if (!ptr && r)
    {
        r->_errno = ENOMEM;
    }
    return ptr;
}

struct mallinfo __wrap__mallinfo_r(struct _reent *r)
{
    (void) r;
    struct mallinfo info = {0};
    return info;
}

void __wrap__malloc_stats_r(struct _reent *r) { (void) r; }

int __wrap__mallopt_r(struct _reent *r, int param, int value)
{
    (void) r;
    (void) param;
    (void) value;
    return 0;
}

size_t __wrap__malloc_usable_size_r(struct _reent *r, void *ptr)
{
    (void) r;
    if (!ptr || !MEMGetSizeForMBlockExpHeap)
    {
        return 0;
    }
    return MEMGetSizeForMBlockExpHeap(ptr);
}

void *__wrap__valloc_r(struct _reent *r, size_t size) { return __wrap__memalign_r(r, OS_PAGE_SIZE, size); }

void *__wrap__pvalloc_r(struct _reent *r, size_t size)
{
    size_t page_size = OS_PAGE_SIZE;
    size_t rounded   = (size + page_size - 1) & ~(page_size - 1);
    return __wrap__memalign_r(r, page_size, rounded);
}

int __wrap__malloc_trim_r(struct _reent *r, size_t pad)
{
    (void) r;
    (void) pad;
    return 0;
}
