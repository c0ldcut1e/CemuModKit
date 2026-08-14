#include "cut_thread_specific.h"
#include "../coreinit/thread.h"
#include "../cut.h"

void __attribute__((weak)) cut_set_thread_specific(__cut_thread_specific_id id, void *value)
{
    OSSetThreadSpecific(OS_THREAD_SPECIFIC_CUT_RESERVED_0 + id - CUT_THREAD_SPECIFIC_0, value);
}

void *__attribute__((weak)) cut_get_thread_specific(__cut_thread_specific_id id)
{
    return OSGetThreadSpecific(OS_THREAD_SPECIFIC_CUT_RESERVED_0 + id - CUT_THREAD_SPECIFIC_0);
    ;
}
