#pragma once

#include "../debug.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Debug
{
    BOOL (*_GX2DebugSetCaptureInterface)(GX2DebugCaptureInterface *interface);
    void (*GX2DebugCaptureStart)(const char *filename, GX2DebugCaptureStartFlags flags);
    void (*GX2DebugCaptureEnd)(GX2DebugCaptureEndFlags flags);
    void (*GX2DebugCaptureFrame)(const char *filename);
    void (*GX2DebugCaptureFrames)(const char *filename, uint32_t count);
} ImportsGX2Debug;

#ifdef __cplusplus
}
#endif
