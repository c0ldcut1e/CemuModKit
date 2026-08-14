#pragma once

typedef enum __cut_thread_specific_id
{
    CUT_THREAD_SPECIFIC_0 = 0,
    CUT_THREAD_SPECIFIC_1 = 1,
} __cut_thread_specific_id;

#ifdef __cplusplus
extern "C" {
#endif

void cut_set_thread_specific(__cut_thread_specific_id id, void *value);

void *cut_get_thread_specific(__cut_thread_specific_id id);

#ifdef __cplusplus
}
#endif
