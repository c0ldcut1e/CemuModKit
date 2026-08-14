#pragma once

#include "../cut.h"
#include "context.h"
#include "threadqueue.h"
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSAlarm OSAlarm;
typedef struct OSAlarmLink OSAlarmLink;
typedef struct OSAlarmQueue OSAlarmQueue;

typedef void (*OSAlarmCallback)(OSAlarm *, OSContext *);

#define OS_ALARM_QUEUE_TAG 0x614C6D51u

struct OSAlarmQueue
{
    //! Should always be set to the value OS_ALARM_QUEUE_TAG.
    uint32_t tag;

    //! Name set by OSInitAlarmQueueEx
    const char *name;
    CUT_UNKNOWN_BYTES(4);

    OSThreadQueue threadQueue;
    OSAlarm *head;
    OSAlarm *tail;
};
CUT_CHECK_OFFSET(OSAlarmQueue, 0x00, tag);
CUT_CHECK_OFFSET(OSAlarmQueue, 0x04, name);
CUT_CHECK_OFFSET(OSAlarmQueue, 0x0c, threadQueue);
CUT_CHECK_OFFSET(OSAlarmQueue, 0x1c, head);
CUT_CHECK_OFFSET(OSAlarmQueue, 0x20, tail);
CUT_CHECK_SIZE(OSAlarmQueue, 0x24);

struct OSAlarmLink
{
    OSAlarm *prev;
    OSAlarm *next;
};
CUT_CHECK_OFFSET(OSAlarmLink, 0x00, prev);
CUT_CHECK_OFFSET(OSAlarmLink, 0x04, next);
CUT_CHECK_SIZE(OSAlarmLink, 0x08);

#define OS_ALARM_TAG 0x614C724Du
struct OSAlarm
{
    //! Should always be set to the value OS_ALARM_TAG.
    uint32_t tag;

    //! Name set from OSCreateAlarmEx.
    const char *name;

    CUT_UNKNOWN_BYTES(4);

    //! The callback to execute once the alarm is triggered.
    OSAlarmCallback callback;

    //! Used with OSCancelAlarms for bulk cancellation of alarms.
    uint32_t group;

    CUT_UNKNOWN_BYTES(4);

    //! The time when the alarm will next be triggered.
    OSTime nextFire;

    //! Link used for when this OSAlarm object is inside an OSAlarmQueue
    OSAlarmLink link;

    //! The period between alarm triggers, this is only set for periodic alarms.
    OSTime period;

    //! The time the alarm was started.
    OSTime start;

    //! User data set with OSSetAlarmUserData and retrieved with OSGetAlarmUserData.
    void *userData;

    //! The current state of the alarm, internal values.
    uint32_t state;

    //! Queue of threads currently waiting for the alarm to trigger with OSWaitAlarm.
    OSThreadQueue threadQueue;

    //! The queue that this alarm is currently in.
    OSAlarmQueue *alarmQueue;

    //! The context the alarm was triggered on.
    OSContext *context;
};
CUT_CHECK_OFFSET(OSAlarm, 0x00, tag);
CUT_CHECK_OFFSET(OSAlarm, 0x04, name);
CUT_CHECK_OFFSET(OSAlarm, 0x0c, callback);
CUT_CHECK_OFFSET(OSAlarm, 0x10, group);
CUT_CHECK_OFFSET(OSAlarm, 0x18, nextFire);
CUT_CHECK_OFFSET(OSAlarm, 0x20, link);
CUT_CHECK_OFFSET(OSAlarm, 0x28, period);
CUT_CHECK_OFFSET(OSAlarm, 0x30, start);
CUT_CHECK_OFFSET(OSAlarm, 0x38, userData);
CUT_CHECK_OFFSET(OSAlarm, 0x3c, state);
CUT_CHECK_OFFSET(OSAlarm, 0x40, threadQueue);
CUT_CHECK_OFFSET(OSAlarm, 0x50, alarmQueue);
CUT_CHECK_OFFSET(OSAlarm, 0x54, context);
CUT_CHECK_SIZE(OSAlarm, 0x58);

/**
 * Cancel an alarm.
 */
CUT_IMPORT BOOL (*OSCancelAlarm)(OSAlarm *alarm);

/**
 * Initialise an alarm structure.
 */
CUT_IMPORT void (*OSCreateAlarm)(OSAlarm *alarm);

/**
 * Return user data set by OSSetAlarmUserData.
 */
CUT_IMPORT void *(*OSGetAlarmUserData)(OSAlarm *alarm);

/**
 * Set a one shot alarm to perform a callback after a set amount of time.
 *
 * \param alarm The alarm to set.
 * \param time The duration until the alarm should be triggered.
 * \param callback The alarm callback to call when the alarm is triggered.
 */
CUT_IMPORT BOOL (*OSSetAlarm)(OSAlarm *alarm, OSTime time, OSAlarmCallback callback);

/**
 * Set alarm user data which is returned by OSGetAlarmUserData.
 */
CUT_IMPORT void (*OSSetAlarmUserData)(OSAlarm *alarm, void *data);

#ifdef __cplusplus
}
#endif
