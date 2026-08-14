#pragma once

#include <string.h>

#include <imgui/imgui.h>

#include <gx2/sampler.h>
#include <gx2/texture.h>

struct ImGui_ImplGX2_Texture
{
    ImGui_ImplGX2_Texture() { memset(this, 0, sizeof(*this)); }

    GX2Texture *texture{};
    GX2Sampler *sampler{};
};

enum class ImGui_ImplGX2_BufferingType : int
{
    SINGLE_BUFFERING  = 1,
    DOUBLE_BUFFERING  = 2,
    TRIPPLE_BUFFERING = 3,
};

IMGUI_IMPL_API void ImGui_ImplGX2_Init(ImGui_ImplGX2_BufferingType bufferingType);
IMGUI_IMPL_API void ImGui_ImplGX2_Shutdown();
IMGUI_IMPL_API void ImGui_ImplGX2_NewFrame();
IMGUI_IMPL_API void ImGui_ImplGX2_RenderDrawData(ImDrawData *data);

IMGUI_IMPL_API void ImGui_ImplGX2_CreateFontsTexture();
IMGUI_IMPL_API void ImGui_ImplGX2_DestroyFontsTexture();
IMGUI_IMPL_API void ImGui_ImplGX2_CreateDeviceObjects();
IMGUI_IMPL_API void ImGui_ImplGX2_DestroyDeviceObjects();

IMGUI_IMPL_API ImGui_ImplGX2_Texture *ImGui_ImplGX2_CreateTextureRGBA32(const void *pixels, int width, int height);
IMGUI_IMPL_API void ImGui_ImplGX2_UpdateTextureRGBA32(ImGui_ImplGX2_Texture *texture, const void *pixels, int width, int height);
IMGUI_IMPL_API void ImGui_ImplGX2_DestroyTexture(ImGui_ImplGX2_Texture *texture);
