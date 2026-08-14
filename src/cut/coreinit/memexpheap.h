#pragma once

#include "../cut.h"
#include "memheap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMExpHeap MEMExpHeap;
typedef struct MEMExpHeapBlock MEMExpHeapBlock;
typedef struct MEMExpHeapBlockList MEMExpHeapBlockList;

typedef void (*MEMExpHeapBlockVisitor)(void *block, MEMHeapHandle heap, void *context);

typedef enum MEMExpHeapMode
{
    MEM_EXP_HEAP_MODE_FIRST_FREE   = 0,
    MEM_EXP_HEAP_MODE_NEAREST_SIZE = 1,
} MEMExpHeapMode;

typedef enum MEMExpHeapDirection
{
    MEM_EXP_HEAP_DIR_FROM_TOP    = 0,
    MEM_EXP_HEAP_DIR_FROM_BOTTOM = 1,
} MEMExpHeapDirection;

typedef enum MEMExpHeapCheckFlags
{
    MEM_EXP_HEAP_CHECK_FLAGS_NONE       = 0,
    MEM_EXP_HEAP_CHECK_FLAGS_LOG_ERRORS = 1,
} MEMExpHeapCheckFlags;

struct MEMExpHeapBlock
{
    uint32_t attribs;
    uint32_t blockSize;
    MEMExpHeapBlock *prev;
    MEMExpHeapBlock *next;
    uint16_t tag;
    CUT_UNKNOWN_BYTES(0x02);
};
CUT_CHECK_OFFSET(MEMExpHeapBlock, 0x00, attribs);
CUT_CHECK_OFFSET(MEMExpHeapBlock, 0x04, blockSize);
CUT_CHECK_OFFSET(MEMExpHeapBlock, 0x08, prev);
CUT_CHECK_OFFSET(MEMExpHeapBlock, 0x0c, next);
CUT_CHECK_OFFSET(MEMExpHeapBlock, 0x10, tag);
CUT_CHECK_SIZE(MEMExpHeapBlock, 0x14);

struct MEMExpHeapBlockList
{
    MEMExpHeapBlock *head;
    MEMExpHeapBlock *tail;
};
CUT_CHECK_OFFSET(MEMExpHeapBlockList, 0x00, head);
CUT_CHECK_OFFSET(MEMExpHeapBlockList, 0x04, tail);
CUT_CHECK_SIZE(MEMExpHeapBlockList, 0x08);

struct CUT_PACKED MEMExpHeap
{
    MEMHeapHeader header;
    MEMExpHeapBlockList freeList;
    MEMExpHeapBlockList usedList;
    uint16_t groupId;
    uint16_t attribs;
};
CUT_CHECK_OFFSET(MEMExpHeap, 0x00, header);
CUT_CHECK_OFFSET(MEMExpHeap, 0x40, freeList);
CUT_CHECK_OFFSET(MEMExpHeap, 0x48, usedList);
CUT_CHECK_OFFSET(MEMExpHeap, 0x50, groupId);
CUT_CHECK_OFFSET(MEMExpHeap, 0x52, attribs);
CUT_CHECK_SIZE(MEMExpHeap, 0x54);

CUT_IMPORT MEMHeapHandle (*MEMCreateExpHeapEx)(void *heap, uint32_t size, uint16_t flags);

CUT_IMPORT void *(*MEMAllocFromExpHeapEx)(MEMHeapHandle heap, uint32_t size, int alignment);

CUT_IMPORT void (*MEMFreeToExpHeap)(MEMHeapHandle heap, void *block);

CUT_IMPORT uint32_t (*MEMGetTotalFreeSizeForExpHeap)(MEMHeapHandle heap);

CUT_IMPORT uint32_t (*MEMGetAllocatableSizeForExpHeapEx)(MEMHeapHandle heap, int alignment);

CUT_IMPORT uint32_t (*MEMGetSizeForMBlockExpHeap)(const void *block);

CUT_IMPORT void (*MEMVisitAllocatedForExpHeap)(MEMHeapHandle heap, MEMExpHeapBlockVisitor callback, void *context);

#ifdef __cplusplus
}
#endif
