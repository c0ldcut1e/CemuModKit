#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets the core executing the current thread.
 *
 * \returns
 * The ID of the current core.
 */
CUT_IMPORT uint32_t (*OSGetCoreId)();

#ifdef __cplusplus
}
#endif
