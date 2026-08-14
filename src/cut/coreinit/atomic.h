#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

CUT_IMPORT BOOL (*OSCompareAndSwapAtomicEx)(volatile uint32_t *ptr, uint32_t compare, uint32_t value, uint32_t *old);

#ifdef __cplusplus
}
#endif
