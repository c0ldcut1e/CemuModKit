#pragma once

#include "../thread.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitThread
{
    void (*OSCancelThread)(OSThread *thread);
    int (*OSCheckActiveThreads)(void);
    int (*OSCheckThreadStackUsage)(OSThread *thread);
    void (*OSClearThreadStackUsage)(OSThread *thread);
    void (*OSContinueThread)(OSThread *thread);
    BOOL (*OSCreateThread)(OSThread *thread, OSThreadEntryPointFn entry, int argc, char *argv, void *stack, uint32_t stackSize, int priority,
                           OSThreadAttributes attributes);
    void (*OSDetachThread)(OSThread *thread);
    void (*OSExitThread)(int result);
    void (*OSGetActiveThreadLink)(OSThread *thread, OSThreadLink *link);
    OSThread *(*OSGetCurrentThread)(void);
    OSThread *(*OSGetDefaultThread)(uint32_t coreID);
    uint32_t (*OSGetStackPointer)(void);
    uint32_t (*OSGetThreadAffinity)(OSThread *thread);
    const char *(*OSGetThreadName)(OSThread *thread);
    int (*OSGetThreadPriority)(OSThread *thread);
    void *(*OSGetThreadSpecific)(OSThreadSpecificID id);
    BOOL (*OSIsThreadSuspended)(OSThread *thread);
    BOOL (*OSIsThreadTerminated)(OSThread *thread);
    BOOL (*OSJoinThread)(OSThread *thread, int *threadResult);
    int (*OSResumeThread)(OSThread *thread);
    BOOL (*OSRunThread)(OSThread *thread, OSThreadEntryPointFn entry, int argc, const char **argv);
    BOOL (*OSSetThreadAffinity)(OSThread *thread, uint32_t affinity);
    BOOL (*OSSetThreadCancelState)(BOOL state);
    OSThreadCleanupCallbackFn (*OSSetThreadCleanupCallback)(OSThread *thread, OSThreadCleanupCallbackFn callback);
    OSThreadDeallocatorFn (*OSSetThreadDeallocator)(OSThread *thread, OSThreadDeallocatorFn deallocator);
    void (*OSSetThreadName)(OSThread *thread, const char *name);
    BOOL (*OSSetThreadPriority)(OSThread *thread, int priority);
    BOOL (*OSSetThreadRunQuantum)(OSThread *thread, uint32_t quantum);
    void (*OSSetThreadSpecific)(OSThreadSpecificID id, void *value);
    BOOL (*OSSetThreadStackUsage)(OSThread *thread);
    void (*OSSleepThread)(OSThreadQueue *queue);
    void (*OSSleepTicks)(OSTime ticks);
    uint32_t (*OSSuspendThread)(OSThread *thread);
    void (*__OSSuspendThreadNolock)(OSThread *thread);
    void (*OSTestThreadCancel)(void);
    void (*OSWakeupThread)(OSThreadQueue *queue);
    void (*OSYieldThread)(void);
} ImportsCoreInitThread;

#ifdef __cplusplus
}
#endif
