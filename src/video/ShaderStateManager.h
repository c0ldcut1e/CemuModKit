#pragma once

#include <cstddef>
#include <cstdint>

#include <whb/gfx.h>

// TODO: Completly redo this because this implementation is kind of weird
class ShaderStateManager
{
public:
    static void SetShader(uint32_t id);
    static void UseShader();
    static uint32_t GenerateShader(const void *shaderData);
    static void AddShaderAttribute(const char *name, uint32_t buffer, uint32_t offset, GX2AttribFormat format);
    static void FinalizeShader();
    static void DestroyShader(uint32_t id);
    static void SetVertexUniformVar(uint32_t offset, uint32_t count, const void *value);
    static void SetPixelUniformVar(uint32_t offset, uint32_t count, const void *value);
    static void SetVertexUniformBlockVar(const char *uniformBlockName, size_t index, const void *value, size_t count);
    static void SetPixelUniformBlockVar(const char *uniformBlockName, size_t index, const void *value, size_t count);

private:
    static uint32_t GenerateShaderId();

    static WHBGfxShaderGroup *FindShaderGroup(uint32_t id);
    static bool StoreShaderGroup(uint32_t id, WHBGfxShaderGroup *shaderGroup);
    static void RemoveShaderGroup(uint32_t id);
    static bool ShaderIdExists(uint32_t id);

    struct ShaderSlot
    {
        uint32_t m_id;
        WHBGfxShaderGroup *m_shaderGroup;
    };

    static inline uint32_t s_currentShaderId         = 0;
    static constexpr size_t s_maxShaders             = 32;
    static inline ShaderSlot s_shaders[s_maxShaders] = {};
};
