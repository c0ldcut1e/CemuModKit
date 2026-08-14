#pragma once
#include "../cut.h"
#include "enum.h"
#include "gx2r/buffer.h"
#include "sampler.h"
#include <string.h>

/**
 * \defgroup gx2_shader Shaders
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2AttribVar GX2AttribVar;
typedef struct GX2AttribStream GX2AttribStream;
typedef struct GX2FetchShader GX2FetchShader;
typedef struct GX2GeometryShader GX2GeometryShader;
typedef struct GX2LoopVar GX2LoopVar;
typedef struct GX2PixelShader GX2PixelShader;
typedef struct GX2SamplerVar GX2SamplerVar;
typedef struct GX2UniformBlock GX2UniformBlock;
typedef struct GX2UniformVar GX2UniformVar;
typedef struct GX2UniformInitialValue GX2UniformInitialValue;
typedef struct GX2VertexShader GX2VertexShader;

struct GX2FetchShader
{
    GX2FetchShaderType type;

    struct
    {
        uint32_t sq_pgm_resources_fs;
    } regs;

    uint32_t size;
    void *program;
    uint32_t attribCount;
    uint32_t numDivisors;
    uint32_t divisors[2];
};
CUT_CHECK_OFFSET(GX2FetchShader, 0x0, type);
CUT_CHECK_OFFSET(GX2FetchShader, 0x4, regs.sq_pgm_resources_fs);
CUT_CHECK_OFFSET(GX2FetchShader, 0x8, size);
CUT_CHECK_OFFSET(GX2FetchShader, 0xc, program);
CUT_CHECK_OFFSET(GX2FetchShader, 0x10, attribCount);
CUT_CHECK_OFFSET(GX2FetchShader, 0x14, numDivisors);
CUT_CHECK_OFFSET(GX2FetchShader, 0x18, divisors);
CUT_CHECK_SIZE(GX2FetchShader, 0x20);

struct GX2UniformBlock
{
    const char *name;
    uint32_t offset;
    uint32_t size;
};
CUT_CHECK_OFFSET(GX2UniformBlock, 0x00, name);
CUT_CHECK_OFFSET(GX2UniformBlock, 0x04, offset);
CUT_CHECK_OFFSET(GX2UniformBlock, 0x08, size);
CUT_CHECK_SIZE(GX2UniformBlock, 0x0C);

struct GX2UniformVar
{
    const char *name;
    GX2ShaderVarType type;
    uint32_t count;
    uint32_t offset;
    int block;
};
CUT_CHECK_OFFSET(GX2UniformVar, 0x00, name);
CUT_CHECK_OFFSET(GX2UniformVar, 0x04, type);
CUT_CHECK_OFFSET(GX2UniformVar, 0x08, count);
CUT_CHECK_OFFSET(GX2UniformVar, 0x0C, offset);
CUT_CHECK_OFFSET(GX2UniformVar, 0x10, block);
CUT_CHECK_SIZE(GX2UniformVar, 0x14);

struct GX2UniformInitialValue
{
    float value[4];
    uint32_t offset;
};
CUT_CHECK_OFFSET(GX2UniformInitialValue, 0x00, value);
CUT_CHECK_OFFSET(GX2UniformInitialValue, 0x10, offset);
CUT_CHECK_SIZE(GX2UniformInitialValue, 0x14);

struct GX2LoopVar
{
    uint32_t offset;
    uint32_t value;
};
CUT_CHECK_OFFSET(GX2LoopVar, 0x00, offset);
CUT_CHECK_OFFSET(GX2LoopVar, 0x04, value);
CUT_CHECK_SIZE(GX2LoopVar, 0x08);

struct GX2SamplerVar
{
    const char *name;
    GX2SamplerVarType type;
    uint32_t location;
};
CUT_CHECK_OFFSET(GX2SamplerVar, 0x00, name);
CUT_CHECK_OFFSET(GX2SamplerVar, 0x04, type);
CUT_CHECK_OFFSET(GX2SamplerVar, 0x08, location);
CUT_CHECK_SIZE(GX2SamplerVar, 0x0C);

struct GX2AttribVar
{
    const char *name;
    GX2ShaderVarType type;
    uint32_t count;
    uint32_t location;
};
CUT_CHECK_OFFSET(GX2AttribVar, 0x00, name);
CUT_CHECK_OFFSET(GX2AttribVar, 0x04, type);
CUT_CHECK_OFFSET(GX2AttribVar, 0x08, count);
CUT_CHECK_OFFSET(GX2AttribVar, 0x0C, location);
CUT_CHECK_SIZE(GX2AttribVar, 0x10);

struct GX2VertexShader
{
    struct
    {
        uint32_t sq_pgm_resources_vs;
        uint32_t vgt_primitiveid_en;
        uint32_t spi_vs_out_config;
        uint32_t num_spi_vs_out_id;
        uint32_t spi_vs_out_id[10];
        uint32_t pa_cl_vs_out_cntl;
        uint32_t sq_vtx_semantic_clear;
        uint32_t num_sq_vtx_semantic;
        uint32_t sq_vtx_semantic[32];
        uint32_t vgt_strmout_buffer_en;
        uint32_t vgt_vertex_reuse_block_cntl;
        uint32_t vgt_hos_reuse_depth;
    } regs;

    uint32_t size;
    void *program;
    GX2ShaderMode mode;

    uint32_t uniformBlockCount;
    GX2UniformBlock *uniformBlocks;

    uint32_t uniformVarCount;
    GX2UniformVar *uniformVars;

    uint32_t initialValueCount;
    GX2UniformInitialValue *initialValues;

    uint32_t loopVarCount;
    GX2LoopVar *loopVars;

    uint32_t samplerVarCount;
    GX2SamplerVar *samplerVars;

    uint32_t attribVarCount;
    GX2AttribVar *attribVars;

    uint32_t ringItemsize;

    BOOL hasStreamOut;
    uint32_t streamOutStride[4];

    GX2RBuffer gx2rBuffer;
};
CUT_CHECK_OFFSET(GX2VertexShader, 0x00, regs.sq_pgm_resources_vs);
CUT_CHECK_OFFSET(GX2VertexShader, 0x04, regs.vgt_primitiveid_en);
CUT_CHECK_OFFSET(GX2VertexShader, 0x08, regs.spi_vs_out_config);
CUT_CHECK_OFFSET(GX2VertexShader, 0x0C, regs.num_spi_vs_out_id);
CUT_CHECK_OFFSET(GX2VertexShader, 0x10, regs.spi_vs_out_id);
CUT_CHECK_OFFSET(GX2VertexShader, 0x38, regs.pa_cl_vs_out_cntl);
CUT_CHECK_OFFSET(GX2VertexShader, 0x3C, regs.sq_vtx_semantic_clear);
CUT_CHECK_OFFSET(GX2VertexShader, 0x40, regs.num_sq_vtx_semantic);
CUT_CHECK_OFFSET(GX2VertexShader, 0x44, regs.sq_vtx_semantic);
CUT_CHECK_OFFSET(GX2VertexShader, 0xC4, regs.vgt_strmout_buffer_en);
CUT_CHECK_OFFSET(GX2VertexShader, 0xC8, regs.vgt_vertex_reuse_block_cntl);
CUT_CHECK_OFFSET(GX2VertexShader, 0xCC, regs.vgt_hos_reuse_depth);
CUT_CHECK_OFFSET(GX2VertexShader, 0xD0, size);
CUT_CHECK_OFFSET(GX2VertexShader, 0xD4, program);
CUT_CHECK_OFFSET(GX2VertexShader, 0xD8, mode);
CUT_CHECK_OFFSET(GX2VertexShader, 0xDc, uniformBlockCount);
CUT_CHECK_OFFSET(GX2VertexShader, 0xE0, uniformBlocks);
CUT_CHECK_OFFSET(GX2VertexShader, 0xE4, uniformVarCount);
CUT_CHECK_OFFSET(GX2VertexShader, 0xE8, uniformVars);
CUT_CHECK_OFFSET(GX2VertexShader, 0xEc, initialValueCount);
CUT_CHECK_OFFSET(GX2VertexShader, 0xF0, initialValues);
CUT_CHECK_OFFSET(GX2VertexShader, 0xF4, loopVarCount);
CUT_CHECK_OFFSET(GX2VertexShader, 0xF8, loopVars);
CUT_CHECK_OFFSET(GX2VertexShader, 0xFc, samplerVarCount);
CUT_CHECK_OFFSET(GX2VertexShader, 0x100, samplerVars);
CUT_CHECK_OFFSET(GX2VertexShader, 0x104, attribVarCount);
CUT_CHECK_OFFSET(GX2VertexShader, 0x108, attribVars);
CUT_CHECK_OFFSET(GX2VertexShader, 0x10c, ringItemsize);
CUT_CHECK_OFFSET(GX2VertexShader, 0x110, hasStreamOut);
CUT_CHECK_OFFSET(GX2VertexShader, 0x114, streamOutStride);
CUT_CHECK_OFFSET(GX2VertexShader, 0x124, gx2rBuffer);
CUT_CHECK_SIZE(GX2VertexShader, 0x134);

struct GX2PixelShader
{
    struct
    {
        uint32_t sq_pgm_resources_ps;
        uint32_t sq_pgm_exports_ps;
        uint32_t spi_ps_in_control_0;
        uint32_t spi_ps_in_control_1;
        uint32_t num_spi_ps_input_cntl;
        uint32_t spi_ps_input_cntls[32];
        uint32_t cb_shader_mask;
        uint32_t cb_shader_control;
        uint32_t db_shader_control;
        uint32_t spi_input_z;
    } regs;

    uint32_t size;
    void *program;
    GX2ShaderMode mode;

    uint32_t uniformBlockCount;
    GX2UniformBlock *uniformBlocks;

    uint32_t uniformVarCount;
    GX2UniformVar *uniformVars;

    uint32_t initialValueCount;
    GX2UniformInitialValue *initialValues;

    uint32_t loopVarCount;
    GX2LoopVar *loopVars;

    uint32_t samplerVarCount;
    GX2SamplerVar *samplerVars;

    GX2RBuffer gx2rBuffer;
};
CUT_CHECK_OFFSET(GX2PixelShader, 0x00, regs.sq_pgm_resources_ps);
CUT_CHECK_OFFSET(GX2PixelShader, 0x04, regs.sq_pgm_exports_ps);
CUT_CHECK_OFFSET(GX2PixelShader, 0x08, regs.spi_ps_in_control_0);
CUT_CHECK_OFFSET(GX2PixelShader, 0x0C, regs.spi_ps_in_control_1);
CUT_CHECK_OFFSET(GX2PixelShader, 0x10, regs.num_spi_ps_input_cntl);
CUT_CHECK_OFFSET(GX2PixelShader, 0x14, regs.spi_ps_input_cntls);
CUT_CHECK_OFFSET(GX2PixelShader, 0x94, regs.cb_shader_mask);
CUT_CHECK_OFFSET(GX2PixelShader, 0x98, regs.cb_shader_control);
CUT_CHECK_OFFSET(GX2PixelShader, 0x9C, regs.db_shader_control);
CUT_CHECK_OFFSET(GX2PixelShader, 0xA0, regs.spi_input_z);
CUT_CHECK_OFFSET(GX2PixelShader, 0xA4, size);
CUT_CHECK_OFFSET(GX2PixelShader, 0xA8, program);
CUT_CHECK_OFFSET(GX2PixelShader, 0xAC, mode);
CUT_CHECK_OFFSET(GX2PixelShader, 0xB0, uniformBlockCount);
CUT_CHECK_OFFSET(GX2PixelShader, 0xB4, uniformBlocks);
CUT_CHECK_OFFSET(GX2PixelShader, 0xB8, uniformVarCount);
CUT_CHECK_OFFSET(GX2PixelShader, 0xBC, uniformVars);
CUT_CHECK_OFFSET(GX2PixelShader, 0xC0, initialValueCount);
CUT_CHECK_OFFSET(GX2PixelShader, 0xC4, initialValues);
CUT_CHECK_OFFSET(GX2PixelShader, 0xC8, loopVarCount);
CUT_CHECK_OFFSET(GX2PixelShader, 0xCC, loopVars);
CUT_CHECK_OFFSET(GX2PixelShader, 0xD0, samplerVarCount);
CUT_CHECK_OFFSET(GX2PixelShader, 0xD4, samplerVars);
CUT_CHECK_OFFSET(GX2PixelShader, 0xD8, gx2rBuffer);
CUT_CHECK_SIZE(GX2PixelShader, 0xE8);

struct GX2GeometryShader
{
    struct
    {
        uint32_t sq_pgm_resources_gs;
        uint32_t vgt_gs_out_prim_type;
        uint32_t vgt_gs_mode;
        uint32_t pa_cl_vs_out_cntl;
        uint32_t sq_pgm_resources_vs;
        uint32_t sq_gs_vert_itemsize;
        uint32_t spi_vs_out_config;
        uint32_t num_spi_vs_out_id;
        uint32_t spi_vs_out_id[10];
        uint32_t vgt_strmout_buffer_en;
    } regs;

    uint32_t size;
    void *program;
    uint32_t vertexProgramSize;
    void *vertexProgram;
    GX2ShaderMode mode;

    uint32_t uniformBlockCount;
    GX2UniformBlock *uniformBlocks;

    uint32_t uniformVarCount;
    GX2UniformVar *uniformVars;

    uint32_t initialValueCount;
    GX2UniformInitialValue *initialValues;

    uint32_t loopVarCount;
    GX2LoopVar *loopVars;

    uint32_t samplerVarCount;
    GX2SamplerVar *samplerVars;

    uint32_t ringItemSize;
    BOOL hasStreamOut;
    uint32_t streamOutStride[4];

    GX2RBuffer gx2rBuffer;
};
CUT_CHECK_OFFSET(GX2GeometryShader, 0x00, regs.sq_pgm_resources_gs);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x04, regs.vgt_gs_out_prim_type);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x08, regs.vgt_gs_mode);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x0C, regs.pa_cl_vs_out_cntl);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x10, regs.sq_pgm_resources_vs);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x14, regs.sq_gs_vert_itemsize);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x18, regs.spi_vs_out_config);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x1C, regs.num_spi_vs_out_id);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x20, regs.spi_vs_out_id);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x48, regs.vgt_strmout_buffer_en);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x4C, size);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x50, program);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x54, vertexProgramSize);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x58, vertexProgram);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x5C, mode);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x60, uniformBlockCount);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x64, uniformBlocks);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x68, uniformVarCount);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x6C, uniformVars);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x70, initialValueCount);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x74, initialValues);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x78, loopVarCount);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x7C, loopVars);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x80, samplerVarCount);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x84, samplerVars);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x88, ringItemSize);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x8C, hasStreamOut);
CUT_CHECK_OFFSET(GX2GeometryShader, 0x90, streamOutStride);
CUT_CHECK_OFFSET(GX2GeometryShader, 0xA0, gx2rBuffer);
CUT_CHECK_SIZE(GX2GeometryShader, 0xB0);

struct GX2AttribStream
{
    uint32_t location;
    uint32_t buffer;
    uint32_t offset;
    GX2AttribFormat format;
    GX2AttribIndexType type;
    uint32_t aluDivisor;
    uint32_t mask;
    GX2EndianSwapMode endianSwap;
};
CUT_CHECK_OFFSET(GX2AttribStream, 0x0, location);
CUT_CHECK_OFFSET(GX2AttribStream, 0x4, buffer);
CUT_CHECK_OFFSET(GX2AttribStream, 0x8, offset);
CUT_CHECK_OFFSET(GX2AttribStream, 0xc, format);
CUT_CHECK_OFFSET(GX2AttribStream, 0x10, type);
CUT_CHECK_OFFSET(GX2AttribStream, 0x14, aluDivisor);
CUT_CHECK_OFFSET(GX2AttribStream, 0x18, mask);
CUT_CHECK_OFFSET(GX2AttribStream, 0x1c, endianSwap);
CUT_CHECK_SIZE(GX2AttribStream, 0x20);

CUT_IMPORT uint32_t (*GX2CalcGeometryShaderInputRingBufferSize)(uint32_t ringItemSize);

CUT_IMPORT uint32_t (*GX2CalcGeometryShaderOutputRingBufferSize)(uint32_t ringItemSize);

CUT_IMPORT uint32_t (*GX2CalcFetchShaderSizeEx)(uint32_t attribs, GX2FetchShaderType fetchShaderType, GX2TessellationMode tesellationMode);

CUT_IMPORT void (*GX2InitFetchShaderEx)(GX2FetchShader *fetchShader, uint8_t *buffer, uint32_t attribCount, const GX2AttribStream *attribs,
                                        GX2FetchShaderType type, GX2TessellationMode tessMode);

CUT_IMPORT void (*GX2SetFetchShader)(const GX2FetchShader *shader);

CUT_IMPORT void (*GX2SetVertexShader)(const GX2VertexShader *shader);

CUT_IMPORT void (*GX2SetPixelShader)(const GX2PixelShader *shader);

CUT_IMPORT void (*GX2SetGeometryShader)(const GX2GeometryShader *shader);

CUT_IMPORT void (*GX2SetVertexSampler)(const GX2Sampler *sampler, uint32_t id);

CUT_IMPORT void (*GX2SetPixelSampler)(const GX2Sampler *sampler, uint32_t id);

CUT_IMPORT void (*GX2SetGeometrySampler)(const GX2Sampler *sampler, uint32_t id);

CUT_IMPORT void (*GX2SetVertexUniformReg)(uint32_t offset, uint32_t count, const void *data);

CUT_IMPORT void (*GX2SetPixelUniformReg)(uint32_t offset, uint32_t count, const void *data);

CUT_IMPORT void (*GX2SetVertexUniformBlock)(uint32_t location, uint32_t size, const void *data);

CUT_IMPORT void (*GX2SetPixelUniformBlock)(uint32_t location, uint32_t size, const void *data);

CUT_IMPORT void (*GX2SetGeometryUniformBlock)(uint32_t location, uint32_t size, const void *data);

CUT_IMPORT void (*GX2SetShaderModeEx)(GX2ShaderMode mode, uint32_t numVsGpr, uint32_t numVsStackEntries, uint32_t numGsGpr,
                                      uint32_t numGsStackEntries, uint32_t numPsGpr, uint32_t numPsStackEntries);

CUT_IMPORT void (*GX2SetStreamOutEnable)(BOOL enable);

CUT_IMPORT void (*GX2SetGeometryShaderInputRingBuffer)(const void *buffer, uint32_t size);

CUT_IMPORT void (*GX2SetGeometryShaderOutputRingBuffer)(void *buffer, uint32_t size);

CUT_IMPORT uint32_t (*GX2GetPixelShaderGPRs)(const GX2PixelShader *shader);

CUT_IMPORT uint32_t (*GX2GetPixelShaderStackEntries)(const GX2PixelShader *shader);

CUT_IMPORT uint32_t (*GX2GetVertexShaderGPRs)(const GX2VertexShader *shader);

CUT_IMPORT uint32_t (*GX2GetVertexShaderStackEntries)(const GX2VertexShader *shader);

CUT_IMPORT uint32_t (*GX2GetGeometryShaderGPRs)(const GX2GeometryShader *shader);

CUT_IMPORT uint32_t (*GX2GetGeometryShaderStackEntries)(const GX2GeometryShader *shader);

static inline GX2UniformBlock *GX2GetGeometryUniformBlock(const GX2GeometryShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->uniformBlockCount; ++i)
    {
        if (strcmp(name, shader->uniformBlocks[i].name) == 0)
        {
            return &shader->uniformBlocks[i];
        }
    }

    return NULL;
}

static inline GX2UniformBlock *GX2GetPixelUniformBlock(const GX2PixelShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->uniformBlockCount; ++i)
    {
        if (strcmp(name, shader->uniformBlocks[i].name) == 0)
        {
            return &shader->uniformBlocks[i];
        }
    }

    return NULL;
}

static inline GX2UniformBlock *GX2GetVertexUniformBlock(const GX2VertexShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->uniformBlockCount; ++i)
    {
        if (strcmp(name, shader->uniformBlocks[i].name) == 0)
        {
            return &shader->uniformBlocks[i];
        }
    }

    return NULL;
}

static inline GX2UniformVar *GX2GetGeometryUniformVar(const GX2GeometryShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->uniformVarCount; ++i)
    {
        if (strcmp(name, shader->uniformVars[i].name) == 0)
        {
            return &shader->uniformVars[i];
        }
    }

    return NULL;
}

static inline GX2UniformVar *GX2GetPixelUniformVar(const GX2PixelShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->uniformVarCount; ++i)
    {
        if (strcmp(name, shader->uniformVars[i].name) == 0)
        {
            return &shader->uniformVars[i];
        }
    }

    return NULL;
}

static inline GX2UniformVar *GX2GetVertexUniformVar(const GX2VertexShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->uniformVarCount; ++i)
    {
        if (strcmp(name, shader->uniformVars[i].name) == 0)
        {
            return &shader->uniformVars[i];
        }
    }

    return NULL;
}

static inline void GX2SetShaderMode(GX2ShaderMode mode)
{
    if (mode == GX2_SHADER_MODE_GEOMETRY_SHADER)
    {
        GX2SetShaderModeEx(mode, 0x2c, 0x20, 0x40, 0x30, 0x4c, 0xb0);
    }
    else
    {
        GX2SetShaderModeEx(mode, 0x30, 0x40, 0x0, 0x0, 0xc8, 0xc0);
    }
}

#ifdef __cplusplus
}
#endif

/** @} */
