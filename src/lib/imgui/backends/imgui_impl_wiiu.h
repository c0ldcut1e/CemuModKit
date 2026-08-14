#pragma once

#include <vector>

#include <imgui/imgui.h>

#include <vpad/input.h>

IMGUI_IMPL_API bool ImGui_ImplWiiU_Init(bool touchAllowed, bool padAllowed);
IMGUI_IMPL_API void ImGui_ImplWiiU_Shutdown();

IMGUI_IMPL_API bool ImGui_ImplWiiU_ShouldConsumeButton();
IMGUI_IMPL_API bool ImGui_ImplWiiU_ShouldConsumeTouch();

IMGUI_IMPL_API bool ImGui_ImplWiiU_ProcessVPADInput(const VPADStatus *input);
IMGUI_IMPL_API const VPADStatus *ImGui_ImplWiiU_GetLastVPADInput();

IMGUI_IMPL_API std::vector<ImGuiContext *> ImGui_ImplWiiU_GetContextsNeedingInput();
