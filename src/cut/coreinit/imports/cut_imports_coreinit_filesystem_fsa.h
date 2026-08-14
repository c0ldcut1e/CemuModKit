#pragma once

#include "../filesystem_fsa.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitFilesystemFsa
{
    FSError (*FSAInit)(void);
    FSAClientHandle (*FSAAddClient)(FSAClientAttachAsyncData *attachAsyncData);
    FSError (*FSADelClient)(FSAClientHandle client);
    const char *(*FSAGetStatusStr)(FSError error);
    FSError (*FSAMount)(FSAClientHandle client, const char *source, const char *target, FSAMountFlags flags, void *arg_buf, uint32_t arg_len);
    FSError (*FSAUnmount)(FSAClientHandle client, const char *mountedTarget, FSAUnmountFlags flags);
    FSError (*FSAChangeDir)(FSAClientHandle client, const char *path);
    FSError (*FSAChangeMode)(FSAClientHandle client, const char *path, FSMode permission);
    FSError (*FSAOpenFileEx)(FSAClientHandle client, const char *path, const char *mode, FSMode createMode, FSOpenFileFlags openFlag,
                             uint32_t preallocSize, FSAFileHandle *outFileHandle);
    FSError (*FSAGetStatFile)(FSAClientHandle client, FSAFileHandle fileHandle, FSAStat *stat);
    FSError (*FSAGetStat)(FSAClientHandle client, const char *path, FSAStat *stat);
    FSError (*FSACloseFile)(FSAClientHandle client, FSAFileHandle fileHandle);
    FSError (*FSAFlushFile)(FSAClientHandle client, FSAFileHandle fileHandle);
    FSError (*FSASetPosFile)(FSAClientHandle client, FSAFileHandle fileHandle, uint32_t pos);
    FSError (*FSATruncateFile)(FSAClientHandle client, FSAFileHandle handle);
    FSError (*FSAWriteFile)(FSAClientHandle client, void *buffer, uint32_t size, uint32_t count, FSAFileHandle handle, uint32_t flags);
    FSError (*FSAReadFile)(FSAClientHandle client, void *buffer, uint32_t size, uint32_t count, FSAFileHandle handle, uint32_t flags);
    FSError (*FSARemove)(FSAClientHandle client, const char *path);
    FSError (*FSARename)(FSAClientHandle client, const char *oldPath, const char *newPath);
    FSError (*FSAOpenDir)(FSAClientHandle client, const char *path, FSADirectoryHandle *dirHandle);
    FSError (*FSAReadDir)(FSAClientHandle client, FSADirectoryHandle dirHandle, FSADirectoryEntry *directoryEntry);
    FSError (*FSARewindDir)(FSAClientHandle client, FSADirectoryHandle dirHandle);
    FSError (*FSACloseDir)(FSAClientHandle client, FSADirectoryHandle dirHandle);
    FSError (*FSAMakeDir)(FSAClientHandle client, const char *path, FSMode mode);
    FSError (*FSAGetFreeSpaceSize)(FSAClientHandle client, const char *path, uint64_t *freeSpaceSize);
    FSError (*FSAGetDeviceInfo)(FSAClientHandle client, const char *path, FSADeviceInfo *fileSystemInfo);
} ImportsCoreInitFilesystemFsa;

#ifdef __cplusplus
}
#endif
