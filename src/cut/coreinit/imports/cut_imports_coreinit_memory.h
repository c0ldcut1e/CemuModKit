#pragma once

#include "../memory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMemory
{
    BOOL (*OSGetSharedData)(OSSharedDataType type, uint32_t unk_r4, void **outPtr, uint32_t *outSize);
    void (*__OSRootLoadShared)(void);
    void *(*OSBlockMove)(void *dst, const void *src, uint32_t size, BOOL flush);
    void *(*OSBlockSet)(void *dst, uint8_t val, uint32_t size);
    void *(*OSAllocFromSystem)(uint32_t size, int align);
    void (*OSFreeToSystem)(void *ptr);
    BOOL (*OSGetForegroundBucket)(uint32_t *outAddr, uint32_t *outSize);
    BOOL (*OSGetForegroundBucketFreeArea)(uint32_t *outAddr, uint32_t *outSize);
    int (*OSGetMemBound)(OSMemoryType type, uint32_t *outAddr, uint32_t *outSize);
    void (*__OSZeroProcessMemory)(uint32_t processID);
} ImportsCoreInitMemory;

#ifdef __cplusplus
}
#endif
