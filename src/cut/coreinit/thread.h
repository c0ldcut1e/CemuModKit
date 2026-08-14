#pragma once

#include <time.h>

#include "../cut.h"
#include "alarm.h"
#include "context.h"
#include "exception.h"
#include "threadqueue.h"
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSFastMutex OSFastMutex;
typedef struct OSFastMutexQueue OSFastMutexQueue;
typedef struct OSMutex OSMutex;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSThread OSThread;
typedef struct OSTLSSection OSTLSSection;
typedef struct OSThreadGHSExceptionHandling OSThreadGHSExceptionHandling;

//! A value from enum OS_THREAD_STATE.
typedef uint8_t OSThreadState;

//! A value from enum OS_THREAD_REQUEST.
typedef uint32_t OSThreadRequest;

//! A bitfield of enum OS_THREAD_ATTRIB.
typedef uint8_t OSThreadAttributes;

//! A bitfield of enum OS_THREAD_TYPE.
typedef uint32_t OSThreadType;

typedef int (*OSThreadEntryPointFn)(int argc, const char **argv);
typedef void (*OSThreadCleanupCallbackFn)(OSThread *thread, void *stack);
typedef void (*OSThreadDeallocatorFn)(OSThread *thread, void *stack);

typedef enum OSThreadSpecificID
{
    //! These can be used by applications
    OS_THREAD_SPECIFIC_0  = 0,
    OS_THREAD_SPECIFIC_1  = 1,
    OS_THREAD_SPECIFIC_2  = 2,
    OS_THREAD_SPECIFIC_3  = 3,
    OS_THREAD_SPECIFIC_4  = 4,
    OS_THREAD_SPECIFIC_5  = 5,
    OS_THREAD_SPECIFIC_6  = 6,
    OS_THREAD_SPECIFIC_7  = 7,
    OS_THREAD_SPECIFIC_8  = 8,
    OS_THREAD_SPECIFIC_9  = 9,
    OS_THREAD_SPECIFIC_10 = 10,
    OS_THREAD_SPECIFIC_11 = 11,
    OS_THREAD_SPECIFIC_12 = 12,
    OS_THREAD_SPECIFIC_13 = 13,
    //! These are reserved to cut for internal use
    OS_THREAD_SPECIFIC_CUT_RESERVED_0 = 14,
    OS_THREAD_SPECIFIC_CUT_RESERVED_1 = 15,
} OSThreadSpecificID;

enum OS_THREAD_STATE
{
    OS_THREAD_STATE_NONE = 0,

    //! Thread is ready to run
    OS_THREAD_STATE_READY = 1 << 0,

    //! Thread is running
    OS_THREAD_STATE_RUNNING = 1 << 1,

    //! Thread is waiting, i.e. on a mutex
    OS_THREAD_STATE_WAITING = 1 << 2,

    //! Thread is about to terminate
    OS_THREAD_STATE_MORIBUND = 1 << 3,
};

enum OS_THREAD_REQUEST
{
    OS_THREAD_REQUEST_NONE    = 0,
    OS_THREAD_REQUEST_SUSPEND = 1,
    OS_THREAD_REQUEST_CANCEL  = 2,
};

enum OS_THREAD_ATTRIB
{
    //! Allow the thread to run on CPU0.
    OS_THREAD_ATTRIB_AFFINITY_CPU0 = 1 << 0,

    //! Allow the thread to run on CPU1.
    OS_THREAD_ATTRIB_AFFINITY_CPU1 = 1 << 1,

    //! Allow the thread to run on CPU2.
    OS_THREAD_ATTRIB_AFFINITY_CPU2 = 1 << 2,

    //! Allow the thread to run any CPU.
    OS_THREAD_ATTRIB_AFFINITY_ANY = ((1 << 0) | (1 << 1) | (1 << 2)),

    //! Start the thread detached.
    OS_THREAD_ATTRIB_DETACHED = 1 << 3,

    //! Enables tracking of stack usage.
    OS_THREAD_ATTRIB_STACK_USAGE = 1 << 5,

    OS_THREAD_ATTRIB_UNKNOWN = 1 << 7
};

enum OS_THREAD_TYPE
{
    OS_THREAD_TYPE_DRIVER = 0,
    OS_THREAD_TYPE_IO     = 1,
    OS_THREAD_TYPE_APP    = 2
};

