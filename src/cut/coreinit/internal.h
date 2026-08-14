#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

CUT_IMPORT int (*__os_snprintf)(char *buf, size_t n, const char *format, ...);

#ifdef __cplusplus
}
#endif
