#pragma once

#include "../core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitCore
{
    uint32_t (*OSGetCoreId)(void);
} ImportsCoreInitCore;

#ifdef __cplusplus
}
#endif
