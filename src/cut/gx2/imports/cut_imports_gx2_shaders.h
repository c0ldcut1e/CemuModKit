#pragma once

#include "../shaders.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Shaders
{
    uint32_t (*GX2CalcGeometryShaderInputRingBufferSize)(uint32_t ringItemSize);
    uint32_t (*GX2CalcGeometryShaderOutputRingBufferSize)(uint32_t ringItemSize);
    uint32_t (*GX2CalcFetchShaderSizeEx)(uint32_t attribs, GX2FetchShaderType fetchShaderType, GX2TessellationMode tesellationMode);
    void (*GX2InitFetchShaderEx)(GX2FetchShader *fetchShader, uint8_t *buffer, uint32_t attribCount, const GX2AttribStream *attribs,
                                 GX2FetchShaderType type, GX2TessellationMode tessMode);
    void (*GX2SetFetchShader)(const GX2FetchShader *shader);
    void (*GX2SetVertexShader)(const GX2VertexShader *shader);
    void (*GX2SetPixelShader)(const GX2PixelShader *shader);
    void (*GX2SetGeometryShader)(const GX2GeometryShader *shader);
    void (*GX2SetVertexSampler)(const GX2Sampler *sampler, uint32_t id);
    void (*GX2SetPixelSampler)(const GX2Sampler *sampler, uint32_t id);
    void (*GX2SetGeometrySampler)(const GX2Sampler *sampler, uint32_t id);
    void (*GX2SetVertexUniformReg)(uint32_t offset, uint32_t count, const void *data);
    void (*GX2SetPixelUniformReg)(uint32_t offset, uint32_t count, const void *data);
    void (*GX2SetVertexUniformBlock)(uint32_t location, uint32_t size, const void *data);
    void (*GX2SetPixelUniformBlock)(uint32_t location, uint32_t size, const void *data);
    void (*GX2SetGeometryUniformBlock)(uint32_t location, uint32_t size, const void *data);
    void (*GX2SetShaderModeEx)(GX2ShaderMode mode, uint32_t numVsGpr, uint32_t numVsStackEntries, uint32_t numGsGpr, uint32_t numGsStackEntries,
                               uint32_t numPsGpr, uint32_t numPsStackEntries);
    void (*GX2SetStreamOutEnable)(BOOL enable);
    void (*GX2SetGeometryShaderInputRingBuffer)(const void *buffer, uint32_t size);
    void (*GX2SetGeometryShaderOutputRingBuffer)(void *buffer, uint32_t size);
    uint32_t (*GX2GetPixelShaderGPRs)(const GX2PixelShader *shader);
    uint32_t (*GX2GetPixelShaderStackEntries)(const GX2PixelShader *shader);
    uint32_t (*GX2GetVertexShaderGPRs)(const GX2VertexShader *shader);
    uint32_t (*GX2GetVertexShaderStackEntries)(const GX2VertexShader *shader);
    uint32_t (*GX2GetGeometryShaderGPRs)(const GX2GeometryShader *shader);
    uint32_t (*GX2GetGeometryShaderStackEntries)(const GX2GeometryShader *shader);
} ImportsGX2Shaders;

#ifdef __cplusplus
}
#endif
