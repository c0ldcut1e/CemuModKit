#include "ShaderStateManager.h"

#include <cstdlib>
#include <cstring>
#include <ctime>

#include <fmt/format_wiiu.h>

#include <coreinit/cache.h>
#include <coreinit/memdefaultheap.h>
#include <gfd/gfd.h>
#include <gx2/mem.h>

#define SHADER_LOG_NORMAL(formatString, ...) fmt::wiiu_debug_println("[ShaderStateManager] [{:08X}] " formatString, s_currentShaderId, ##__VA_ARGS__)

#define SHADER_LOG_VERBOSE(formatString, ...)                                                                                                        \
    fmt::wiiu_verbose_debug_println("[ShaderStateManager] [{:08X}] " formatString, s_currentShaderId, ##__VA_ARGS__)

static void cleanupShaderGroup(WHBGfxShaderGroup *shaderGroup)
{
    if (!shaderGroup)
    {
        return;
    }

    if (shaderGroup->vertexShader)
    {
        MEMFreeToDefaultHeap(shaderGroup->vertexShader->gx2rBuffer.buffer ? shaderGroup->vertexShader->gx2rBuffer.buffer
                                                                          : shaderGroup->vertexShader->program);
        MEMFreeToDefaultHeap(shaderGroup->vertexShader);
    }

    if (shaderGroup->pixelShader)
    {
        MEMFreeToDefaultHeap(shaderGroup->pixelShader->gx2rBuffer.buffer ? shaderGroup->pixelShader->gx2rBuffer.buffer
                                                                         : shaderGroup->pixelShader->program);
        MEMFreeToDefaultHeap(shaderGroup->pixelShader);
    }

    MEMFreeToDefaultHeap(shaderGroup->fetchShaderProgram);

    free(shaderGroup);
}

void ShaderStateManager::SetShader(uint32_t id)
{
    if (!FindShaderGroup(id))
    {
        return;
    }

    s_currentShaderId = id;
}

void ShaderStateManager::UseShader()
{
    WHBGfxShaderGroup *shaderGroup = FindShaderGroup(s_currentShaderId);
    if (!shaderGroup)
    {
        SHADER_LOG_NORMAL("Failed to use shader");
        return;
    }

    GX2SetFetchShader(&shaderGroup->fetchShader);
    GX2SetVertexShader(shaderGroup->vertexShader);
    GX2SetPixelShader(shaderGroup->pixelShader);
}

uint32_t ShaderStateManager::GenerateShader(const void *shaderData)
{
    s_currentShaderId = GenerateShaderId();
    SHADER_LOG_VERBOSE("Generating new shader");

    WHBGfxShaderGroup *shaderGroup = nullptr;
    GX2VertexShader *vertexShader  = nullptr;
    GX2PixelShader *pixelShader    = nullptr;
    void *vertexShaderProgram      = nullptr;
    void *pixelShaderProgram       = nullptr;

    uint32_t headerSize  = 0;
    uint32_t programSize = 0;

    shaderGroup = (WHBGfxShaderGroup *) malloc(sizeof(WHBGfxShaderGroup));
    if (!shaderGroup)
    {
        SHADER_LOG_NORMAL("Failed to allocate shader group");
        s_currentShaderId = 0;
        return 0;
    }

    memset(shaderGroup, 0, sizeof(WHBGfxShaderGroup));

    if (GFDGetVertexShaderCount(shaderData) == 0)
    {
        SHADER_LOG_NORMAL("Failed to load vertex shader: count == 0");
        goto fail;
    }

    headerSize = GFDGetVertexShaderHeaderSize(0, shaderData);
    if (headerSize == 0)
    {
        SHADER_LOG_NORMAL("Failed to load vertex shader: header size == 0");
        goto fail;
    }

    programSize = GFDGetVertexShaderProgramSize(0, shaderData);
    if (programSize == 0)
    {
        SHADER_LOG_NORMAL("Failed to load vertex shader: program size == 0");
        goto fail;
    }

    vertexShader = (GX2VertexShader *) MEMAllocFromDefaultHeapEx(headerSize, 64);
    if (!vertexShader)
    {
        SHADER_LOG_NORMAL("Failed to load vertex shader: failed to allocate shader (header size == %u)", headerSize);
        goto fail;
    }

    vertexShaderProgram = MEMAllocFromDefaultHeapEx(programSize, GX2_SHADER_PROGRAM_ALIGNMENT);
    if (!vertexShaderProgram)
    {
        SHADER_LOG_NORMAL("Failed to load vertex shader: failed to allocate program");
        goto fail;
    }

    if (!GFDGetVertexShader(vertexShader, vertexShaderProgram, 0, shaderData))
    {
        SHADER_LOG_NORMAL("Failed to load vertex shader: GFDGetVertexShader failed");
        goto fail;
    }

    vertexShader->program              = vertexShaderProgram;
    vertexShader->size                 = programSize;
    vertexShader->gx2rBuffer.flags     = GX2R_RESOURCE_BIND_SHADER_PROGRAM;
    vertexShader->gx2rBuffer.elemSize  = programSize;
    vertexShader->gx2rBuffer.elemCount = 1;
    vertexShader->gx2rBuffer.buffer    = vertexShaderProgram;
    shaderGroup->vertexShader          = vertexShader;

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, vertexShader->program, vertexShader->size);

    SHADER_LOG_VERBOSE("Successfully loaded vertex shader");

    if (GFDGetPixelShaderCount(shaderData) == 0)
    {
        SHADER_LOG_NORMAL("Failed to load pixel shader: count == 0");
        goto fail;
    }

    headerSize = GFDGetPixelShaderHeaderSize(0, shaderData);
    if (headerSize == 0)
    {
        SHADER_LOG_NORMAL("Failed to load pixel shader: header size == 0");
        goto fail;
    }

    programSize = GFDGetPixelShaderProgramSize(0, shaderData);
    if (programSize == 0)
    {
        SHADER_LOG_NORMAL("Failed to load pixel shader: program size == 0");
        goto fail;
    }

    pixelShader = (GX2PixelShader *) MEMAllocFromDefaultHeapEx(headerSize, 64);
    if (!pixelShader)
    {
        SHADER_LOG_NORMAL("Failed to load pixel shader: failed to allocate shader (header size == %u)", headerSize);
        goto fail;
    }

    pixelShaderProgram = MEMAllocFromDefaultHeapEx(programSize, GX2_SHADER_PROGRAM_ALIGNMENT);
    if (!pixelShaderProgram)
    {
        SHADER_LOG_NORMAL("Failed to load pixel shader: failed to allocate program");
        goto fail;
    }

    if (!GFDGetPixelShader(pixelShader, pixelShaderProgram, 0, shaderData))
    {
        SHADER_LOG_NORMAL("Failed to load pixel shader: GFDGetPixelShader failed");
        goto fail;
    }

    pixelShader->program              = pixelShaderProgram;
    pixelShader->size                 = programSize;
    pixelShader->gx2rBuffer.flags     = GX2R_RESOURCE_BIND_SHADER_PROGRAM;
    pixelShader->gx2rBuffer.elemSize  = programSize;
    pixelShader->gx2rBuffer.elemCount = 1;
    pixelShader->gx2rBuffer.buffer    = pixelShaderProgram;
    shaderGroup->pixelShader          = pixelShader;

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, pixelShader->program, pixelShader->size);

    SHADER_LOG_VERBOSE("Successfully loaded pixel shader");

    if (!StoreShaderGroup(s_currentShaderId, shaderGroup))
    {
        SHADER_LOG_NORMAL("Failed to store shader: registry is full");
        goto fail;
    }

    return s_currentShaderId;

