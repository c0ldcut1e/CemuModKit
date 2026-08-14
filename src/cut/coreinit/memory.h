#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSMemoryType
{
    OS_MEM1 = 1,
    OS_MEM2 = 2,
} OSMemoryType;

typedef enum OSSharedDataType
{
    OS_SHAREDDATATYPE_FONT_CHINESE   = 0,
    OS_SHAREDDATATYPE_FONT_KOREAN    = 1,
    OS_SHAREDDATATYPE_FONT_STANDARD  = 2,
    OS_SHAREDDATATYPE_FONT_TAIWANESE = 3,
    OS_SHAREDDATATYPE_FONT_MAX       = 4,
} OSSharedDataType;

CUT_IMPORT BOOL (*OSGetSharedData)(OSSharedDataType type, uint32_t unk_r4, void **outPtr, uint32_t *outSize);

CUT_IMPORT void (*__OSRootLoadShared)();

CUT_IMPORT void *(*OSBlockMove)(void *dst, const void *src, uint32_t size, BOOL flush);

CUT_IMPORT void *(*OSBlockSet)(void *dst, uint8_t val, uint32_t size);

CUT_IMPORT void *(*OSAllocFromSystem)(uint32_t size, int align);

CUT_IMPORT void (*OSFreeToSystem)(void *ptr);

CUT_IMPORT BOOL (*OSGetForegroundBucket)(uint32_t *outAddr, uint32_t *outSize);

CUT_IMPORT BOOL (*OSGetForegroundBucketFreeArea)(uint32_t *outAddr, uint32_t *outSize);

CUT_IMPORT int (*OSGetMemBound)(OSMemoryType type, uint32_t *outAddr, uint32_t *outSize);

CUT_IMPORT void (*__OSZeroProcessMemory)(uint32_t processID);

#ifdef __cplusplus
}
#endif
