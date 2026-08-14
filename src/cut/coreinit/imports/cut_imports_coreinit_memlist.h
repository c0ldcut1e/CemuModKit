#pragma once

#include "../memlist.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMemlist
{
    void *(*MEMGetNextListObject)(MEMMemoryList *list, void *object);
} ImportsCoreInitMemlist;

#ifdef __cplusplus
}
#endif
