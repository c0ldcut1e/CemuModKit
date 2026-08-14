#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSystemInfo OSSystemInfo;

struct OSSystemInfo
{
    uint32_t busClockSpeed;
    uint32_t coreClockSpeed;
    int64_t baseTime;
    CUT_UNKNOWN_BYTES(0x10);
};
CUT_CHECK_OFFSET(OSSystemInfo, 0x0, busClockSpeed);
CUT_CHECK_OFFSET(OSSystemInfo, 0x4, coreClockSpeed);
CUT_CHECK_OFFSET(OSSystemInfo, 0x8, baseTime);
CUT_CHECK_SIZE(OSSystemInfo, 0x20);

CUT_IMPORT OSSystemInfo *(*OSGetSystemInfo)();

CUT_IMPORT BOOL (*OSEnableHomeButtonMenu)(BOOL enable);

CUT_IMPORT BOOL (*OSIsHomeButtonMenuEnabled)();

CUT_IMPORT uint32_t (*__OSGetProcessSDKVersion)();

#ifdef __cplusplus
}
#endif
