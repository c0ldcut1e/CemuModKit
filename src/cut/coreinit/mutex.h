#pragma once

#include "../cut.h"
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSThread OSThread;

typedef struct OSMutex OSMutex;
typedef struct OSMutexLink OSMutexLink;

struct OSMutexLink
{
    OSMutex *next;
    OSMutex *prev;
};
CUT_CHECK_OFFSET(OSMutexLink, 0x00, next);
CUT_CHECK_OFFSET(OSMutexLink, 0x04, prev);
CUT_CHECK_SIZE(OSMutexLink, 0x8);

#define OS_MUTEX_TAG 0x6D557458u

struct OSMutex
{
    //! Should always be set to the value OS_MUTEX_TAG.
    uint32_t tag;

    //! Name set by OSInitMutexEx.
    const char *name;

    CUT_UNKNOWN_BYTES(4);

    //! Queue of threads waiting for this mutex to unlock.
    OSThreadQueue queue;

    //! Current owner of mutex.
    OSThread *owner;

    //! Current recursion lock count of mutex.
    int count;

    //! Link used inside OSThread's mutex queue.
    OSMutexLink link;
};
CUT_CHECK_OFFSET(OSMutex, 0x00, tag);
CUT_CHECK_OFFSET(OSMutex, 0x04, name);
CUT_CHECK_OFFSET(OSMutex, 0x0c, queue);
CUT_CHECK_OFFSET(OSMutex, 0x1c, owner);
CUT_CHECK_OFFSET(OSMutex, 0x20, count);
CUT_CHECK_OFFSET(OSMutex, 0x24, link);
CUT_CHECK_SIZE(OSMutex, 0x2c);

/**
 * Initialise a mutex structure.
 */
CUT_IMPORT void (*OSInitMutex)(OSMutex *mutex);

/**
 * Initialise a mutex structure with a name.
 */
CUT_IMPORT void (*OSInitMutexEx)(OSMutex *mutex, const char *name);

/**
 * Lock the mutex.
 *
 * If no one owns the mutex, set current thread as owner.
 *
 * If the lock is owned by the current thread, increase the recursion count.
 *
 * If the lock is owned by another thread, the current thread will sleep until
 * the owner has unlocked this mutex.
 *
 * Similar to <a href="http://en.cppreference.com/w/cpp/thread/recursive_mutex/lock">std::recursive_mutex::lock</a>.
 */
CUT_IMPORT void (*OSLockMutex)(OSMutex *mutex);

/**
 * Try to lock a mutex.
 *
 * If no one owns the mutex, set current thread as owner.
 *
 * If the lock is owned by the current thread, increase the recursion count.
 *
 * If the lock is owned by another thread, do not block, return FALSE.
 *
 * \return TRUE if the mutex is locked, FALSE if the mutex is owned by another thread.
 *
 * Similar to <a href="http://en.cppreference.com/w/cpp/thread/recursive_mutex/try_lock">std::recursive_mutex::try_lock</a>.
 */
CUT_IMPORT BOOL (*OSTryLockMutex)(OSMutex *mutex);

/**
 * Unlocks the mutex.
 *
 * Will decrease the recursion count, will only unlock the mutex when the
 * recursion count reaches 0.
 *
 * If any other threads are waiting to lock the mutex they will be woken.
 *
 * Similar to <a href="http://en.cppreference.com/w/cpp/thread/recursive_mutex/unlock">std::recursive_mutex::unlock</a>.
 */
CUT_IMPORT void (*OSUnlockMutex)(OSMutex *mutex);

#ifdef __cplusplus
}
#endif
