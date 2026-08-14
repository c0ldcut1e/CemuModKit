#pragma once

#include "../exception.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitException
{
    OSExceptionCallbackFn (*OSSetExceptionCallback)(OSExceptionType exceptionType, OSExceptionCallbackFn callback);
    OSExceptionCallbackFn (*OSSetExceptionCallbackEx)(OSExceptionMode mode, OSExceptionType exceptionType, OSExceptionCallbackFn callback);
} ImportsCoreInitException;

#ifdef __cplusplus
}
#endif
