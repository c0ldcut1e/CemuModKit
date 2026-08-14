#pragma once
#include "../cut.h"
#include "enum.h"
#include <coreinit/time.h>

/**
 * \defgroup gx2_tessellation Tessellation
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

CUT_IMPORT void (*GX2SetTessellation)(GX2TessellationMode tessellationMode, GX2PrimitiveMode primitiveMode, GX2IndexType indexType);

CUT_IMPORT void (*GX2SetMinTessellationLevel)(float min);

CUT_IMPORT void (*GX2SetMaxTessellationLevel)(float max);

#ifdef __cplusplus
}
#endif

/** @} */
