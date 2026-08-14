#include "gfx.h"

#include "../coreinit/memdefaultheap.h"
#include "../gfd/gfd.h"
#include "../gx2/clear.h"
#include "../gx2/display.h"
#include "../gx2/event.h"
#include "../gx2/mem.h"
#include "../gx2/registers.h"
#include "../gx2/state.h"
#include "../gx2/surface.h"
#include "../gx2/swap.h"
#include "../gx2/utils.h"
#include <string.h>

#define WHB_GFX_COMMAND_BUFFER_POOL_SIZE (0x400000)

static void *sCommandBufferPool;
static void *sDrcScanBuffer;
static uint32_t sDrcScanBufferSize;
static GX2DrcRenderMode sDrcRenderMode;
static GX2SurfaceFormat sDrcSurfaceFormat;
static void *sTvScanBuffer;
static uint32_t sTvScanBufferSize;
static GX2TVRenderMode sTvRenderMode;
static GX2SurfaceFormat sTvSurfaceFormat;
static GX2ColorBuffer sTvColourBuffer;
static GX2DepthBuffer sTvDepthBuffer;
static GX2ColorBuffer sDrcColourBuffer;
static GX2DepthBuffer sDrcDepthBuffer;
static GX2ContextState *sTvContextState;
static GX2ContextState *sDrcContextState;
static BOOL sDrawingTv;
static BOOL sGpuTimedOut;
static BOOL sGx2Initialized;

static void *WHBGfxAlloc(uint32_t size, uint32_t alignment)
{
    if (alignment < 4)
    {
        alignment = 4;
    }

    return MEMAllocFromDefaultHeapEx(size, (int) alignment);
}

static void WHBGfxFree(void *block)
{
    if (block)
    {
        MEMFreeToDefaultHeap(block);
    }
}

static void WHBGfxInitColourBuffer(GX2ColorBuffer *cb, uint32_t width, uint32_t height, GX2SurfaceFormat format, GX2AAMode aa)
{
    memset(cb, 0, sizeof(*cb));
    cb->surface.use       = GX2_SURFACE_USE_TEXTURE_COLOR_BUFFER_TV;
    cb->surface.dim       = GX2_SURFACE_DIM_TEXTURE_2D;
    cb->surface.width     = width;
    cb->surface.height    = height;
    cb->surface.depth     = 1;
    cb->surface.mipLevels = 1;
    cb->surface.format    = format;
    cb->surface.aa        = aa;
    cb->surface.tileMode  = GX2_TILE_MODE_DEFAULT;
    cb->viewNumSlices     = 1;
    GX2CalcSurfaceSizeAndAlignment(&cb->surface);
    GX2InitColorBufferRegs(cb);
}

static void WHBGfxInitDepthBuffer(GX2DepthBuffer *db, uint32_t width, uint32_t height, GX2SurfaceFormat format, GX2AAMode aa)
{
    memset(db, 0, sizeof(*db));

    if (format == GX2_SURFACE_FORMAT_UNORM_R24_X8 || format == GX2_SURFACE_FORMAT_FLOAT_D24_S8)
    {
        db->surface.use = GX2_SURFACE_USE_DEPTH_BUFFER;
    }
    else
    {
        db->surface.use = GX2_SURFACE_USE_DEPTH_BUFFER | GX2_SURFACE_USE_TEXTURE;
    }

    db->surface.dim       = GX2_SURFACE_DIM_TEXTURE_2D;
    db->surface.width     = width;
    db->surface.height    = height;
    db->surface.depth     = 1;
    db->surface.mipLevels = 1;
    db->surface.format    = format;
    db->surface.aa        = aa;
    db->surface.tileMode  = GX2_TILE_MODE_DEFAULT;
    db->viewNumSlices     = 1;
    db->depthClear        = 1.0f;
    GX2CalcSurfaceSizeAndAlignment(&db->surface);
    GX2InitDepthBufferRegs(db);
}

static BOOL WHBGfxAllocateSurface(GX2Surface *surface, GX2InvalidateMode invalidateMode)
{
    surface->image = WHBGfxAlloc(surface->imageSize, surface->alignment);
    if (!surface->image)
    {
        return FALSE;
    }

    GX2Invalidate(invalidateMode, surface->image, surface->imageSize);
    return TRUE;
}

