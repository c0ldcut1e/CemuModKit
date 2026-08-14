#include <stdio.h>
#include <string.h>

#include "../coreinit/debug.h"
#include "../coreinit/exit.h"
#include "../coreinit/internal.h"
#include "cut_newlib.h"

extern void __fini_cut(void);

void __cut__abort(void)
{
    const char *error_text = "Abort called.\n";
    if (OSIsDebuggerPresent())
    {
        __asm__ __volatile__("mr 3, %0\n"      // load 'tmp' into r3
                             "tw 0x1f, 31, 31" // DBGSTR_INSTRUCTION
                             :
                             : "r"(error_text)
                             : "r3");
    }
    OSFatal(error_text);
    /* NOTREACHED */
    while (1);
}

void __cut__assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
    char tmp[512]    = {};
    char buffer[512] = {};

    __os_snprintf(tmp, sizeof(tmp), "assertion \"%s\" failed:\n file \"%s\", line %d%s%s", failedexpr, file, line, func ? ", function: " : "",
                  func ? func : "");

    // make sure to add a \n every 64 characters to fit on the DRC screen.
    char *target_ptr = buffer;
    int i = 0, j = 0, lineLength = 0;
    while (tmp[i] != '\0' && j < sizeof(buffer) - 2)
    {
        if (tmp[i] == '\n')
        {
            lineLength = 0;
        }
        else if (lineLength >= 64)
        {
            target_ptr[j++] = '\n';
            lineLength      = 0;
        }
        target_ptr[j++] = tmp[i++];
        lineLength++;
    }

    if (OSIsDebuggerPresent())
    {
        __asm__ __volatile__("mr 3, %0\n"      // load 'tmp' into r3
                             "tw 0x1f, 31, 31" // DBGSTR_INSTRUCTION
                             :
                             : "r"(tmp)
                             : "r3");
    }

    OSFatal(buffer);
    /* NOTREACHED */
    while (1);
}

void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr) { return __cut_sbrk_r(ptr, incr); }

struct _reent *__syscall_getreent(void) { return __cut_getreent(); }

int __syscall_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz) { return __cut_gettod_r(ptr, tp, tz); }

int __syscall_nanosleep(const struct timespec *req, struct timespec *rem) { return __cut_nanosleep(req, rem); }

int __syscall_clock_gettime(clockid_t clock_id, struct timespec *tp) { return __cut_clock_gettime(clock_id, tp); }

int __syscall_clock_settime(clockid_t clock_id, const struct timespec *tp) { return __cut_clock_settime(clock_id, tp); }

int __syscall_clock_getres(clockid_t clock_id, struct timespec *res) { return __cut_clock_getres(clock_id, res); }

void __syscall_abort() { __cut__abort(); }

void __syscall_assert_func(const char *file, int line, const char *func, const char *failedexpr) { __cut__assert_func(file, line, func, failedexpr); }

void __fini_cut_newlib() { __fini_cut_sbrk_heap(); }
