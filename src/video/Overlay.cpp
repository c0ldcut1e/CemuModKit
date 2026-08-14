#include "Overlay.h"

#include <coreinit/time.h>
#include <imgui/backends/imgui_impl_wiiu.h>
#include <stb_image.h>

#include <utils/Utils.h>

Overlay::Overlay()
{
    IMGUI_CHECKVERSION();

    ImguiInit(m_overlayContext, false, true, ImGui_ImplGX2_BufferingType::SINGLE_BUFFERING, nullptr, SD_CARD_PATH "/font.ttf");
}

Overlay::~Overlay() { ImguiShutdown(m_overlayContext); }

void Overlay::Draw(const GX2ColorBuffer *colorBuffer, GX2ScanTarget scanTarget)
{
    UNUSED_PARAMETER(scanTarget);

    m_framebufferScale = ImVec2(colorBuffer->surface.width / (float) TV_WIDTH, colorBuffer->surface.height / (float) TV_HEIGHT);
    ImguiStart(m_overlayContext, m_framebufferScale);

    ImGui::ShowDemoWindow();

    ImguiEnd();
}

void Overlay::ImguiInit(ImGuiContext *&context, bool touchAllowed, bool padAllowed, ImGui_ImplGX2_BufferingType bufferingType,
                        const char *iniFilename, const char *fontPath)
{
    context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);
    ImGui_ImplWiiU_Init(touchAllowed, padAllowed);
    ImGui_ImplGX2_Init(bufferingType);

    ImGuiIO &io    = ImGui::GetIO();
    io.IniFilename = iniFilename;

    if (fontPath)
    {
        io.Fonts->TexGlyphPadding = 3;

        ImFontConfig fontConfig;
        fontConfig.OversampleH = 4;
        fontConfig.OversampleV = 4;
        fontConfig.PixelSnapH  = false;

        ImFont *font = io.Fonts->AddFontFromFileTTF(fontPath, 22.0f, &fontConfig);
        io.Fonts->AddFontFromFileTTF(fontPath, 30.0f, &fontConfig);
        if (font)
        {
            io.FontDefault = font;
        }
    }
}

void Overlay::ImguiShutdown(ImGuiContext *context)
{
    if (!context)
    {
        return;
    }

    m_lastFrameTime = 0;

    ImGui::SetCurrentContext(context);
    ImGui_ImplGX2_Shutdown();
    ImGui_ImplWiiU_Shutdown();
    ImGui::DestroyContext(context);
}

void Overlay::ImguiStart(ImGuiContext *context, ImVec2 framebufferScale)
{
    ImGui::SetCurrentContext(context);

    int64_t now     = OSGetTime();
    float deltaTime = 1.0f / 60.0f;
    if (m_lastFrameTime != 0)
    {
        int64_t deltaTicks = now - m_lastFrameTime;
        if (deltaTicks > 0)
        {
            deltaTime = (float) ((double) deltaTicks / (double) OSTimerClockSpeed);
            if (deltaTime > (1.0f / 15.0f))
            {
                deltaTime = 1.0f / 15.0f;
            }
        }
        else
        {
            deltaTime = 0.0f;
        }
    }

    m_lastFrameTime = now;

    ImGuiIO &io                = ImGui::GetIO();
    io.DisplaySize             = ImVec2((float) TV_WIDTH, (float) TV_HEIGHT);
    io.DisplayFramebufferScale = framebufferScale;
    io.DeltaTime               = deltaTime;

    ImGui_ImplGX2_NewFrame();
    ImGui::NewFrame();
}

void Overlay::ImguiEnd()
{
    ImGui::Render();
    ImGui_ImplGX2_RenderDrawData(ImGui::GetDrawData());
}
