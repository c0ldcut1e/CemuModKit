#pragma once
#include "../cut.h"
#include "enum.h"

/**
 * \defgroup gx2_swap Swap
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2ColorBuffer GX2ColorBuffer;
typedef struct GX2Texture GX2Texture;

CUT_IMPORT void (*GX2CopyColorBufferToScanBuffer)(const GX2ColorBuffer *buffer, GX2ScanTarget scanTarget);

CUT_IMPORT void (*GX2GetCurrentScanBuffer)(GX2ScanTarget scanTarget, GX2ColorBuffer *buffer);

CUT_IMPORT void (*GX2SwapScanBuffers)(void);

CUT_IMPORT BOOL (*GX2GetLastFrame)(GX2ScanTarget scanTarget, GX2Texture *texture);

CUT_IMPORT BOOL (*GX2GetLastFrameGamma)(GX2ScanTarget scanTarget, float *gammaOut);

CUT_IMPORT uint32_t (*GX2GetSwapInterval)(void);

CUT_IMPORT void (*GX2SetSwapInterval)(uint32_t interval);

#ifdef __cplusplus
}
#endif

/** @} */
