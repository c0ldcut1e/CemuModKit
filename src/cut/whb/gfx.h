#pragma once

#include "../cut.h"
#include "../gx2/context.h"
#include "../gx2/shaders.h"
#include "../gx2/texture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WHBGfxShaderGroup WHBGfxShaderGroup;

struct WHBGfxShaderGroup
{
    GX2FetchShader fetchShader;
    void *fetchShaderProgram;
    GX2PixelShader *pixelShader;
    GX2VertexShader *vertexShader;
    uint32_t numAttributes;
    GX2AttribStream attributes[16];
};

BOOL WHBGfxInit(void);
void WHBGfxShutdown(void);

void WHBGfxBeginRender(void);
void WHBGfxFinishRender(void);
void WHBGfxClearColor(float r, float g, float b, float a);

void WHBGfxBeginRenderDRC(void);
void WHBGfxFinishRenderDRC(void);
void WHBGfxBeginRenderTV(void);
void WHBGfxFinishRenderTV(void);

GX2PixelShader *WHBGfxLoadGFDPixelShader(uint32_t index, const void *file);
BOOL WHBGfxFreePixelShader(GX2PixelShader *shader);
GX2VertexShader *WHBGfxLoadGFDVertexShader(uint32_t index, const void *file);
BOOL WHBGfxFreeVertexShader(GX2VertexShader *shader);

BOOL WHBGfxLoadGFDShaderGroup(WHBGfxShaderGroup *group, uint32_t index, const void *file);
BOOL WHBGfxInitShaderAttribute(WHBGfxShaderGroup *group, const char *name, uint32_t buffer, uint32_t offset, GX2AttribFormat format);
BOOL WHBGfxInitFetchShader(WHBGfxShaderGroup *group);
BOOL WHBGfxFreeShaderGroup(WHBGfxShaderGroup *group);

GX2Texture *WHBGfxLoadGFDTexture(uint32_t index, const void *file);
BOOL WHBGfxFreeTexture(GX2Texture *texture);

GX2ColorBuffer *WHBGfxGetTVColourBuffer(void);
GX2DepthBuffer *WHBGfxGetTVDepthBuffer(void);
GX2ContextState *WHBGfxGetTVContextState(void);
GX2ColorBuffer *WHBGfxGetDRCColourBuffer(void);
GX2DepthBuffer *WHBGfxGetDRCDepthBuffer(void);
GX2ContextState *WHBGfxGetDRCContextState(void);

#ifdef __cplusplus
}
#endif
