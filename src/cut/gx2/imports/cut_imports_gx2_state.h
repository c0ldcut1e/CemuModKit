#pragma once

#include "../state.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2State
{
    void (*GX2Init)(uint32_t *attributes);
    void (*GX2Shutdown)(void);
    void (*GX2Flush)(void);
    void (*GX2ResetGPU)(uint32_t unknown);
    int (*GX2GetMainCoreId)(void);
} ImportsGX2State;

#ifdef __cplusplus
}
#endif
