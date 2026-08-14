#include <stdlib.h>

#include "../coreinit/thread.h"
#include "cut_newlib.h"
#include "cut_thread_specific.h"

#define __CUT_CONTEXT_THREAD_SPECIFIC_ID CUT_THREAD_SPECIFIC_1

struct __cut_thread_context
{
    struct _reent reent;
    OSThreadCleanupCallbackFn savedCleanup;
};

static void __cut_thread_cleanup(OSThread *thread, void *stack)
{
    struct __cut_thread_context *context;

    context = (struct __cut_thread_context *) cut_get_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID);
    if (!context || &context->reent == _GLOBAL_REENT)
    {
        abort();
    }

    if (context->savedCleanup)
    {
        context->savedCleanup(thread, stack);
    }

    _reclaim_reent(&context->reent);

    // Use global reent during free since the current reent is getting freed
    cut_set_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID, _GLOBAL_REENT);

    free(context);

    cut_set_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID, NULL);
}

struct _reent *__cut_getreent(void)
{
    struct __cut_thread_context *context;

    context = (struct __cut_thread_context *) cut_get_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID);
    if (!context)
    {
        // Temporarily use global reent during context allocation
        cut_set_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID, _GLOBAL_REENT);

        context = (struct __cut_thread_context *) malloc(sizeof(*context));
        if (!context)
        {
            cut_set_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID, NULL);
            return NULL;
        }

        _REENT_INIT_PTR(&context->reent);
        context->savedCleanup = OSSetThreadCleanupCallback(OSGetCurrentThread(), &__cut_thread_cleanup);

        cut_set_thread_specific(__CUT_CONTEXT_THREAD_SPECIFIC_ID, context);
    }

    return &context->reent;
}