static BOOL WHBGfxAllocateBuffers(void)
{
    sTvScanBuffer = WHBGfxAlloc(sTvScanBufferSize, GX2_SCAN_BUFFER_ALIGNMENT);
    if (!sTvScanBuffer)
    {
        return FALSE;
    }
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sTvScanBuffer, sTvScanBufferSize);
    GX2SetTVBuffer(sTvScanBuffer, sTvScanBufferSize, sTvRenderMode, sTvSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE);

    if (!WHBGfxAllocateSurface(&sTvColourBuffer.surface, GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_COLOR_BUFFER) ||
        !WHBGfxAllocateSurface(&sTvDepthBuffer.surface, GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_DEPTH_BUFFER))
    {
        return FALSE;
    }

    sDrcScanBuffer = WHBGfxAlloc(sDrcScanBufferSize, GX2_SCAN_BUFFER_ALIGNMENT);
    if (!sDrcScanBuffer)
    {
        return FALSE;
    }
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sDrcScanBuffer, sDrcScanBufferSize);
    GX2SetDRCBuffer(sDrcScanBuffer, sDrcScanBufferSize, sDrcRenderMode, sDrcSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE);

    return WHBGfxAllocateSurface(&sDrcColourBuffer.surface, GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_COLOR_BUFFER) &&
           WHBGfxAllocateSurface(&sDrcDepthBuffer.surface, GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_DEPTH_BUFFER);
}

static void WHBGfxFreeBuffers(void)
{
    WHBGfxFree(sTvScanBuffer);
    sTvScanBuffer = NULL;
    WHBGfxFree(sTvColourBuffer.surface.image);
    sTvColourBuffer.surface.image = NULL;
    WHBGfxFree(sTvDepthBuffer.surface.image);
    sTvDepthBuffer.surface.image = NULL;

    WHBGfxFree(sDrcScanBuffer);
    sDrcScanBuffer = NULL;
    WHBGfxFree(sDrcColourBuffer.surface.image);
    sDrcColourBuffer.surface.image = NULL;
    WHBGfxFree(sDrcDepthBuffer.surface.image);
    sDrcDepthBuffer.surface.image = NULL;
}

static void WHBGfxChooseTVMode(uint32_t *outWidth, uint32_t *outHeight)
{
    switch (GX2GetSystemTVScanMode())
    {
        case GX2_TV_SCAN_MODE_480I:
        case GX2_TV_SCAN_MODE_480P:
            if (GX2GetSystemTVAspectRatio() == GX2_ASPECT_RATIO_16_9)
            {
                sTvRenderMode = GX2_TV_RENDER_MODE_WIDE_480P;
                *outWidth     = 854;
            }
            else
            {
                sTvRenderMode = GX2_TV_RENDER_MODE_STANDARD_480P;
                *outWidth     = 640;
            }
            *outHeight = 480;
            break;
        case GX2_TV_SCAN_MODE_1080I:
        case GX2_TV_SCAN_MODE_1080P:
            sTvRenderMode = GX2_TV_RENDER_MODE_WIDE_1080P;
            *outWidth     = 1920;
            *outHeight    = 1080;
            break;
        case GX2_TV_SCAN_MODE_720P:
        default:
            sTvRenderMode = GX2_TV_RENDER_MODE_WIDE_720P;
            *outWidth     = 1280;
            *outHeight    = 720;
            break;
    }
}

