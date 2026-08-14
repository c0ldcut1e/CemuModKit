#pragma once

#include "../core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsSndCoreCore
{
    void (*AXInit)();
    void (*AXInitEx)(uint32_t unk0);
    void (*AXQuit)();
    BOOL (*AXIsInit)();
    void (*AXSetDefaultMixerSelect)(uint32_t mixerSelect);
    uint32_t (*AXGetDefaultMixerSelect)();
    AXResult (*AXRegisterAppFrameCallback)(AXFrameCallback callback);
    AXResult (*AXDeregisterAppFrameCallback)(AXFrameCallback callback);
    AXFrameCallback (*AXRegisterFrameCallback)(AXFrameCallback callback);
    AXFrameCallback (*AXRegisterCallback)(AXFrameCallback callback);
    uint32_t (*AXGetInputSamplesPerFrame)();
    uint32_t (*AXGetInputSamplesPerSec)();
} ImportsSndCoreCore;

#ifdef __cplusplus
}
#endif
