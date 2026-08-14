#pragma once

#include "../tessellation.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Tessellation
{
    void (*GX2SetTessellation)(GX2TessellationMode tessellationMode, GX2PrimitiveMode primitiveMode, GX2IndexType indexType);
    void (*GX2SetMinTessellationLevel)(float min);
    void (*GX2SetMaxTessellationLevel)(float max);
} ImportsGX2Tessellation;

#ifdef __cplusplus
}
#endif