BOOL WHBGfxInit(void)
{
    uint32_t drcWidth  = 854;
    uint32_t drcHeight = 480;
    uint32_t tvWidth;
    uint32_t tvHeight;
    uint32_t unk;

    sCommandBufferPool = WHBGfxAlloc(WHB_GFX_COMMAND_BUFFER_POOL_SIZE, GX2_COMMAND_BUFFER_ALIGNMENT);
    if (!sCommandBufferPool)
    {
        goto error;
    }

    uint32_t initAttribs[] = {GX2_INIT_CMD_BUF_BASE,
                              (uintptr_t) sCommandBufferPool,
                              GX2_INIT_CMD_BUF_POOL_SIZE,
                              WHB_GFX_COMMAND_BUFFER_POOL_SIZE,
                              GX2_INIT_ARGC,
                              0,
                              GX2_INIT_ARGV,
                              0,
                              GX2_INIT_END};
    GX2Init(initAttribs);
    sGx2Initialized = TRUE;

    sDrcRenderMode    = GX2GetSystemDRCMode();
    sTvSurfaceFormat  = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
    sDrcSurfaceFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
    WHBGfxChooseTVMode(&tvWidth, &tvHeight);

    GX2CalcTVSize(sTvRenderMode, sTvSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE, &sTvScanBufferSize, &unk);
    GX2CalcDRCSize(sDrcRenderMode, sDrcSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE, &sDrcScanBufferSize, &unk);

    WHBGfxInitColourBuffer(&sTvColourBuffer, tvWidth, tvHeight, sTvSurfaceFormat, GX2_AA_MODE1X);
    WHBGfxInitDepthBuffer(&sTvDepthBuffer, tvWidth, tvHeight, GX2_SURFACE_FORMAT_FLOAT_R32, GX2_AA_MODE1X);
    WHBGfxInitColourBuffer(&sDrcColourBuffer, drcWidth, drcHeight, sDrcSurfaceFormat, GX2_AA_MODE1X);
    WHBGfxInitDepthBuffer(&sDrcDepthBuffer, drcWidth, drcHeight, GX2_SURFACE_FORMAT_FLOAT_R32, GX2_AA_MODE1X);

    if (!WHBGfxAllocateBuffers())
    {
        goto error;
    }

    sTvContextState = WHBGfxAlloc(sizeof(GX2ContextState), GX2_CONTEXT_STATE_ALIGNMENT);
    if (!sTvContextState)
    {
        goto error;
    }
    GX2SetupContextStateEx(sTvContextState, TRUE);
    GX2SetContextState(sTvContextState);
    GX2SetColorBuffer(&sTvColourBuffer, GX2_RENDER_TARGET_0);
    GX2SetDepthBuffer(&sTvDepthBuffer);
    GX2SetViewport(0, 0, (float) sTvColourBuffer.surface.width, (float) sTvColourBuffer.surface.height, 0.0f, 1.0f);
    GX2SetScissor(0, 0, sTvColourBuffer.surface.width, sTvColourBuffer.surface.height);
    GX2SetTVScale(sTvColourBuffer.surface.width, sTvColourBuffer.surface.height);

    sDrcContextState = WHBGfxAlloc(sizeof(GX2ContextState), GX2_CONTEXT_STATE_ALIGNMENT);
    if (!sDrcContextState)
    {
        goto error;
    }
    GX2SetupContextStateEx(sDrcContextState, TRUE);
    GX2SetContextState(sDrcContextState);
    GX2SetColorBuffer(&sDrcColourBuffer, GX2_RENDER_TARGET_0);
    GX2SetDepthBuffer(&sDrcDepthBuffer);
    GX2SetViewport(0, 0, (float) sDrcColourBuffer.surface.width, (float) sDrcColourBuffer.surface.height, 0.0f, 1.0f);
    GX2SetScissor(0, 0, sDrcColourBuffer.surface.width, sDrcColourBuffer.surface.height);
    GX2SetDRCScale(sDrcColourBuffer.surface.width, sDrcColourBuffer.surface.height);
    GX2SetSwapInterval(1);

    return TRUE;

error:
    WHBGfxShutdown();
    return FALSE;
}

void WHBGfxShutdown(void)
{
    if (!sGx2Initialized)
    {
        WHBGfxFreeBuffers();
        WHBGfxFree(sTvContextState);
        sTvContextState = NULL;
        WHBGfxFree(sDrcContextState);
        sDrcContextState = NULL;
        WHBGfxFree(sCommandBufferPool);
        sCommandBufferPool = NULL;
        return;
    }

    if (sGpuTimedOut)
    {
        GX2ResetGPU(0);
        sGpuTimedOut = FALSE;
    }

    GX2DrawDone();
    GX2Shutdown();
    sGx2Initialized = FALSE;

    WHBGfxFreeBuffers();
    WHBGfxFree(sTvContextState);
    sTvContextState = NULL;
    WHBGfxFree(sDrcContextState);
    sDrcContextState = NULL;
    WHBGfxFree(sCommandBufferPool);
    sCommandBufferPool = NULL;
}

