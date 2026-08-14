#pragma once

#include "../internal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitInternal
{
    int (*__os_snprintf)(char *buf, size_t n, const char *format, ...);
} ImportsCoreInitInternal;

#ifdef __cplusplus
}
#endif
