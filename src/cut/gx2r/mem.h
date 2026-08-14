#pragma once
#include "../cut.h"
#include "resource.h"

/**
 * \defgroup gx2r_mem Memory
 * \ingroup gx2r
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*GX2RAllocFunction)(GX2RResourceFlags, uint32_t, uint32_t);
typedef void (*GX2RFreeFunction)(GX2RResourceFlags, void *);

#ifdef __cplusplus
}
#endif

/** @} */
