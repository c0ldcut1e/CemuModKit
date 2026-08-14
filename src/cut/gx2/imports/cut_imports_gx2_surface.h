#pragma once

#include "../surface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Surface
{
    void (*GX2CalcSurfaceSizeAndAlignment)(GX2Surface *surface);
    void (*GX2CalcDepthBufferHiZInfo)(GX2DepthBuffer *depthBuffer, uint32_t *outSize, uint32_t *outAlignment);
    void (*GX2CalcColorBufferAuxInfo)(GX2ColorBuffer *surface, uint32_t *outSize, uint32_t *outAlignment);
    void (*GX2SetColorBuffer)(const GX2ColorBuffer *colorBuffer, GX2RenderTarget target);
    void (*GX2SetDepthBuffer)(const GX2DepthBuffer *depthBuffer);
    void (*GX2InitColorBufferRegs)(GX2ColorBuffer *colorBuffer);
    void (*GX2InitDepthBufferRegs)(GX2DepthBuffer *depthBuffer);
    void (*GX2InitDepthBufferHiZEnable)(GX2DepthBuffer *depthBuffer, BOOL enable);
    uint32_t (*GX2GetSurfaceSwizzle)(const GX2Surface *surface);
    void (*GX2SetSurfaceSwizzle)(GX2Surface *surface, uint32_t swizzle);
    void (*GX2CopySurface)(const GX2Surface *src, uint32_t srcLevel, uint32_t srcDepth, GX2Surface *dst, uint32_t dstLevel, uint32_t dstDepth);
    void (*GX2CopySurfaceEx)(const GX2Surface *src, uint32_t srcLevel, uint32_t srcDepth, GX2Surface *dst, uint32_t dstLevel, uint32_t dstDepth,
                             uint32_t numRects, GX2Rect *srcRects, GX2Point *dstPoints);
    void (*GX2ResolveAAColorBuffer)(const GX2ColorBuffer *srcColorBuffer, GX2Surface *dstSurface, uint32_t dstMip, uint32_t dstSlice);
} ImportsGX2Surface;

#ifdef __cplusplus
}
#endif
