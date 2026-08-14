#pragma once

#include "../clear.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Clear
{
    void (*GX2ClearColor)(GX2ColorBuffer *colorBuffer, float red, float green, float blue, float alpha);
    void (*GX2ClearDepthStencilEx)(GX2DepthBuffer *depthBuffer, float depth, uint8_t stencil, GX2ClearFlags clearMode);
    void (*GX2ClearBuffersEx)(GX2ColorBuffer *colorBuffer, GX2DepthBuffer *depthBuffer, float red, float green, float blue, float alpha, float depth,
                              uint8_t stencil, GX2ClearFlags clearMode);
    void (*GX2SetClearDepth)(GX2DepthBuffer *depthBuffer, float depth);
    void (*GX2SetClearStencil)(GX2DepthBuffer *depthBuffer, uint8_t stencil);
    void (*GX2SetClearDepthStencil)(GX2DepthBuffer *depthBuffer, float depth, uint8_t stencil);
} ImportsGX2Clear;

#ifdef __cplusplus
}
#endif
