#pragma once
#include "../cut.h"
#include "resource.h"

/**
 * \defgroup gx2r_buffer Buffer
 * \ingroup gx2r
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2RBuffer GX2RBuffer;

struct GX2RBuffer
{
    GX2RResourceFlags flags;
    uint32_t elemSize;
    uint32_t elemCount;
    void *buffer;
};
CUT_CHECK_SIZE(GX2RBuffer, 0x10);
CUT_CHECK_OFFSET(GX2RBuffer, 0x00, flags);
CUT_CHECK_OFFSET(GX2RBuffer, 0x04, elemSize);
CUT_CHECK_OFFSET(GX2RBuffer, 0x08, elemCount);
CUT_CHECK_OFFSET(GX2RBuffer, 0x0C, buffer);

#ifdef __cplusplus
}
#endif

/** @} */
