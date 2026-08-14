#pragma once

#include "../temp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Temp
{
    uint32_t (*GX2TempGetGPUVersion)(void);
} ImportsGX2Temp;

#ifdef __cplusplus
}
#endif
