#pragma once

#include "../swap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Swap
{
    void (*GX2CopyColorBufferToScanBuffer)(const GX2ColorBuffer *buffer, GX2ScanTarget scanTarget);
    void (*GX2GetCurrentScanBuffer)(GX2ScanTarget scanTarget, GX2ColorBuffer *buffer);
    void (*GX2SwapScanBuffers)(void);
    BOOL (*GX2GetLastFrame)(GX2ScanTarget scanTarget, GX2Texture *texture);
    BOOL (*GX2GetLastFrameGamma)(GX2ScanTarget scanTarget, float *gammaOut);
    uint32_t (*GX2GetSwapInterval)(void);
    void (*GX2SetSwapInterval)(uint32_t interval);
} ImportsGX2Swap;

#ifdef __cplusplus
}
#endif
