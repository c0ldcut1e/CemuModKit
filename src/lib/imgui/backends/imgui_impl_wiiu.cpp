#include "imgui_impl_wiiu.h"

#include <algorithm>
#include <string.h>

#include <imgui/imgui_internal.h>

struct ImGui_ImplWiiU_Data
{
    ImGui_ImplWiiU_Data() { memset((void *) this, 0, sizeof(*this)); }

    bool touchAllowed = true;
    bool padAllowed   = true;

    uint32_t vpadHeld = 0;
    uint32_t wpadHeld = 0;
    uint16_t lastKeys = 0;

    VPADStatus lastVPAD{};
};

struct PadKey
{
    ImGuiKey key;
    uint32_t vMask;
};

static std::vector<ImGuiContext *> gWiiUContexts;

static ImGui_ImplWiiU_Data *ImGui_ImplWiiU_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplWiiU_Data *) ImGui::GetIO().BackendPlatformUserData : nullptr;
}

bool ImGui_ImplWiiU_Init(bool touchAllowed, bool padAllowed)
{
    ImGuiIO &io = ImGui::GetIO();
    IM_ASSERT(io.BackendPlatformUserData == nullptr && "Already initialized a platform backend!");

    auto *backendData         = IM_NEW(ImGui_ImplWiiU_Data)();
    backendData->touchAllowed = touchAllowed;
    backendData->padAllowed   = padAllowed;

    io.BackendPlatformUserData = backendData;
    io.BackendPlatformName     = "imgui_impl_wiiu";
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.IniFilename = nullptr;

    io.KeyRepeatDelay = 0.5f;
    io.KeyRepeatRate  = 0.05f;

    ImGuiContext *context = ImGui::GetCurrentContext();
    IM_ASSERT(context != nullptr);

    gWiiUContexts.push_back(context);

    return true;
}

void ImGui_ImplWiiU_Shutdown()
{
    ImGui_ImplWiiU_Data *backendData = ImGui_ImplWiiU_GetBackendData();
    IM_ASSERT(backendData && "No platform backend to shutdown, or already shutdown?");

    ImGuiContext *context = ImGui::GetCurrentContext();
    auto it               = std::find(gWiiUContexts.begin(), gWiiUContexts.end(), context);
    if (it != gWiiUContexts.end())
    {
        gWiiUContexts.erase(it);
    }

    ImGuiIO &io                = ImGui::GetIO();
    io.BackendPlatformName     = nullptr;
    io.BackendPlatformUserData = nullptr;

    IM_DELETE(backendData);
}

static bool ImGui_ImplWiiU_WantsInput()
{
    const ImGuiIO &io = ImGui::GetIO();
    return io.WantCaptureMouse || io.WantCaptureKeyboard || io.WantTextInput ||
           ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) && io.NavActive && ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow));
}

static const PadKey kPadKeys[] = {{ImGuiKey_GamepadDpadLeft, VPAD_BUTTON_LEFT},
                                  {ImGuiKey_GamepadDpadRight, VPAD_BUTTON_RIGHT},
                                  {ImGuiKey_GamepadDpadUp, VPAD_BUTTON_UP},
                                  {ImGuiKey_GamepadDpadDown, VPAD_BUTTON_DOWN},

                                  {ImGuiKey_GamepadFaceLeft, VPAD_BUTTON_X},
                                  {ImGuiKey_GamepadFaceRight, VPAD_BUTTON_B},
                                  {ImGuiKey_GamepadFaceDown, VPAD_BUTTON_A},

                                  {ImGuiKey_GamepadLStickLeft, VPAD_STICK_L_EMULATION_LEFT},
                                  {ImGuiKey_GamepadLStickRight, VPAD_STICK_L_EMULATION_RIGHT},
                                  {ImGuiKey_GamepadLStickUp, VPAD_STICK_L_EMULATION_UP},
                                  {ImGuiKey_GamepadLStickDown, VPAD_STICK_L_EMULATION_DOWN},

                                  {ImGuiKey_GamepadL1, VPAD_BUTTON_L},
                                  {ImGuiKey_GamepadR1, VPAD_BUTTON_R}};

static constexpr size_t kKeyCount = sizeof(kPadKeys) / sizeof(kPadKeys[0]);

static void ImGui_ImplWiiU_ReportKeys(ImGui_ImplWiiU_Data *backendData)
{
    if (!ImGui_ImplWiiU_WantsInput())
    {
        return;
    }

    ImGuiIO &io      = ImGui::GetIO();
    uint16_t newMask = 0;

    for (size_t i = 0; i < kKeyCount; ++i)
    {
        bool pressed = backendData->vpadHeld & kPadKeys[i].vMask;
        if (pressed)
        {
            newMask |= uint16_t(1 << i);
        }

        if (((backendData->lastKeys ^ newMask) >> i) & 1)
        {
            io.AddKeyEvent(kPadKeys[i].key, pressed);
        }
    }

    backendData->lastKeys = newMask;
}

static bool ImGui_ImplWiiU_WantsButton(const ImGui_ImplWiiU_Data *backendData)
{
    if (!backendData || !backendData->padAllowed)
    {
        return false;
    }

    const ImGuiIO &io = ImGui::GetIO();
    return (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) && io.NavActive;
}

IMGUI_IMPL_API bool ImGui_ImplWiiU_ShouldConsumeTouch()
{
    ImGuiIO &io = ImGui::GetIO();
    return io.WantCaptureMouse || io.MouseDown[0] || io.MouseDown[1] || io.MouseDown[2];
}

IMGUI_IMPL_API bool ImGui_ImplWiiU_ShouldConsumeButton()
{
    const ImGui_ImplWiiU_Data *backendData = ImGui_ImplWiiU_GetBackendData();
    bool res                               = ImGui_ImplWiiU_WantsButton(backendData);

    return res;
}

bool ImGui_ImplWiiU_ProcessVPADInput(const VPADStatus *input)
{
    ImGui_ImplWiiU_Data *backendData = ImGui_ImplWiiU_GetBackendData();
    IM_ASSERT(backendData != nullptr && "Did you call ImGui_ImplWiiU_Init() ?");

    if (backendData->padAllowed)
    {
        backendData->vpadHeld = input->hold;
        ImGui_ImplWiiU_ReportKeys(backendData);
    }

    backendData->lastVPAD = *input;

    return ImGui_ImplWiiU_WantsInput();
}

const VPADStatus *ImGui_ImplWiiU_GetLastVPADInput()
{
    const ImGui_ImplWiiU_Data *backendData = ImGui_ImplWiiU_GetBackendData();
    IM_ASSERT(backendData != nullptr && "Did you call ImGui_ImplWiiU_Init() ?");

    return backendData ? &backendData->lastVPAD : nullptr;
}

std::vector<ImGuiContext *> ImGui_ImplWiiU_GetContextsNeedingInput()
{
    std::vector<ImGuiContext *> result;

    for (ImGuiContext *context : gWiiUContexts)
    {
        if (!context)
            continue;

        ImGui::SetCurrentContext(context);
        ImGuiIO &io = ImGui::GetIO();

        ImGui_ImplWiiU_Data *backendData = (ImGui_ImplWiiU_Data *) io.BackendPlatformUserData;
        if (!backendData)
        {
            continue;
        }

        result.push_back(context);
    }

    return result;
}