fail:
    s_currentShaderId = 0;

    if (!shaderGroup->vertexShader)
    {
        MEMFreeToDefaultHeap(vertexShaderProgram);
        MEMFreeToDefaultHeap(vertexShader);
    }

    if (!shaderGroup->pixelShader)
    {
        MEMFreeToDefaultHeap(pixelShaderProgram);
        MEMFreeToDefaultHeap(pixelShader);
    }

    cleanupShaderGroup(shaderGroup);

    return 0;
}

void ShaderStateManager::AddShaderAttribute(const char *name, uint32_t buffer, uint32_t offset, GX2AttribFormat format)
{
    WHBGfxShaderGroup *shaderGroup = FindShaderGroup(s_currentShaderId);
    if (!shaderGroup)
    {
        SHADER_LOG_NORMAL("Failed to add shader attribute");
        return;
    }

    WHBGfxInitShaderAttribute(shaderGroup, name, buffer, offset, format);
}

void ShaderStateManager::FinalizeShader()
{
    WHBGfxShaderGroup *shaderGroup = FindShaderGroup(s_currentShaderId);
    if (!shaderGroup)
    {
        SHADER_LOG_NORMAL("Failed to finalize shader");
        return;
    }

    uint32_t size = GX2CalcFetchShaderSizeEx(shaderGroup->numAttributes, GX2_FETCH_SHADER_TESSELLATION_NONE, GX2_TESSELLATION_MODE_DISCRETE);
    if (size == 0)
    {
        SHADER_LOG_NORMAL("Failed to finalize shader: fetch shader size == 0");
        RemoveShaderGroup(s_currentShaderId);
        s_currentShaderId = 0;
        cleanupShaderGroup(shaderGroup);
        return;
    }

    void *fetchShaderProgram = MEMAllocFromDefaultHeapEx(size, GX2_SHADER_PROGRAM_ALIGNMENT);
    if (!fetchShaderProgram)
    {
        SHADER_LOG_NORMAL("Failed to finalize shader: failed to allocate fetch shader program");
        RemoveShaderGroup(s_currentShaderId);
        s_currentShaderId = 0;
        cleanupShaderGroup(shaderGroup);
        return;
    }

    GX2FetchShader fetchShader;
    GX2InitFetchShaderEx(&fetchShader, (uint8_t *) fetchShaderProgram, shaderGroup->numAttributes, shaderGroup->attributes,
                         GX2_FETCH_SHADER_TESSELLATION_NONE, GX2_TESSELLATION_MODE_DISCRETE);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, fetchShaderProgram, size);

    shaderGroup->fetchShaderProgram = fetchShaderProgram;
    shaderGroup->fetchShader        = fetchShader;
}

