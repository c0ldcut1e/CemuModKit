#pragma once
#include "../cut.h"
#include "enum.h"

/**
 * \defgroup gx2_sampler Sampler
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2Sampler GX2Sampler;

struct GX2Sampler
{
    uint32_t regs[3];
};
CUT_CHECK_SIZE(GX2Sampler, 12);

CUT_IMPORT void (*GX2InitSampler)(GX2Sampler *sampler, GX2TexClampMode clampMode, GX2TexXYFilterMode minMagFilterMode);

CUT_IMPORT void (*GX2InitSamplerBorderType)(GX2Sampler *sampler, GX2TexBorderType borderType);

CUT_IMPORT void (*GX2InitSamplerClamping)(GX2Sampler *sampler, GX2TexClampMode clampX, GX2TexClampMode clampY, GX2TexClampMode clampZ);

CUT_IMPORT void (*GX2InitSamplerDepthCompare)(GX2Sampler *sampler, GX2CompareFunction depthCompare);

CUT_IMPORT void (*GX2InitSamplerFilterAdjust)(GX2Sampler *sampler, BOOL highPrecision, GX2TexMipPerfMode perfMip, GX2TexZPerfMode perfZ);

CUT_IMPORT void (*GX2InitSamplerLOD)(GX2Sampler *sampler, float lodMin, float lodMax, float lodBias);

CUT_IMPORT void (*GX2InitSamplerLODAdjust)(GX2Sampler *sampler, float unk1, BOOL unk2);

CUT_IMPORT void (*GX2InitSamplerRoundingMode)(GX2Sampler *sampler, GX2RoundingMode roundingMode);

CUT_IMPORT void (*GX2InitSamplerXYFilter)(GX2Sampler *sampler, GX2TexXYFilterMode filterMag, GX2TexXYFilterMode filterMin, GX2TexAnisoRatio maxAniso);

CUT_IMPORT void (*GX2InitSamplerZMFilter)(GX2Sampler *sampler, GX2TexZFilterMode filterZ, GX2TexMipFilterMode filterMip);

#ifdef __cplusplus
}
#endif

/** @} */
