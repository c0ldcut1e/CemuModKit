#pragma once

#include "../time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitTime
{
    OSTime (*OSGetTime)(void);
    OSTime (*OSGetSystemTime)(void);
    OSTick (*OSGetTick)(void);
    OSTick (*OSGetSystemTick)(void);
    OSTime (*OSCalendarTimeToTicks)(OSCalendarTime *calendarTime);
    void (*OSTicksToCalendarTime)(OSTime time, OSCalendarTime *calendarTime);
} ImportsCoreInitTime;

#ifdef __cplusplus
}
#endif
