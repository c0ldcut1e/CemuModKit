#ifndef __CUT_NEWLIB_H
#define __CUT_NEWLIB_H

#include <sys/errno.h>
#include <sys/iosupport.h>
#include <sys/reent.h>
#include <sys/time.h>

#define __CUT_MAX_KEYS               (128)
#define __CUT_STACK_SIZE             (128 * 1024)

#define __CUT_KEY_THREAD_SPECIFIC_ID CUT_THREAD_SPECIFIC_0

void *__cut_sbrk_r(struct _reent *r, ptrdiff_t incr);
int __cut_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz);
int __cut_clock_gettime(clockid_t clock_id, struct timespec *tp);
int __cut_clock_settime(clockid_t clock_id, const struct timespec *tp);
int __cut_clock_getres(clockid_t clock_id, struct timespec *res);
int __cut_nanosleep(const struct timespec *req, struct timespec *rem);
struct _reent *__cut_getreent(void);

void __fini_cut_sbrk_heap();

#endif // ifndef __CUT_NEWLIB_H