struct CUT_PACKED OSThreadGHSExceptionHandling
{
    CUT_UNKNOWN_BYTES(0x68);
    void *eh_globals;
    void *eh_mem_manage[9];
    void *eh_store_globals[6];
    void *eh_store_globals_tdeh[76];
};
CUT_CHECK_OFFSET(OSThreadGHSExceptionHandling, 0x68, eh_globals);
CUT_CHECK_OFFSET(OSThreadGHSExceptionHandling, 0x6c, eh_mem_manage);
CUT_CHECK_OFFSET(OSThreadGHSExceptionHandling, 0x90, eh_store_globals);
CUT_CHECK_OFFSET(OSThreadGHSExceptionHandling, 0xa8, eh_store_globals_tdeh);
CUT_CHECK_SIZE(OSThreadGHSExceptionHandling, 0x1d8);

struct OSMutexQueue
{
    OSMutex *head;
    OSMutex *tail;
    void *parent;
    CUT_UNKNOWN_BYTES(4);
};
CUT_CHECK_OFFSET(OSMutexQueue, 0x0, head);
CUT_CHECK_OFFSET(OSMutexQueue, 0x4, tail);
CUT_CHECK_OFFSET(OSMutexQueue, 0x8, parent);
CUT_CHECK_SIZE(OSMutexQueue, 0x10);

struct OSFastMutexQueue
{
    OSFastMutex *head;
    OSFastMutex *tail;
};
CUT_CHECK_OFFSET(OSFastMutexQueue, 0x00, head);
CUT_CHECK_OFFSET(OSFastMutexQueue, 0x04, tail);
CUT_CHECK_SIZE(OSFastMutexQueue, 0x08);

struct OSTLSSection
{
    void *data;
    CUT_UNKNOWN_BYTES(4);
};
CUT_CHECK_OFFSET(OSTLSSection, 0x00, data);
CUT_CHECK_SIZE(OSTLSSection, 0x08);

#define OS_THREAD_TAG 0x74487244u
#pragma pack(push, 1)
struct CUT_ALIGNAS(8) OSThread
{
    OSContext context;

    //! Should always be set to the value OS_THREAD_TAG.
    uint32_t tag;

    //! Bitfield of OS_THREAD_STATE
    OSThreadState state;

    //! Bitfield of OS_THREAD_ATTRIB
    OSThreadAttributes attr;

    //! Unique thread ID
    uint16_t id;

    //! Suspend count (increased by OSSuspendThread).
    int suspendCounter;

    //! Actual priority of thread.
    int priority;

    //! Base priority of thread, 0 is highest priority, 31 is lowest priority.
    int basePriority;

    //! Exit value
    int exitValue;

    //! Core run queue stuff
    OSThreadQueue *coreRunQueue[3];
    OSThreadLink coreRunQueueLink[3];

    //! Queue the thread is currently waiting on
    OSThreadQueue *queue;

    //! Link used for thread queue
    OSThreadLink link;

    //! Queue of threads waiting to join this thread
    OSThreadQueue joinQueue;

    //! Mutex this thread is waiting to lock
    OSMutex *mutex;

    //! Queue of mutexes this thread owns
    OSMutexQueue mutexQueue;

    //! Link for global active thread queue
    OSThreadLink activeLink;

    //! Stack start (top, highest address)
    void *stackStart;

    //! Stack end (bottom, lowest address)
    void *stackEnd;

    //! Thread entry point
    OSThreadEntryPointFn entryPoint;

    //! GHS Exception handling thread-specifics
    OSThreadGHSExceptionHandling ghsExceptionHandling;

    BOOL alarmCancelled;

    //! Thread specific values, accessed with OSSetThreadSpecific and OSGetThreadSpecific.
    void *specific[0x10];

    OSThreadType type;

    //! Thread name, accessed with OSSetThreadName and OSGetThreadName.
    const char *name;

    OSAlarm *waitEventTimeoutAlarm;

    //! The stack pointer passed in OSCreateThread.
    void *userStackPointer;

    //! Called just before thread is terminated, set with OSSetThreadCleanupCallback
    OSThreadCleanupCallbackFn cleanupCallback;

    //! Called just after a thread is terminated, set with OSSetThreadDeallocator
    OSThreadDeallocatorFn deallocator;

    //! If TRUE then a thread can be cancelled or suspended, set with OSSetThreadCancelState
    BOOL cancelState;

    //! Current thread request, used for cancelleing and suspending the thread.
    OSThreadRequest requestFlag;

    //! Pending suspend request count
    int needSuspend;

    //! Result of thread suspend
    int suspendResult;

    //! Queue of threads waiting for a thread to be suspended.
    OSThreadQueue suspendQueue;

