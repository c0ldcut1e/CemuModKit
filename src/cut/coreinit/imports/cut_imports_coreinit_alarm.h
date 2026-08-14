#pragma once

#include "../alarm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitAlarm
{
    BOOL (*OSCancelAlarm)(OSAlarm *alarm);
    void (*OSCreateAlarm)(OSAlarm *alarm);
    void *(*OSGetAlarmUserData)(OSAlarm *alarm);
    BOOL (*OSSetAlarm)(OSAlarm *alarm, OSTime time, OSAlarmCallback callback);
    void (*OSSetAlarmUserData)(OSAlarm *alarm, void *data);
} ImportsCoreInitAlarm;

#ifdef __cplusplus
}
#endif
