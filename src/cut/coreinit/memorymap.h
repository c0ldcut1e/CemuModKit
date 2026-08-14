#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSMemoryMapMode
{
    OS_MAP_MEMORY_INVALID    = 0,
    OS_MAP_MEMORY_READ_ONLY  = 1,
    OS_MAP_MEMORY_READ_WRITE = 2,
    OS_MAP_MEMORY_FREE       = 3,
    OS_MAP_MEMORY_ALLOCATED  = 4,
} OSMemoryMapMode;

#define OS_PAGE_SIZE (128 * 1024)

CUT_IMPORT uint32_t (*OSEffectiveToPhysical)(uint32_t virtualAddress);

CUT_IMPORT uint32_t (*__OSPhysicalToEffectiveCached)(uint32_t physicalAddress);

CUT_IMPORT uint32_t (*__OSPhysicalToEffectiveUncached)(uint32_t physicalAddress);

CUT_IMPORT BOOL (*OSIsAddressValid)(uint32_t virtualAddress);

CUT_IMPORT BOOL (*__OSValidateAddressSpaceRange)(int unused, uint32_t virtualAddress, uint32_t size);

CUT_IMPORT uint32_t (*OSAllocVirtAddr)(uint32_t virtualAddress, uint32_t size, uint32_t align);

CUT_IMPORT BOOL (*OSFreeVirtAddr)(uint32_t virtualAddress, uint32_t size);

CUT_IMPORT OSMemoryMapMode (*OSQueryVirtAddr)(uint32_t virtualAddress);

CUT_IMPORT BOOL (*OSMapMemory)(uint32_t virtualAddress, uint32_t physicalAddress, uint32_t size, OSMemoryMapMode mode);

CUT_IMPORT BOOL (*OSUnmapMemory)(uint32_t virtualAddress, uint32_t size);

CUT_IMPORT void (*OSGetMapVirtAddrRange)(uint32_t *outVirtualAddress, uint32_t *outSize);

CUT_IMPORT void (*OSGetAvailPhysAddrRange)(uint32_t *outPhysicalAddress, uint32_t *outSize);

CUT_IMPORT void (*OSGetDataPhysAddrRange)(uint32_t *outPhysicalAddress, uint32_t *outSize);

#ifdef __cplusplus
}
#endif
