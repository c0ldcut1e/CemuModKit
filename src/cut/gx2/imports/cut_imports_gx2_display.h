#pragma once

#include "../display.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Display
{
    void (*GX2SetTVEnable)(BOOL enable);
    void (*GX2SetDRCEnable)(BOOL enable);
    void (*GX2CalcTVSize)(GX2TVRenderMode tvRenderMode, GX2SurfaceFormat surfaceFormat, GX2BufferingMode bufferingMode, uint32_t *size,
                          uint32_t *unkOut);
    void (*GX2CalcDRCSize)(GX2DrcRenderMode drcRenderMode, GX2SurfaceFormat surfaceFormat, GX2BufferingMode bufferingMode, uint32_t *size,
                           uint32_t *unkOut);
    void (*GX2SetTVBuffer)(void *buffer, uint32_t size, GX2TVRenderMode tvRenderMode, GX2SurfaceFormat surfaceFormat, GX2BufferingMode bufferingMode);
    void (*GX2SetDRCBuffer)(void *buffer, uint32_t size, GX2DrcRenderMode drcRenderMode, GX2SurfaceFormat surfaceFormat,
                            GX2BufferingMode bufferingMode);
    void (*GX2SetTVScale)(uint32_t x, uint32_t y);
    void (*GX2SetDRCScale)(uint32_t x, uint32_t y);
    GX2AspectRatio (*GX2GetSystemTVAspectRatio)(void);
    GX2TVScanMode (*GX2GetSystemTVScanMode)(void);
    GX2DrcRenderMode (*GX2GetSystemDRCScanMode)(void);
    GX2DrcRenderMode (*GX2GetSystemDRCMode)(void);
    GX2DRCConnectCallback (*GX2SetDRCConnectCallback)(uint32_t drcSlot, GX2DRCConnectCallback callback);
} ImportsGX2Display;

#ifdef __cplusplus
}
#endif
