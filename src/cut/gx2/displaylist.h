#pragma once
#include "../cut.h"

/**
 * \defgroup gx2_displaylist Display List
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

CUT_IMPORT void (*GX2BeginDisplayListEx)(void *displayList, uint32_t bytes, BOOL unk1);

CUT_IMPORT uint32_t (*GX2EndDisplayList)(void *displayList);

CUT_IMPORT void (*GX2DirectCallDisplayList)(const void *displayList, uint32_t bytes);

CUT_IMPORT void (*GX2CallDisplayList)(const void *displayList, uint32_t bytes);

CUT_IMPORT BOOL (*GX2GetDisplayListWriteStatus)(void);

CUT_IMPORT BOOL (*GX2GetCurrentDisplayList)(void **outDisplayList, uint32_t *outSize);

CUT_IMPORT void (*GX2CopyDisplayList)(const void *displayList, uint32_t bytes);

#ifdef __cplusplus
}
#endif

/** @} */
