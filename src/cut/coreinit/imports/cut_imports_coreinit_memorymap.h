#pragma once

#include "../memorymap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMemorymap
{
    uint32_t (*OSEffectiveToPhysical)(uint32_t virtualAddress);
    uint32_t (*__OSPhysicalToEffectiveCached)(uint32_t physicalAddress);
    uint32_t (*__OSPhysicalToEffectiveUncached)(uint32_t physicalAddress);
    BOOL (*OSIsAddressValid)(uint32_t virtualAddress);
    BOOL (*__OSValidateAddressSpaceRange)(int unused, uint32_t virtualAddress, uint32_t size);
    uint32_t (*OSAllocVirtAddr)(uint32_t virtualAddress, uint32_t size, uint32_t align);
    BOOL (*OSFreeVirtAddr)(uint32_t virtualAddress, uint32_t size);
    OSMemoryMapMode (*OSQueryVirtAddr)(uint32_t virtualAddress);
    BOOL (*OSMapMemory)(uint32_t virtualAddress, uint32_t physicalAddress, uint32_t size, OSMemoryMapMode mode);
    BOOL (*OSUnmapMemory)(uint32_t virtualAddress, uint32_t size);
    void (*OSGetMapVirtAddrRange)(uint32_t *outVirtualAddress, uint32_t *outSize);
    void (*OSGetAvailPhysAddrRange)(uint32_t *outPhysicalAddress, uint32_t *outSize);
    void (*OSGetDataPhysAddrRange)(uint32_t *outPhysicalAddress, uint32_t *outSize);
} ImportsCoreInitMemorymap;

#ifdef __cplusplus
}
#endif
