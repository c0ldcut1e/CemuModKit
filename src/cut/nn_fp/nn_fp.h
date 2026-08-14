#pragma once

#include "../cut.h"
#include "../nn/result.h"

#ifdef __cplusplus

namespace nn::fp
{
    CUT_IMPORT Result (*Initialize)();

    CUT_IMPORT Result (*LoginAsync)(void (*funcPtr)(nn::Result *result, void *userParam), void *userParam);
} // namespace nn::fp

#endif //__cplusplus
