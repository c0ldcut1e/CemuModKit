#pragma once
#include "../cut.h"

/**
 * \defgroup gx2_context Context State
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2ShadowState GX2ShadowState;
typedef struct GX2ContextState GX2ContextState;

struct GX2ShadowState
{
    uint32_t config[0xB00];
    uint32_t context[0x400];
    uint32_t alu[0x800];
    uint32_t loop[0x60];
    CUT_PADDING_BYTES((0x80 - 0x60) * 4);
    uint32_t resource[0xD9E];
    CUT_PADDING_BYTES((0xDC0 - 0xD9E) * 4);
    uint32_t sampler[0xA2];
    CUT_PADDING_BYTES((0xC0 - 0xA2) * 4);
};
CUT_CHECK_OFFSET(GX2ShadowState, 0x0000, config);
CUT_CHECK_OFFSET(GX2ShadowState, 0x2C00, context);
CUT_CHECK_OFFSET(GX2ShadowState, 0x3C00, alu);
CUT_CHECK_OFFSET(GX2ShadowState, 0x5C00, loop);
CUT_CHECK_OFFSET(GX2ShadowState, 0x5E00, resource);
CUT_CHECK_OFFSET(GX2ShadowState, 0x9500, sampler);
CUT_CHECK_SIZE(GX2ShadowState, 0x9800);

struct GX2ContextState
{
    GX2ShadowState shadowState;
    CUT_UNKNOWN_BYTES(4);
    uint32_t shadowDisplayListSize;
    CUT_UNKNOWN_BYTES(0x9e00 - 0x9808);
    uint32_t shadowDisplayList[192];
};
CUT_CHECK_OFFSET(GX2ContextState, 0x0000, shadowState);
CUT_CHECK_OFFSET(GX2ContextState, 0x9804, shadowDisplayListSize);
CUT_CHECK_OFFSET(GX2ContextState, 0x9e00, shadowDisplayList);
CUT_CHECK_SIZE(GX2ContextState, 0xa100);

CUT_IMPORT void (*GX2SetupContextStateEx)(GX2ContextState *state, BOOL unk1);

CUT_IMPORT void (*GX2GetContextStateDisplayList)(const GX2ContextState *state, void *outDisplayList, uint32_t *outSize);

CUT_IMPORT void (*GX2SetContextState)(GX2ContextState *state);

CUT_IMPORT void (*GX2SetDefaultState)(void);

#ifdef __cplusplus
}
#endif

/** @} */
