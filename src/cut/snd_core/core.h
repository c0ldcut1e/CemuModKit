#pragma once

#include "../cut.h"
#include "device.h"
#include "result.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*AXFrameCallback)(void);

//! A value from enum AX_INIT_RENDERER.
typedef uint32_t AXInitRenderer;

//! A value from enum AX_INIT_PIPELINE.
typedef uint32_t AXInitPipeline;

enum AX_INIT_RENDERER
{
    AX_INIT_RENDERER_32KHZ = 0,
    AX_INIT_RENDERER_48KHZ = 1,
};

enum AX_INIT_PIPELINE
{
    AX_INIT_PIPELINE_SINGLE     = 0,
    AX_INIT_PIPELINE_FOUR_STAGE = 1,
};

enum AX_MIXER_SELECT
{
    AX_MIXER_SELECT_DSP  = 0,
    AX_MIXER_SELECT_PPC  = 1,
    AX_MIXER_SELECT_BOTH = 2,
};

CUT_IMPORT void (*AXInit)();

CUT_IMPORT void (*AXInitEx)(uint32_t unk0);

CUT_IMPORT void (*AXQuit)();

CUT_IMPORT BOOL (*AXIsInit)();

CUT_IMPORT void (*AXSetDefaultMixerSelect)(uint32_t mixerSelect);

CUT_IMPORT uint32_t (*AXGetDefaultMixerSelect)();

CUT_IMPORT AXResult (*AXRegisterAppFrameCallback)(AXFrameCallback callback);

CUT_IMPORT AXResult (*AXDeregisterAppFrameCallback)(AXFrameCallback callback);

CUT_IMPORT AXFrameCallback (*AXRegisterFrameCallback)(AXFrameCallback callback);

CUT_IMPORT AXFrameCallback (*AXRegisterCallback)(AXFrameCallback callback);

CUT_IMPORT uint32_t (*AXGetInputSamplesPerFrame)();

CUT_IMPORT uint32_t (*AXGetInputSamplesPerSec)();

#ifdef __cplusplus
}
#endif