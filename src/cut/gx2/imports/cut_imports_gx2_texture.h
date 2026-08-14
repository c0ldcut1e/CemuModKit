#pragma once

#include "../texture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Texture
{
    void (*GX2InitTextureRegs)(GX2Texture *texture);
    void (*GX2SetPixelTexture)(const GX2Texture *texture, uint32_t unit);
    void (*GX2SetVertexTexture)(const GX2Texture *texture, uint32_t unit);
    void (*GX2SetGeometryTexture)(const GX2Texture *texture, uint32_t unit);
} ImportsGX2Texture;

#ifdef __cplusplus
}
#endif