    CUT_UNKNOWN_BYTES(0x4);

    //! How many ticks the thread should run for before suspension.
    int64_t runQuantumTicks;

    //! The total amount of core time consumed by this thread (Does not include time while Running)
    uint64_t coreTimeConsumedNs;

    //! The number of times this thread has been awoken.
    uint64_t wakeCount;

    OSTime unk0x610;
    OSTime unk0x618;
    OSTime unk0x620;
    OSTime unk0x628;

    //! Callback for DSI exception
    OSExceptionCallbackFn dsiCallback[3];
    //! Callback for ISI exception
    OSExceptionCallbackFn isiCallback[3];
    //! Callback for Program exception
    OSExceptionCallbackFn programCallback[3];
    //! Callback for PerfMon exception
    OSExceptionCallbackFn perfMonCallback[3];

    //! Checks for synchronization objects placed on stack in debug mode when set to true.
    BOOL stackSyncObjAllowed;

    //! Number of TLS sections
    uint16_t tlsSectionCount;

    CUT_UNKNOWN_BYTES(0x2);

    //! TLS Sections
    OSTLSSection *tlsSections;

    //! The fast mutex we are currently waiting for
    OSFastMutex *fastMutex;

    //! The fast mutexes we are currently contended on
    OSFastMutexQueue contendedFastMutexes;

    //! The fast mutexes we currently own locks on
    OSFastMutexQueue fastMutexQueue;

    //! Callback for Alignment exception
    OSExceptionCallbackFn alignCallback[3];

    //! Cleared on thread creation but never used
    uint32_t reserved[5];
};
#pragma pack(pop)
CUT_CHECK_OFFSET(OSThread, 0x320, tag);
CUT_CHECK_OFFSET(OSThread, 0x324, state);
CUT_CHECK_OFFSET(OSThread, 0x325, attr);
CUT_CHECK_OFFSET(OSThread, 0x326, id);
CUT_CHECK_OFFSET(OSThread, 0x328, suspendCounter);
CUT_CHECK_OFFSET(OSThread, 0x32c, priority);
CUT_CHECK_OFFSET(OSThread, 0x330, basePriority);
CUT_CHECK_OFFSET(OSThread, 0x334, exitValue);
CUT_CHECK_OFFSET(OSThread, 0x338, coreRunQueue);
CUT_CHECK_OFFSET(OSThread, 0x344, coreRunQueueLink);
CUT_CHECK_OFFSET(OSThread, 0x35c, queue);
CUT_CHECK_OFFSET(OSThread, 0x360, link);
CUT_CHECK_OFFSET(OSThread, 0x368, joinQueue);
CUT_CHECK_OFFSET(OSThread, 0x378, mutex);
CUT_CHECK_OFFSET(OSThread, 0x37c, mutexQueue);
CUT_CHECK_OFFSET(OSThread, 0x38c, activeLink);
CUT_CHECK_OFFSET(OSThread, 0x394, stackStart);
CUT_CHECK_OFFSET(OSThread, 0x398, stackEnd);
CUT_CHECK_OFFSET(OSThread, 0x39c, entryPoint);
CUT_CHECK_OFFSET(OSThread, 0x3a0, ghsExceptionHandling);
CUT_CHECK_OFFSET(OSThread, 0x57c, specific);
CUT_CHECK_OFFSET(OSThread, 0x5bc, type);
CUT_CHECK_OFFSET(OSThread, 0x5c0, name);
CUT_CHECK_OFFSET(OSThread, 0x5c4, waitEventTimeoutAlarm);
CUT_CHECK_OFFSET(OSThread, 0x5c8, userStackPointer);
CUT_CHECK_OFFSET(OSThread, 0x5cc, cleanupCallback);
CUT_CHECK_OFFSET(OSThread, 0x5d0, deallocator);
CUT_CHECK_OFFSET(OSThread, 0x5d4, cancelState);
CUT_CHECK_OFFSET(OSThread, 0x5d8, requestFlag);
CUT_CHECK_OFFSET(OSThread, 0x5dc, needSuspend);
CUT_CHECK_OFFSET(OSThread, 0x5e0, suspendResult);
CUT_CHECK_OFFSET(OSThread, 0x5e4, suspendQueue);
CUT_CHECK_OFFSET(OSThread, 0x5f8, runQuantumTicks);
CUT_CHECK_OFFSET(OSThread, 0x600, coreTimeConsumedNs);
CUT_CHECK_OFFSET(OSThread, 0x608, wakeCount);
CUT_CHECK_OFFSET(OSThread, 0x610, unk0x610);
CUT_CHECK_OFFSET(OSThread, 0x618, unk0x618);
CUT_CHECK_OFFSET(OSThread, 0x620, unk0x620);
CUT_CHECK_OFFSET(OSThread, 0x628, unk0x628);
CUT_CHECK_OFFSET(OSThread, 0x630, dsiCallback);
CUT_CHECK_OFFSET(OSThread, 0x63c, isiCallback);
CUT_CHECK_OFFSET(OSThread, 0x648, programCallback);
CUT_CHECK_OFFSET(OSThread, 0x654, perfMonCallback);
CUT_CHECK_OFFSET(OSThread, 0x664, tlsSectionCount);
CUT_CHECK_OFFSET(OSThread, 0x668, tlsSections);
CUT_CHECK_OFFSET(OSThread, 0x66c, fastMutex);
CUT_CHECK_OFFSET(OSThread, 0x670, contendedFastMutexes);
CUT_CHECK_OFFSET(OSThread, 0x678, fastMutexQueue);
CUT_CHECK_OFFSET(OSThread, 0x680, alignCallback);
CUT_CHECK_OFFSET(OSThread, 0x68c, reserved);
CUT_CHECK_SIZE(OSThread, 0x6a0);

