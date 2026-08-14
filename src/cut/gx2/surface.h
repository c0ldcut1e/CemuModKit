#pragma once
#include "../cut.h"
#include "enum.h"
#include <gx2r/resource.h>

/**
 * \defgroup gx2_surface Surface
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2Surface GX2Surface;
typedef struct GX2DepthBuffer GX2DepthBuffer;
typedef struct GX2ColorBuffer GX2ColorBuffer;
typedef struct GX2Rect GX2Rect;
typedef struct GX2Point GX2Point;

struct GX2Surface
{
    GX2SurfaceDim dim;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t mipLevels;
    GX2SurfaceFormat format;
    GX2AAMode aa;
    union
    {
        GX2SurfaceUse use;
        GX2RResourceFlags resourceFlags;
    };
    uint32_t imageSize;
    void *image;
    uint32_t mipmapSize;
    void *mipmaps;
    GX2TileMode tileMode;
    uint32_t swizzle;
    uint32_t alignment;
    uint32_t pitch;
    uint32_t mipLevelOffset[13];
};
CUT_CHECK_OFFSET(GX2Surface, 0x0, dim);
CUT_CHECK_OFFSET(GX2Surface, 0x4, width);
CUT_CHECK_OFFSET(GX2Surface, 0x8, height);
CUT_CHECK_OFFSET(GX2Surface, 0xc, depth);
CUT_CHECK_OFFSET(GX2Surface, 0x10, mipLevels);
CUT_CHECK_OFFSET(GX2Surface, 0x14, format);
CUT_CHECK_OFFSET(GX2Surface, 0x18, aa);
CUT_CHECK_OFFSET(GX2Surface, 0x1c, use);
CUT_CHECK_OFFSET(GX2Surface, 0x1c, resourceFlags);
CUT_CHECK_OFFSET(GX2Surface, 0x20, imageSize);
CUT_CHECK_OFFSET(GX2Surface, 0x24, image);
CUT_CHECK_OFFSET(GX2Surface, 0x28, mipmapSize);
CUT_CHECK_OFFSET(GX2Surface, 0x2c, mipmaps);
CUT_CHECK_OFFSET(GX2Surface, 0x30, tileMode);
CUT_CHECK_OFFSET(GX2Surface, 0x34, swizzle);
CUT_CHECK_OFFSET(GX2Surface, 0x38, alignment);
CUT_CHECK_OFFSET(GX2Surface, 0x3C, pitch);
CUT_CHECK_OFFSET(GX2Surface, 0x40, mipLevelOffset);
CUT_CHECK_SIZE(GX2Surface, 0x74);

struct GX2DepthBuffer
{
    GX2Surface surface;

    uint32_t viewMip;
    uint32_t viewFirstSlice;
    uint32_t viewNumSlices;
    void *hiZPtr;
    uint32_t hiZSize;
    float depthClear;
    uint32_t stencilClear;

    uint32_t regs[7];
};
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x74, viewMip);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x78, viewFirstSlice);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x7C, viewNumSlices);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x80, hiZPtr);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x84, hiZSize);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x88, depthClear);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x8C, stencilClear);
CUT_CHECK_OFFSET(GX2DepthBuffer, 0x90, regs);
CUT_CHECK_SIZE(GX2DepthBuffer, 0xAC);

struct GX2ColorBuffer
{
    GX2Surface surface;

    uint32_t viewMip;
    uint32_t viewFirstSlice;
    uint32_t viewNumSlices;
    void *aaBuffer;
    uint32_t aaSize;

    uint32_t regs[5];
};
CUT_CHECK_OFFSET(GX2ColorBuffer, 0x74, viewMip);
CUT_CHECK_OFFSET(GX2ColorBuffer, 0x78, viewFirstSlice);
CUT_CHECK_OFFSET(GX2ColorBuffer, 0x7C, viewNumSlices);
CUT_CHECK_OFFSET(GX2ColorBuffer, 0x80, aaBuffer);
CUT_CHECK_OFFSET(GX2ColorBuffer, 0x84, aaSize);
CUT_CHECK_OFFSET(GX2ColorBuffer, 0x88, regs);
CUT_CHECK_SIZE(GX2ColorBuffer, 0x9C);

struct GX2Rect
{
    int left;
    int top;
    int right;
    int bottom;
};
CUT_CHECK_OFFSET(GX2Rect, 0x0, left);
CUT_CHECK_OFFSET(GX2Rect, 0x4, top);
CUT_CHECK_OFFSET(GX2Rect, 0x8, right);
CUT_CHECK_OFFSET(GX2Rect, 0xc, bottom);
CUT_CHECK_SIZE(GX2Rect, 0x10);

struct GX2Point
{
    int x;
    int y;
};
CUT_CHECK_OFFSET(GX2Point, 0x0, x);
CUT_CHECK_OFFSET(GX2Point, 0x4, y);
CUT_CHECK_SIZE(GX2Point, 0x8);

CUT_IMPORT void (*GX2CalcSurfaceSizeAndAlignment)(GX2Surface *surface);

CUT_IMPORT void (*GX2CalcDepthBufferHiZInfo)(GX2DepthBuffer *depthBuffer, uint32_t *outSize, uint32_t *outAlignment);

CUT_IMPORT void (*GX2CalcColorBufferAuxInfo)(GX2ColorBuffer *surface, uint32_t *outSize, uint32_t *outAlignment);

CUT_IMPORT void (*GX2SetColorBuffer)(const GX2ColorBuffer *colorBuffer, GX2RenderTarget target);

CUT_IMPORT void (*GX2SetDepthBuffer)(const GX2DepthBuffer *depthBuffer);

CUT_IMPORT void (*GX2InitColorBufferRegs)(GX2ColorBuffer *colorBuffer);

CUT_IMPORT void (*GX2InitDepthBufferRegs)(GX2DepthBuffer *depthBuffer);

CUT_IMPORT void (*GX2InitDepthBufferHiZEnable)(GX2DepthBuffer *depthBuffer, BOOL enable);

CUT_IMPORT uint32_t (*GX2GetSurfaceSwizzle)(const GX2Surface *surface);

CUT_IMPORT void (*GX2SetSurfaceSwizzle)(GX2Surface *surface, uint32_t swizzle);

CUT_IMPORT void (*GX2CopySurface)(const GX2Surface *src, uint32_t srcLevel, uint32_t srcDepth, GX2Surface *dst, uint32_t dstLevel, uint32_t dstDepth);

CUT_IMPORT void (*GX2CopySurfaceEx)(const GX2Surface *src, uint32_t srcLevel, uint32_t srcDepth, GX2Surface *dst, uint32_t dstLevel,
                                    uint32_t dstDepth, uint32_t numRects, GX2Rect *srcRects, GX2Point *dstPoints);

CUT_IMPORT void (*GX2ResolveAAColorBuffer)(const GX2ColorBuffer *srcColorBuffer, GX2Surface *dstSurface, uint32_t dstMip, uint32_t dstSlice);

#ifdef __cplusplus
}
#endif

/** @} */
