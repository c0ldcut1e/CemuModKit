#pragma once

#include "../displaylist.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2DisplayList
{
    void (*GX2BeginDisplayListEx)(void *displayList, uint32_t bytes, BOOL unk1);
    uint32_t (*GX2EndDisplayList)(void *displayList);
    void (*GX2DirectCallDisplayList)(const void *displayList, uint32_t bytes);
    void (*GX2CallDisplayList)(const void *displayList, uint32_t bytes);
    BOOL (*GX2GetDisplayListWriteStatus)(void);
    BOOL (*GX2GetCurrentDisplayList)(void **outDisplayList, uint32_t *outSize);
    void (*GX2CopyDisplayList)(const void *displayList, uint32_t bytes);
} ImportsGX2DisplayList;

#ifdef __cplusplus
}
#endif