void WHBGfxBeginRender(void)
{
    uint32_t swapCount;
    uint32_t flipCount;
    OSTime lastFlip;
    OSTime lastVsync;
    uint32_t waitCount = 0;

    while (1)
    {
        GX2GetSwapStatus(&swapCount, &flipCount, &lastFlip, &lastVsync);
        if (flipCount >= swapCount)
        {
            break;
        }

        if (waitCount >= 10)
        {
            sGpuTimedOut = TRUE;
            break;
        }

        waitCount++;
        GX2WaitForVsync();
    }
}

void WHBGfxFinishRender(void)
{
    GX2SwapScanBuffers();
    GX2Flush();
    GX2DrawDone();
    GX2SetTVEnable(TRUE);
    GX2SetDRCEnable(TRUE);
}

void WHBGfxClearColor(float r, float g, float b, float a)
{
    if (sDrawingTv)
    {
        GX2ClearColor(&sTvColourBuffer, r, g, b, a);
        GX2ClearDepthStencilEx(&sTvDepthBuffer, sTvDepthBuffer.depthClear, sTvDepthBuffer.stencilClear,
                               GX2_CLEAR_FLAGS_DEPTH | GX2_CLEAR_FLAGS_STENCIL);
        GX2SetContextState(sTvContextState);
    }
    else
    {
        GX2ClearColor(&sDrcColourBuffer, r, g, b, a);
        GX2ClearDepthStencilEx(&sDrcDepthBuffer, sDrcDepthBuffer.depthClear, sDrcDepthBuffer.stencilClear,
                               GX2_CLEAR_FLAGS_DEPTH | GX2_CLEAR_FLAGS_STENCIL);
        GX2SetContextState(sDrcContextState);
    }
}

void WHBGfxBeginRenderDRC(void)
{
    GX2SetContextState(sDrcContextState);
    sDrawingTv = FALSE;
}

void WHBGfxFinishRenderDRC(void) { GX2CopyColorBufferToScanBuffer(&sDrcColourBuffer, GX2_SCAN_TARGET_DRC); }

void WHBGfxBeginRenderTV(void)
{
    GX2SetContextState(sTvContextState);
    sDrawingTv = TRUE;
}

void WHBGfxFinishRenderTV(void) { GX2CopyColorBufferToScanBuffer(&sTvColourBuffer, GX2_SCAN_TARGET_TV); }

GX2ColorBuffer *WHBGfxGetTVColourBuffer(void) { return &sTvColourBuffer; }

GX2DepthBuffer *WHBGfxGetTVDepthBuffer(void) { return &sTvDepthBuffer; }

GX2ContextState *WHBGfxGetTVContextState(void) { return sTvContextState; }

GX2ColorBuffer *WHBGfxGetDRCColourBuffer(void) { return &sDrcColourBuffer; }

GX2DepthBuffer *WHBGfxGetDRCDepthBuffer(void) { return &sDrcDepthBuffer; }

GX2ContextState *WHBGfxGetDRCContextState(void) { return sDrcContextState; }

GX2PixelShader *WHBGfxLoadGFDPixelShader(uint32_t index, const void *file)
{
    uint32_t headerSize;
    uint32_t programSize;
    GX2PixelShader *shader = NULL;
    void *program          = NULL;

    if (index >= GFDGetPixelShaderCount(file))
    {
        goto error;
    }

    headerSize  = GFDGetPixelShaderHeaderSize(index, file);
    programSize = GFDGetPixelShaderProgramSize(index, file);
    if (!headerSize || !programSize)
    {
        goto error;
    }

    shader  = WHBGfxAlloc(headerSize, 64);
    program = WHBGfxAlloc(programSize, GX2_SHADER_PROGRAM_ALIGNMENT);
    if (!shader || !program)
    {
        goto error;
    }

    if (!GFDGetPixelShader(shader, program, index, file))
    {
        goto error;
    }

    shader->gx2rBuffer.flags     = GX2R_RESOURCE_BIND_SHADER_PROGRAM;
    shader->gx2rBuffer.elemSize  = programSize;
    shader->gx2rBuffer.elemCount = 1;
    shader->gx2rBuffer.buffer    = program;
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, shader->program, shader->size);
    return shader;

error:
    WHBGfxFree(program);
    WHBGfxFree(shader);
    return NULL;
}