/**
 * Cancels a thread.
 *
 * This sets the threads requestFlag to OS_THREAD_REQUEST_CANCEL, the thread will
 * be terminated next time OSTestThreadCancel is called.
 */
CUT_IMPORT void (*OSCancelThread)(OSThread *thread);

/**
 * Returns the count of active threads.
 */
CUT_IMPORT int (*OSCheckActiveThreads)();

/**
 * Get the maximum amount of stack the thread has used.
 */
CUT_IMPORT int (*OSCheckThreadStackUsage)(OSThread *thread);

/**
 * Disable tracking of thread stack usage.
 */
CUT_IMPORT void (*OSClearThreadStackUsage)(OSThread *thread);

/**
 * Clears a thread's suspend counter and resumes it.
 */
CUT_IMPORT void (*OSContinueThread)(OSThread *thread);

/**
 * Create a new thread.
 *
 * \param thread Thread to initialise.
 * \param entry Thread entry point.
 * \param argc argc argument passed to entry point.
 * \param argv argv argument passed to entry point.
 * \param stack Top of stack (highest address).
 * \param stackSize Size of stack.
 * \param priority Thread priority, 0 is highest priorty, 31 is lowest.
 * \param attributes Thread attributes, see OSThreadAttributes.
 */
CUT_IMPORT BOOL (*OSCreateThread)(OSThread *thread, OSThreadEntryPointFn entry, int argc, char *argv, void *stack, uint32_t stackSize, int priority,
                                  OSThreadAttributes attributes);

/**
 * Detach thread.
 */
CUT_IMPORT void (*OSDetachThread)(OSThread *thread);

/**
 * Exit the current thread with a exit code.
 *
 * This function is implicitly called when the thread entry point returns.
 */
CUT_IMPORT void (*OSExitThread)(int result);

/**
 * Get the next and previous thread in the thread's active queue.
 */
CUT_IMPORT void (*OSGetActiveThreadLink)(OSThread *thread, OSThreadLink *link);

/**
 * Return pointer to OSThread object for the current thread.
 */
CUT_IMPORT OSThread *(*OSGetCurrentThread)();

/**
 * Returns the default thread for a specific core.
 *
 * Each core has 1 default thread created before the game boots. The default
 * thread for core 1 calls the RPX entry point, the default threads for core 0
 * and 2 are suspended and can be used with OSRunThread.
 */
CUT_IMPORT OSThread *(*OSGetDefaultThread)(uint32_t coreID);

/**
 * Return current stack pointer, value of r1 register.
 */
CUT_IMPORT uint32_t (*OSGetStackPointer)();

/**
 * Get a thread's affinity.
 */
CUT_IMPORT uint32_t (*OSGetThreadAffinity)(OSThread *thread);

/**
 * Get a thread's name.
 */
CUT_IMPORT const char *(*OSGetThreadName)(OSThread *thread);

/**
 * Get a thread's base priority.
 */
CUT_IMPORT int (*OSGetThreadPriority)(OSThread *thread);

/**
 * Get a thread's specific value set by OSSetThreadSpecific.
 */
CUT_IMPORT void *(*OSGetThreadSpecific)(OSThreadSpecificID id);

/**
 * Returns TRUE if a thread is suspended.
 */
