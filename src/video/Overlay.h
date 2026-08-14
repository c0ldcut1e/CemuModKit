#pragma once

#include <gx2/enum.h>
#include <gx2/surface.h>

#include <cstdint>

#include <imgui/backends/imgui_impl_gx2.h>
#include <imgui/imgui.h>

class Overlay
{
public:
    Overlay();
    ~Overlay();

    void Draw(const GX2ColorBuffer *colorBuffer, GX2ScanTarget scanTarget);

private:
    Overlay(const Overlay &)            = delete;
    Overlay &operator=(const Overlay &) = delete;
    Overlay(Overlay &&)                 = delete;
    Overlay &operator=(Overlay &&)      = delete;

    void ImguiInit(ImGuiContext *&context, bool touchAllowed, bool padAllowed, ImGui_ImplGX2_BufferingType bufferingType, const char *iniFilename,
                   const char *fontPath = nullptr);
    void ImguiShutdown(ImGuiContext *context);
    void ImguiStart(ImGuiContext *context, ImVec2 framebufferScale);
    void ImguiEnd();

    ImGuiContext *m_overlayContext = nullptr;
    ImVec2 m_framebufferScale      = ImVec2(1.0f, 1.0f);
    int64_t m_lastFrameTime        = 0;
};
