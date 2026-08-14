#pragma once
#include "../cut.h"
#include "enum.h"
#include "surface.h"

/**
 * \defgroup gx2_display Display
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GX2DRCConnectCallback)(uint32_t drcSlot, BOOL attached);

CUT_IMPORT void (*GX2SetTVEnable)(BOOL enable);

CUT_IMPORT void (*GX2SetDRCEnable)(BOOL enable);

CUT_IMPORT void (*GX2CalcTVSize)(GX2TVRenderMode tvRenderMode, GX2SurfaceFormat surfaceFormat, GX2BufferingMode bufferingMode, uint32_t *size,
                                 uint32_t *unkOut);

CUT_IMPORT void (*GX2CalcDRCSize)(GX2DrcRenderMode drcRenderMode, GX2SurfaceFormat surfaceFormat, GX2BufferingMode bufferingMode, uint32_t *size,
                                  uint32_t *unkOut);

CUT_IMPORT void (*GX2SetTVBuffer)(void *buffer, uint32_t size, GX2TVRenderMode tvRenderMode, GX2SurfaceFormat surfaceFormat,
                                  GX2BufferingMode bufferingMode);

CUT_IMPORT void (*GX2SetDRCBuffer)(void *buffer, uint32_t size, GX2DrcRenderMode drcRenderMode, GX2SurfaceFormat surfaceFormat,
                                   GX2BufferingMode bufferingMode);

CUT_IMPORT void (*GX2SetTVScale)(uint32_t x, uint32_t y);

CUT_IMPORT void (*GX2SetDRCScale)(uint32_t x, uint32_t y);

CUT_IMPORT GX2AspectRatio (*GX2GetSystemTVAspectRatio)(void);

CUT_IMPORT GX2TVScanMode (*GX2GetSystemTVScanMode)(void);

CUT_IMPORT GX2DrcRenderMode (*GX2GetSystemDRCScanMode)(void);

CUT_IMPORT GX2DrcRenderMode (*GX2GetSystemDRCMode)(void);

CUT_IMPORT GX2DRCConnectCallback (*GX2SetDRCConnectCallback)(uint32_t drcSlot, GX2DRCConnectCallback callback);

#ifdef __cplusplus
}
#endif

/** @} */
