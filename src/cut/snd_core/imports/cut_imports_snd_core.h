#pragma once

#include "cut_imports_snd_core_core.h"
#include "cut_imports_snd_core_device.h"
#include "cut_imports_snd_core_voice.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsSndCore
{
    ImportsSndCoreCore core;
    ImportsSndCoreDevice device;
    ImportsSndCoreVoice voice;
} ImportsSndCore;

#ifdef __cplusplus
}
#endif
