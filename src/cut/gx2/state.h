#pragma once

#include "../cut.h"
#include "enum.h"

/**
 * \defgroup gx2_state State
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

CUT_IMPORT void (*GX2Init)(uint32_t *attributes);

CUT_IMPORT void (*GX2Shutdown)(void);

CUT_IMPORT void (*GX2Flush)(void);

CUT_IMPORT void (*GX2ResetGPU)(uint32_t unknown);

/**
 * @return -1 if GX2 is not running, on success the core where GX2Init has been called is returned.
 */
CUT_IMPORT int (*GX2GetMainCoreId)(void);

#ifdef __cplusplus
}
#endif

/** @} */