void ShaderStateManager::DestroyShader(uint32_t id)
{
    WHBGfxShaderGroup *shaderGroup = FindShaderGroup(id);
    if (!shaderGroup)
    {
        return;
    }

    cleanupShaderGroup(shaderGroup);
    RemoveShaderGroup(id);

    if (s_currentShaderId == id)
        s_currentShaderId = 0;
}

void ShaderStateManager::SetVertexUniformVar(uint32_t offset, uint32_t count, const void *value)
{
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

    if (!FindShaderGroup(s_currentShaderId))
    {
        SHADER_LOG_NORMAL("Failed to set vertex uniform variable at offset %u", offset);
        return;
    }

    GX2SetVertexUniformReg(offset, count, value);
}

void ShaderStateManager::SetPixelUniformVar(uint32_t offset, uint32_t count, const void *value)
{
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

    if (!FindShaderGroup(s_currentShaderId))
    {
        SHADER_LOG_NORMAL("Failed to set pixel uniform variable at offset %u", offset);
        return;
    }

    GX2SetPixelUniformReg(offset, count, value);
}

void ShaderStateManager::SetVertexUniformBlockVar(const char *uniformBlockName, size_t index, const void *value, size_t count)
{
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    WHBGfxShaderGroup *shaderGroup = FindShaderGroup(s_currentShaderId);
    if (!shaderGroup)
    {
        SHADER_LOG_NORMAL("Failed to set vertex uniform block var %s", uniformBlockName);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    GX2UniformBlock *uniformBlock = GX2GetVertexUniformBlock(shaderGroup->vertexShader, uniformBlockName);
    if (!uniformBlock)
    {
        SHADER_LOG_NORMAL("Failed to set vertex uniform block var %s: uniform block is null", uniformBlockName);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    uint32_t *temp = (uint32_t *) MEMAllocFromDefaultHeapEx(uniformBlock->size, GX2_UNIFORM_BLOCK_ALIGNMENT);
    if (!temp)
    {
        SHADER_LOG_NORMAL("Failed to set vertex uniform block var %s: failed to allocate temporary "
                          "uniform block buffer",
                          uniformBlockName);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    memset(temp, 0, uniformBlock->size);

    const uint32_t *src = (const uint32_t *) value;
    size_t maxRegs      = uniformBlock->size / sizeof(uint32_t);
    if (index + count > maxRegs)
    {
        MEMFreeToDefaultHeap(temp);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        temp[index + i] = __builtin_bswap32(src[i]);
    }

    DCFlushRange(temp, uniformBlock->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, temp, uniformBlock->size);

    GX2SetVertexUniformBlock(uniformBlock->offset, uniformBlock->size, temp);

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, temp, uniformBlock->size);

    MEMFreeToDefaultHeap(temp);

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);
}

void ShaderStateManager::SetPixelUniformBlockVar(const char *uniformBlockName, size_t index, const void *value, size_t count)
{
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    WHBGfxShaderGroup *shaderGroup = FindShaderGroup(s_currentShaderId);
    if (!shaderGroup)
    {
        SHADER_LOG_NORMAL("Failed to set pixel uniform block var %s", uniformBlockName);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    GX2UniformBlock *uniformBlock = GX2GetPixelUniformBlock(shaderGroup->pixelShader, uniformBlockName);
    if (!uniformBlock)
    {
        SHADER_LOG_NORMAL("Failed to set pixel uniform block var %s: uniform block is null", uniformBlockName);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    uint32_t *temp = (uint32_t *) MEMAllocFromDefaultHeapEx(uniformBlock->size, GX2_UNIFORM_BLOCK_ALIGNMENT);
    if (!temp)
    {
        SHADER_LOG_NORMAL("Failed to set pixel uniform block var %s: failed to allocate temporary "
                          "uniform block buffer",
                          uniformBlockName);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    memset(temp, 0, uniformBlock->size);

    const uint32_t *src = (const uint32_t *) value;
    size_t maxRegs      = uniformBlock->size / sizeof(uint32_t);
    if (index + count > maxRegs)
    {
        MEMFreeToDefaultHeap(temp);

        GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);

        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        temp[index + i] = __builtin_bswap32(src[i]);
    }

    DCFlushRange(temp, uniformBlock->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, temp, uniformBlock->size);

    GX2SetPixelUniformBlock(uniformBlock->offset, uniformBlock->size, temp);

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, temp, uniformBlock->size);

    MEMFreeToDefaultHeap(temp);

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);
}

uint32_t ShaderStateManager::GenerateShaderId()
{
    static uint32_t state = []
    {
        uint32_t addr      = (uint32_t) &state;
        uint32_t timeValue = (uint32_t) time(nullptr);
        return (uint32_t) (addr ^ timeValue);
    }();

    uint32_t id;
    do
    {
        state *= 0x4A39B70D;
        id = state >> 1;
    } while (id == 0 || ShaderIdExists(id));

    return id;
}

WHBGfxShaderGroup *ShaderStateManager::FindShaderGroup(uint32_t id)
{
    for (size_t i = 0; i < s_maxShaders; i++)
    {
        if (s_shaders[i].m_id == id)
        {
            return s_shaders[i].m_shaderGroup;
        }
    }

    return nullptr;
}

bool ShaderStateManager::StoreShaderGroup(uint32_t id, WHBGfxShaderGroup *shaderGroup)
{
    for (size_t i = 0; i < s_maxShaders; i++)
    {
        if (s_shaders[i].m_id == 0)
        {
            s_shaders[i].m_id          = id;
            s_shaders[i].m_shaderGroup = shaderGroup;
            return true;
        }
    }

    return false;
}

void ShaderStateManager::RemoveShaderGroup(uint32_t id)
{
    for (size_t i = 0; i < s_maxShaders; i++)
    {
        if (s_shaders[i].m_id == id)
        {
            s_shaders[i].m_id          = 0;
            s_shaders[i].m_shaderGroup = nullptr;
            return;
        }
    }
}

bool ShaderStateManager::ShaderIdExists(uint32_t id) { return FindShaderGroup(id) != nullptr; }
