#pragma once

#include "../systeminfo.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitSysteminfo
{
    OSSystemInfo *(*OSGetSystemInfo)(void);
    BOOL (*OSEnableHomeButtonMenu)(BOOL enable);
    BOOL (*OSIsHomeButtonMenuEnabled)(void);
    uint32_t (*__OSGetProcessSDKVersion)(void);
} ImportsCoreInitSysteminfo;

#ifdef __cplusplus
}
#endif
