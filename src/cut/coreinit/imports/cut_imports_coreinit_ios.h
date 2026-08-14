#pragma once

#include "../ios.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitIos
{
    IOSError (*IOS_Open)(const char *device, IOSOpenMode mode);
    IOSError (*IOS_Close)(IOSHandle handle);
    IOSError (*IOS_Ioctl)(IOSHandle handle, uint32_t request, void *inBuf, uint32_t inLen, void *outBuf, uint32_t outLen);
    IOSError (*IOS_IoctlAsync)(IOSHandle handle, uint32_t request, void *inBuf, uint32_t inLen, void *outBuf, uint32_t outLen,
                               IOSAsyncCallbackFn callback, void *context);
    IOSError (*IOS_Ioctlv)(IOSHandle handle, uint32_t request, uint32_t vecIn, uint32_t vecOut, IOSVec *vec);
    IOSError (*IOS_IoctlvAsync)(IOSHandle handle, uint32_t request, uint32_t vecIn, uint32_t vecOut, IOSVec *vec, IOSAsyncCallbackFn callback,
                                void *context);
} ImportsCoreInitIos;

#ifdef __cplusplus
}
#endif
