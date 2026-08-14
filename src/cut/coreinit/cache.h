#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Invalidates a range of cached data.
 */
CUT_IMPORT void (*DCInvalidateRange)(void *addr, uint32_t size);

/**
 * Flushes a range of cached data.
 */
CUT_IMPORT void (*DCFlushRange)(void *addr, uint32_t size);

/**
 * Stores a range of cached data.
 */
CUT_IMPORT void (*DCStoreRange)(void *addr, uint32_t size);

/**
 * Flushes a range of cached data without running sync/eieio afterwards.
 */
CUT_IMPORT void (*DCFlushRangeNoSync)(void *addr, uint32_t size);

/**
 * Stores a range of cached data without running sync/eieio afterwards.
 */
CUT_IMPORT void (*DCStoreRangeNoSync)(void *addr, uint32_t size);

/**
 * Zeroes a range of cached data.
 */
CUT_IMPORT void (*DCZeroRange)(void *addr, uint32_t size);

/**
 * Hints that a range of data should be cached soon.
 */
CUT_IMPORT void (*DCTouchRange)(void *addr, uint32_t size);

/**
 * Invalidates a range of cached instructions.
 */
CUT_IMPORT void (*ICInvalidateRange)(void *addr, uint32_t size);

CUT_IMPORT void (*OSMemoryBarrier)();

#ifdef __cplusplus
}
#endif
