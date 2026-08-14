#pragma once

#include "../mem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Mem
{
    void (*GX2Invalidate)(GX2InvalidateMode mode, void *buffer, uint32_t size);
} ImportsGX2Mem;

#ifdef __cplusplus
}
#endif
