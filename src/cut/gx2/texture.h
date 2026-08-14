#pragma once
#include "../cut.h"
#include "surface.h"

/**
 * \defgroup gx2_texture Texture
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2Texture GX2Texture;

struct GX2Texture
{
    GX2Surface surface;
    uint32_t viewFirstMip;
    uint32_t viewNumMips;
    uint32_t viewFirstSlice;
    uint32_t viewNumSlices;
    uint32_t compMap;

    uint32_t regs[5];
};
CUT_CHECK_OFFSET(GX2Texture, 0x0, surface);
CUT_CHECK_OFFSET(GX2Texture, 0x74, viewFirstMip);
CUT_CHECK_OFFSET(GX2Texture, 0x78, viewNumMips);
CUT_CHECK_OFFSET(GX2Texture, 0x7c, viewFirstSlice);
CUT_CHECK_OFFSET(GX2Texture, 0x80, viewNumSlices);
CUT_CHECK_OFFSET(GX2Texture, 0x84, compMap);
CUT_CHECK_OFFSET(GX2Texture, 0x88, regs);
CUT_CHECK_SIZE(GX2Texture, 0x9c);

CUT_IMPORT void (*GX2InitTextureRegs)(GX2Texture *texture);

CUT_IMPORT void (*GX2SetPixelTexture)(const GX2Texture *texture, uint32_t unit);

CUT_IMPORT void (*GX2SetVertexTexture)(const GX2Texture *texture, uint32_t unit);

CUT_IMPORT void (*GX2SetGeometryTexture)(const GX2Texture *texture, uint32_t unit);

#ifdef __cplusplus
}
#endif

/** @} */
