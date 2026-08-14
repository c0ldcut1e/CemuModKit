#pragma once
#include "../cut.h"
#include "enum.h"
#include <coreinit/time.h>

/**
 * \defgroup gx2_event Event
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2DisplayListOverrunData GX2DisplayListOverrunData;
typedef void (*GX2EventCallbackFunction)(GX2EventType, void *);

struct GX2DisplayListOverrunData
{
    //! Pointer to overrun display list
    void *oldList;

    //! Size of overrun display list
    uint32_t oldSize;

    //! Pointer to new display list
    void *newList;

    //! Size of new display list
    uint32_t newSize;

    CUT_UNKNOWN_BYTES(8);
};
CUT_CHECK_OFFSET(GX2DisplayListOverrunData, 0x00, oldList);
CUT_CHECK_OFFSET(GX2DisplayListOverrunData, 0x04, oldSize);
CUT_CHECK_OFFSET(GX2DisplayListOverrunData, 0x08, newList);
CUT_CHECK_OFFSET(GX2DisplayListOverrunData, 0x0C, newSize);
CUT_CHECK_SIZE(GX2DisplayListOverrunData, 0x18);

CUT_IMPORT BOOL (*GX2DrawDone)(void);

CUT_IMPORT void (*GX2WaitForVsync)(void);

CUT_IMPORT void (*GX2WaitForFlip)(void);

CUT_IMPORT void (*GX2SetEventCallback)(GX2EventType type, GX2EventCallbackFunction func, void *userData);

CUT_IMPORT void (*GX2GetEventCallback)(GX2EventType type, GX2EventCallbackFunction *funcOut, void **userDataOut);

CUT_IMPORT OSTime (*GX2GetRetiredTimeStamp)(void);

CUT_IMPORT OSTime (*GX2GetLastSubmittedTimeStamp)(void);

CUT_IMPORT void (*GX2GetSwapStatus)(uint32_t *swapCount, uint32_t *flipCount, OSTime *lastFlip, OSTime *lastVsync);

CUT_IMPORT BOOL (*GX2WaitTimeStamp)(OSTime time);

#ifdef __cplusplus
}
#endif

/** @} */