BOOL WHBGfxFreePixelShader(GX2PixelShader *shader)
{
    if (!shader)
    {
        return TRUE;
    }

    WHBGfxFree(shader->gx2rBuffer.buffer ? shader->gx2rBuffer.buffer : shader->program);
    WHBGfxFree(shader);
    return TRUE;
}

GX2VertexShader *WHBGfxLoadGFDVertexShader(uint32_t index, const void *file)
{
    uint32_t headerSize;
    uint32_t programSize;
    GX2VertexShader *shader = NULL;
    void *program           = NULL;

    if (index >= GFDGetVertexShaderCount(file))
    {
        goto error;
    }

    headerSize  = GFDGetVertexShaderHeaderSize(index, file);
    programSize = GFDGetVertexShaderProgramSize(index, file);
    if (!headerSize || !programSize)
    {
        goto error;
    }

    shader  = WHBGfxAlloc(headerSize, 64);
    program = WHBGfxAlloc(programSize, GX2_SHADER_PROGRAM_ALIGNMENT);
    if (!shader || !program)
    {
        goto error;
    }

    if (!GFDGetVertexShader(shader, program, index, file))
    {
        goto error;
    }

    shader->gx2rBuffer.flags     = GX2R_RESOURCE_BIND_SHADER_PROGRAM;
    shader->gx2rBuffer.elemSize  = programSize;
    shader->gx2rBuffer.elemCount = 1;
    shader->gx2rBuffer.buffer    = program;
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, shader->program, shader->size);
    return shader;

error:
    WHBGfxFree(program);
    WHBGfxFree(shader);
    return NULL;
}

BOOL WHBGfxFreeVertexShader(GX2VertexShader *shader)
{
    if (!shader)
    {
        return TRUE;
    }

    WHBGfxFree(shader->gx2rBuffer.buffer ? shader->gx2rBuffer.buffer : shader->program);
    WHBGfxFree(shader);
    return TRUE;
}

BOOL WHBGfxLoadGFDShaderGroup(WHBGfxShaderGroup *group, uint32_t index, const void *file)
{
    memset(group, 0, sizeof(*group));
    group->vertexShader = WHBGfxLoadGFDVertexShader(index, file);
    group->pixelShader  = WHBGfxLoadGFDPixelShader(index, file);

    if (!group->vertexShader || !group->pixelShader)
    {
        WHBGfxFreeShaderGroup(group);
        return FALSE;
    }

    return TRUE;
}

static uint32_t WHBGfxGetAttribFormatSel(GX2AttribFormat format)
{
    switch (format)
    {
        case GX2_ATTRIB_FORMAT_UNORM_8:
        case GX2_ATTRIB_FORMAT_UINT_8:
        case GX2_ATTRIB_FORMAT_SNORM_8:
        case GX2_ATTRIB_FORMAT_SINT_8:
        case GX2_ATTRIB_FORMAT_FLOAT_32:
            return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_0, GX2_SQ_SEL_0, GX2_SQ_SEL_1);
        case GX2_ATTRIB_FORMAT_UNORM_8_8:
        case GX2_ATTRIB_FORMAT_UINT_8_8:
        case GX2_ATTRIB_FORMAT_SNORM_8_8:
        case GX2_ATTRIB_FORMAT_SINT_8_8:
        case GX2_ATTRIB_FORMAT_FLOAT_32_32:
            return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_Y, GX2_SQ_SEL_0, GX2_SQ_SEL_1);
        case GX2_ATTRIB_FORMAT_FLOAT_32_32_32:
            return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_Y, GX2_SQ_SEL_Z, GX2_SQ_SEL_1);
        case GX2_ATTRIB_FORMAT_UNORM_8_8_8_8:
        case GX2_ATTRIB_FORMAT_UINT_8_8_8_8:
        case GX2_ATTRIB_FORMAT_SNORM_8_8_8_8:
        case GX2_ATTRIB_FORMAT_SINT_8_8_8_8:
        case GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32:
            return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_Y, GX2_SQ_SEL_Z, GX2_SQ_SEL_W);
        default:
            return GX2_SEL_MASK(GX2_SQ_SEL_0, GX2_SQ_SEL_0, GX2_SQ_SEL_0, GX2_SQ_SEL_1);
    }
}

