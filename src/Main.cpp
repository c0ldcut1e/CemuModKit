#include "Main.h"

#include <gx2/context.h>

#include <fmt/format_wiiu.h>

#include <imgui/backends/imgui_impl_wiiu.h>
#include <imgui/imgui.h>

#include <FunctionPatcher.h>

#include "video/Overlay.h"

bool g_blockGameInput = true;

Overlay *g_overlay = nullptr;

GX2ContextState *g_originalContextState = nullptr;
GX2ColorBuffer g_lastTVColorBuffer{};
GX2ColorBuffer g_lastDRCColorBuffer{};

DECL_FUNCTION(void, GX2GetCurrentScanBuffer, GX2ScanTarget scanTarget, GX2ColorBuffer *buffer)
{
    real_GX2GetCurrentScanBuffer(scanTarget, buffer);

    if (scanTarget == GX2_SCAN_TARGET_TV)
    {
        memmove(&g_lastTVColorBuffer, buffer, sizeof(GX2ColorBuffer));
    }
    else
    {
        memmove(&g_lastDRCColorBuffer, buffer, sizeof(GX2ColorBuffer));
    }
}

DECL_FUNCTION(void, GX2SetContextState, GX2ContextState *state)
{
    real_GX2SetContextState(state);

    g_originalContextState = state;
}

DECL_FUNCTION(void, GX2SetupContextStateEx, GX2ContextState *state, BOOL unk1)
{
    real_GX2SetupContextStateEx(state, unk1);

    g_originalContextState = state;
}

DECL_FUNCTION(void, GX2CopyColorBufferToScanBuffer, const GX2ColorBuffer *buffer, GX2ScanTarget scanTarget)
{
    if (g_originalContextState)
    {
        real_GX2SetContextState(g_originalContextState);
    }

    GX2SetColorBuffer(buffer, GX2_RENDER_TARGET_0);

    if (g_overlay)
    {
        g_overlay->Draw(buffer, scanTarget);
    }

    if (g_originalContextState)
    {
        real_GX2SetContextState(g_originalContextState);
    }

    real_GX2CopyColorBufferToScanBuffer(buffer, scanTarget);
}

DECL_FUNCTION(int, VPADRead, VPADChan chan, VPADStatus *buffers, uint32_t count, VPADReadError *outError)
{
    VPADReadError realErr;
    int result = real_VPADRead(chan, buffers, count, &realErr);
    if (result > 0 && realErr == VPAD_READ_SUCCESS)
    {
        for (uint32_t i = 0; i < count; i++)
        {
            VPADTouchData calibration{};
            VPADGetTPCalibratedPoint(chan, &calibration, &buffers[i].tpNormal);
            buffers[i].tpFiltered1.touched = calibration.touched;
            buffers[i].tpFiltered1.x       = calibration.x;
            buffers[i].tpFiltered1.y       = calibration.y;
            buffers[i].tpFiltered2         = buffers[i].tpFiltered1;
        }

        uint32_t sampleCount = (uint32_t) result;
        VPADStatus merged    = buffers[sampleCount - 1];
        for (uint32_t i = 0; i + 1 < sampleCount; i++)
        {
            merged.trigger |= buffers[i].trigger;
            merged.release |= buffers[i].release;
        }

        ImGuiContext *previousContext = ImGui::GetCurrentContext();

        bool consumeTouch = false;

        for (ImGuiContext *context : ImGui_ImplWiiU_GetContextsNeedingInput())
        {
            if (!context)
            {
                continue;
            }

            ImGui::SetCurrentContext(context);
            ImGui_ImplWiiU_ProcessVPADInput(&merged);

            consumeTouch |= ImGui_ImplWiiU_ShouldConsumeTouch();
        }

        ImGui::SetCurrentContext(previousContext);

        if (g_blockGameInput)
        {
            for (uint32_t i = 0; i < count; i++)
            {
                buffers[i].hold    = 0;
                buffers[i].trigger = 0;
                buffers[i].release = 0;
                memset(&buffers[i].leftStick, 0, sizeof(buffers[i].leftStick));
                memset(&buffers[i].rightStick, 0, sizeof(buffers[i].rightStick));
                memset(&buffers[i].direction, 0, sizeof(buffers[i].direction));
                memset(&buffers[i].tpNormal, 0, sizeof(buffers[i].tpNormal));
                memset(&buffers[i].tpFiltered1, 0, sizeof(buffers[i].tpFiltered1));
                memset(&buffers[i].tpFiltered2, 0, sizeof(buffers[i].tpFiltered2));
            }

            merged.hold    = 0;
            merged.trigger = 0;
            merged.release = 0;
            memset(&merged.leftStick, 0, sizeof(merged.leftStick));
            memset(&merged.rightStick, 0, sizeof(merged.rightStick));
            memset(&merged.direction, 0, sizeof(merged.direction));
            memset(&merged.tpNormal, 0, sizeof(merged.tpNormal));
            memset(&merged.tpFiltered1, 0, sizeof(merged.tpFiltered1));
            memset(&merged.tpFiltered2, 0, sizeof(merged.tpFiltered2));
        }
        else if (consumeTouch)
        {
            for (uint32_t i = 0; i < count; i++)
            {
                memset(&buffers[i].tpNormal, 0, sizeof(buffers[i].tpNormal));
                memset(&buffers[i].tpFiltered1, 0, sizeof(buffers[i].tpFiltered1));
                memset(&buffers[i].tpFiltered2, 0, sizeof(buffers[i].tpFiltered2));
            }

            memset(&merged.tpNormal, 0, sizeof(merged.tpNormal));
            memset(&merged.tpFiltered1, 0, sizeof(merged.tpFiltered1));
            memset(&merged.tpFiltered2, 0, sizeof(merged.tpFiltered2));
        }

        buffers[sampleCount - 1] = merged;
    }

    if (outError)
    {
        *outError = realErr;
    }

    return result;
}

void ModKitMain()
{
    g_overlay = new Overlay();

    REPLACE_FUNCTION(GX2GetCurrentScanBuffer, gx2, GX2GetCurrentScanBuffer);
    REPLACE_FUNCTION(GX2SetContextState, gx2, GX2SetContextState);
    REPLACE_FUNCTION(GX2SetupContextStateEx, gx2, GX2SetupContextStateEx);
    REPLACE_FUNCTION(GX2CopyColorBufferToScanBuffer, gx2, GX2CopyColorBufferToScanBuffer);
    REPLACE_FUNCTION(VPADRead, vpad, VPADRead);
}