CUT_IMPORT BOOL (*OSIsThreadSuspended)(OSThread *thread);

/**
 * Returns TRUE if a thread is terminated.
 */
CUT_IMPORT BOOL (*OSIsThreadTerminated)(OSThread *thread);

/**
 * Wait until thread is terminated.
 *
 * If the target thread is detached, returns FALSE.
 *
 * \param thread Thread to wait for
 * \param threadResult Pointer to store thread exit value in.
 * \returns Returns TRUE if thread has terminated, FALSE if thread is detached.
 */
CUT_IMPORT BOOL (*OSJoinThread)(OSThread *thread, int *threadResult);

/**
 * Resumes a thread.
 *
 * Decrements the thread's suspend counter, if the counter reaches 0 the thread
 * is resumed.
 *
 * \returns Returns the previous value of the suspend counter.
 */
CUT_IMPORT int (*OSResumeThread)(OSThread *thread);

/**
 * Run a function on an already created thread.
 *
 * Can only be used on idle threads.
 */
CUT_IMPORT BOOL (*OSRunThread)(OSThread *thread, OSThreadEntryPointFn entry, int argc, const char **argv);

/**
 * Set a thread's affinity.
 */
CUT_IMPORT BOOL (*OSSetThreadAffinity)(OSThread *thread, uint32_t affinity);

/**
 * Set a thread's cancellation state.
 *
 * If the state is TRUE then the thread can be suspended or cancelled when
 * OSTestThreadCancel is called.
 */
CUT_IMPORT BOOL (*OSSetThreadCancelState)(BOOL state);

/**
 * Set the callback to be called just before a thread is terminated.
 */
CUT_IMPORT
OSThreadCleanupCallbackFn (*OSSetThreadCleanupCallback)(OSThread *thread, OSThreadCleanupCallbackFn callback);

/**
 * Set the callback to be called just after a thread is terminated.
 */
CUT_IMPORT
OSThreadDeallocatorFn (*OSSetThreadDeallocator)(OSThread *thread, OSThreadDeallocatorFn deallocator);

/**
 * Set a thread's name.
 */
CUT_IMPORT void (*OSSetThreadName)(OSThread *thread, const char *name);

/**
 * Set a thread's priority.
 */
CUT_IMPORT BOOL (*OSSetThreadPriority)(OSThread *thread, int priority);

/**
 * Set a thread's run quantum.
 *
 * This is the maximum amount of time the thread can run for before being forced
 * to yield.
 */
CUT_IMPORT BOOL (*OSSetThreadRunQuantum)(OSThread *thread, uint32_t quantum);

/**
 * Set a thread specific value.
 *
 * Can be read with OSGetThreadSpecific.
 */
CUT_IMPORT void (*OSSetThreadSpecific)(OSThreadSpecificID id, void *value);

/**
 * Set thread stack usage tracking.
 */
CUT_IMPORT BOOL (*OSSetThreadStackUsage)(OSThread *thread);

/**
 * Sleep the current thread and add it to a thread queue.
 *
 * Will sleep until the thread queue is woken with OSWakeupThread.
 */
CUT_IMPORT void (*OSSleepThread)(OSThreadQueue *queue);

/**
 * Sleep the current thread for a period of time.
 */
CUT_IMPORT void (*OSSleepTicks)(OSTime ticks);

/**
 * Suspend a thread.
 *
 * Increases a thread's suspend counter, if the counter is >0 then the thread is
 * suspended.
 *
 * \returns Returns the thread's previous suspend counter value
 */
CUT_IMPORT uint32_t (*OSSuspendThread)(OSThread *thread);

CUT_IMPORT void (*__OSSuspendThreadNolock)(OSThread *thread);

/**
 * Check to see if the current thread should be cancelled or suspended.
 *
 * This is implicitly called in:
 * - OSLockMutex
 * - OSTryLockMutex
 * - OSUnlockMutex
 * - OSAcquireSpinLock
 * - OSTryAcquireSpinLock
 * - OSTryAcquireSpinLockWithTimeout
 * - OSReleaseSpinLock
 * - OSCancelThread
 */
CUT_IMPORT void (*OSTestThreadCancel)();

/**
 * Wake up all threads in queue.
 *
 * Clears the thread queue.
 */
CUT_IMPORT void (*OSWakeupThread)(OSThreadQueue *queue);

/**
 * Yield execution to waiting threads with same priority.
 *
 * This will never switch to a thread with a lower priority than the current
 * thread.
 */
CUT_IMPORT void (*OSYieldThread)();

#ifdef __cplusplus
}
#endif