static int WHBGfxGetVertexAttribVarLocation(const GX2VertexShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->attribVarCount; ++i)
    {
        if (strcmp(shader->attribVars[i].name, name) == 0)
        {
            return (int) shader->attribVars[i].location;
        }
    }

    return -1;
}

BOOL WHBGfxInitShaderAttribute(WHBGfxShaderGroup *group, const char *name, uint32_t buffer, uint32_t offset, GX2AttribFormat format)
{
    int location = WHBGfxGetVertexAttribVarLocation(group->vertexShader, name);
    GX2AttribStream *attrib;

    if (location == -1 || group->numAttributes >= 16)
    {
        return FALSE;
    }

    attrib             = &group->attributes[group->numAttributes++];
    attrib->location   = (uint32_t) location;
    attrib->buffer     = buffer;
    attrib->offset     = offset;
    attrib->format     = format;
    attrib->type       = GX2_ATTRIB_INDEX_PER_VERTEX;
    attrib->aluDivisor = 0;
    attrib->mask       = WHBGfxGetAttribFormatSel(format);
    attrib->endianSwap = GX2_ENDIAN_SWAP_DEFAULT;
    return TRUE;
}

BOOL WHBGfxInitFetchShader(WHBGfxShaderGroup *group)
{
    uint32_t size = GX2CalcFetchShaderSizeEx(group->numAttributes, GX2_FETCH_SHADER_TESSELLATION_NONE, GX2_TESSELLATION_MODE_DISCRETE);

    group->fetchShaderProgram = WHBGfxAlloc(size, GX2_SHADER_PROGRAM_ALIGNMENT);
    if (!group->fetchShaderProgram)
    {
        return FALSE;
    }

    GX2InitFetchShaderEx(&group->fetchShader, group->fetchShaderProgram, group->numAttributes, group->attributes, GX2_FETCH_SHADER_TESSELLATION_NONE,
                         GX2_TESSELLATION_MODE_DISCRETE);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, group->fetchShaderProgram, size);
    return TRUE;
}

BOOL WHBGfxFreeShaderGroup(WHBGfxShaderGroup *group)
{
    if (!group)
    {
        return TRUE;
    }

    WHBGfxFree(group->fetchShaderProgram);
    group->fetchShaderProgram = NULL;
    WHBGfxFreePixelShader(group->pixelShader);
    group->pixelShader = NULL;
    WHBGfxFreeVertexShader(group->vertexShader);
    group->vertexShader = NULL;
    return TRUE;
}

GX2Texture *WHBGfxLoadGFDTexture(uint32_t index, const void *file)
{
    uint32_t headerSize;
    uint32_t imageSize;
    uint32_t mipmapSize;
    uint32_t alignment;
    GX2Texture *texture = NULL;
    void *image         = NULL;
    void *mipmaps       = NULL;

    if (index >= GFDGetTextureCount(file))
    {
        goto error;
    }

    headerSize = GFDGetTextureHeaderSize(index, file);
    imageSize  = GFDGetTextureImageSize(index, file);
    mipmapSize = GFDGetTextureMipImageSize(index, file);
    alignment  = GFDGetTextureAlignmentSize(index, file);
    if (!alignment)
    {
        alignment = 64;
    }

    if (!headerSize || !imageSize)
    {
        goto error;
    }

    texture = WHBGfxAlloc(headerSize, 64);
    image   = WHBGfxAlloc(imageSize, alignment);
    if (mipmapSize)
    {
        mipmaps = WHBGfxAlloc(mipmapSize, alignment);
    }

    if (!texture || !image || (mipmapSize && !mipmaps))
    {
        goto error;
    }

    if (!GFDGetTexture(texture, image, mipmaps, index, file))
    {
        goto error;
    }

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, texture->surface.image, texture->surface.imageSize);
    if (texture->surface.mipmaps && texture->surface.mipmapSize)
    {
        GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, texture->surface.mipmaps, texture->surface.mipmapSize);
    }

    return texture;

error:
    WHBGfxFree(mipmaps);
    WHBGfxFree(image);
    WHBGfxFree(texture);
    return NULL;
}

BOOL WHBGfxFreeTexture(GX2Texture *texture)
{
    if (!texture)
    {
        return TRUE;
    }

    WHBGfxFree(texture->surface.mipmaps);
    WHBGfxFree(texture->surface.image);
    WHBGfxFree(texture);
    return TRUE;
}
