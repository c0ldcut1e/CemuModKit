#pragma once

#include "../cut.h"
#include "memlist.h"
#include "spinlock.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMHeapHeader MEMHeapHeader;
typedef MEMHeapHeader *MEMHeapHandle;

typedef enum MEMBaseHeapType
{
    MEM_BASE_HEAP_MEM1 = 0,
    MEM_BASE_HEAP_MEM2 = 1,
    MEM_BASE_HEAP_FG   = 8,
} MEMBaseHeapType;

typedef enum MEMHeapFillType
{
    MEM_HEAP_FILL_TYPE_UNUSED    = 0,
    MEM_HEAP_FILL_TYPE_ALLOCATED = 1,
    MEM_HEAP_FILL_TYPE_FREED     = 2,
} MEMHeapFillType;

typedef enum MEMHeapTag
{
    MEM_BLOCK_HEAP_TAG    = 0x424C4B48u,
    MEM_EXPANDED_HEAP_TAG = 0x45585048u,
    MEM_FRAME_HEAP_TAG    = 0x46524D48u,
    MEM_UNIT_HEAP_TAG     = 0x554E5448u,
    MEM_USER_HEAP_TAG     = 0x55535248u,
} MEMHeapTag;

typedef enum MEMHeapFlags
{
    MEM_HEAP_FLAG_ZERO_ALLOCATED = 1 << 0,
    MEM_HEAP_FLAG_DEBUG_MODE     = 1 << 1,
    MEM_HEAP_FLAG_USE_LOCK       = 1 << 2,
} MEMHeapFlags;

struct MEMHeapHeader
{
    //! Tag indicating which type of heap this is
    MEMHeapTag tag;

    //! Link for list this heap is in
    MEMMemoryLink link;

    //! List of all child heaps in this heap
    MEMMemoryList list;

    //! Pointer to start of allocatable memory
    void *dataStart;

    //! Pointer to end of allocatable memory
    void *dataEnd;

    //! Lock used when MEM_HEAP_FLAG_USE_LOCK is set.
    OSSpinLock lock;

    //! Flags set during heap creation.
    uint32_t flags;

    CUT_UNKNOWN_BYTES(0x0C);
};
CUT_CHECK_OFFSET(MEMHeapHeader, 0x00, tag);
CUT_CHECK_OFFSET(MEMHeapHeader, 0x04, link);
CUT_CHECK_OFFSET(MEMHeapHeader, 0x0C, list);
CUT_CHECK_OFFSET(MEMHeapHeader, 0x18, dataStart);
CUT_CHECK_OFFSET(MEMHeapHeader, 0x1C, dataEnd);
CUT_CHECK_OFFSET(MEMHeapHeader, 0x20, lock);
CUT_CHECK_OFFSET(MEMHeapHeader, 0x30, flags);
CUT_CHECK_SIZE(MEMHeapHeader, 0x40);

/**
 * Get base heap for memory area.
 */
CUT_IMPORT MEMHeapHandle (*MEMGetBaseHeapHandle)(MEMBaseHeapType type);

#ifdef __cplusplus
}
#endif

/** @} */
