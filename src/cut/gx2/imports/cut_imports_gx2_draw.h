#pragma once

#include "../draw.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2Draw
{
    void (*GX2SetAttribBuffer)(uint32_t index, uint32_t size, uint32_t stride, const void *buffer);
    void (*GX2DrawEx)(GX2PrimitiveMode mode, uint32_t count, uint32_t offset, uint32_t numInstances);
    void (*GX2DrawEx2)(GX2PrimitiveMode mode, uint32_t count, uint32_t offset, uint32_t numInstances, uint32_t baseInstance);
    void (*GX2DrawIndexedEx)(GX2PrimitiveMode mode, uint32_t count, GX2IndexType indexType, const void *indices, uint32_t offset,
                             uint32_t numInstances);
    void (*GX2DrawIndexedEx2)(GX2PrimitiveMode mode, uint32_t count, GX2IndexType indexType, const void *indices, uint32_t offset,
                              uint32_t numInstances, uint32_t baseInstance);
    void (*GX2DrawIndexedImmediateEx)(GX2PrimitiveMode mode, uint32_t count, GX2IndexType indexType, const void *indices, uint32_t offset,
                                      uint32_t numInstances);
    void (*GX2SetPrimitiveRestartIndex)(uint32_t index);
} ImportsGX2Draw;

#ifdef __cplusplus
}
#endif
