#pragma once

#include "../event.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Event
{
    BOOL (*GX2DrawDone)(void);
    void (*GX2WaitForVsync)(void);
    void (*GX2WaitForFlip)(void);
    void (*GX2SetEventCallback)(GX2EventType type, GX2EventCallbackFunction func, void *userData);
    void (*GX2GetEventCallback)(GX2EventType type, GX2EventCallbackFunction *funcOut, void **userDataOut);
    OSTime (*GX2GetRetiredTimeStamp)(void);
    OSTime (*GX2GetLastSubmittedTimeStamp)(void);
    void (*GX2GetSwapStatus)(uint32_t *swapCount, uint32_t *flipCount, OSTime *lastFlip, OSTime *lastVsync);
    BOOL (*GX2WaitTimeStamp)(OSTime time);
} ImportsGX2Event;

#ifdef __cplusplus
}
#endif
