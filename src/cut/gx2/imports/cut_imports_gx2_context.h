#pragma once

#include "../context.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Context
{
    void (*GX2SetupContextStateEx)(GX2ContextState *state, BOOL unk1);
    void (*GX2GetContextStateDisplayList)(const GX2ContextState *state, void *outDisplayList, uint32_t *outSize);
    void (*GX2SetContextState)(GX2ContextState *state);
    void (*GX2SetDefaultState)(void);
} ImportsGX2Context;

#ifdef __cplusplus
}
#endif
