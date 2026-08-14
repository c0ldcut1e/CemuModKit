#pragma once

#include "../aperture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Aperture
{
    void (*GX2AllocateTilingApertureEx)(GX2Surface *surface, uint32_t level, uint32_t depth, GX2EndianSwapMode endian, GX2ApertureHandle *outHandle,
                                        void **outAddress);
    void (*GX2FreeTilingAperture)(GX2ApertureHandle handle);
} ImportsGX2Aperture;

#ifdef __cplusplus
}
#endif
