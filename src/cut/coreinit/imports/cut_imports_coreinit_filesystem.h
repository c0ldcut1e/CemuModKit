#pragma once

#include "../filesystem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitFilesystem
{
    void (*FSInit)(void);
    void (*FSShutdown)(void);
    FSStatus (*FSAddClient)(FSClient *client, FSErrorFlag errorMask);
    FSStatus (*FSDelClient)(FSClient *client, FSErrorFlag errorMask);
    uint32_t (*FSGetClientNum)(void);
    void (*FSInitCmdBlock)(FSCmdBlock *block);
    FSAsyncResult *(*FSGetAsyncResult)(FSMessage *message);
    FSStatus (*FSGetCwd)(FSClient *client, FSCmdBlock *block, char *buffer, uint32_t bufferSize, FSErrorFlag errorMask);
    FSStatus (*FSGetCwdAsync)(FSClient *client, FSCmdBlock *block, char *buffer, uint32_t bufferSize, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSChangeDir)(FSClient *client, FSCmdBlock *block, const char *path, FSErrorFlag errorMask);
    FSStatus (*FSChangeDirAsync)(FSClient *client, FSCmdBlock *block, const char *path, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSGetStat)(FSClient *client, FSCmdBlock *block, const char *path, FSStat *stat, FSErrorFlag errorMask);
    FSStatus (*FSGetStatAsync)(FSClient *client, FSCmdBlock *block, const char *path, FSStat *stat, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSRemove)(FSClient *client, FSCmdBlock *block, const char *path, FSErrorFlag errorMask);
    FSStatus (*FSRemoveAsync)(FSClient *client, FSCmdBlock *block, const char *path, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSOpenFile)(FSClient *client, FSCmdBlock *block, const char *path, const char *mode, FSFileHandle *handle, FSErrorFlag errorMask);
    FSStatus (*FSOpenFileAsync)(FSClient *client, FSCmdBlock *block, const char *path, const char *mode, FSFileHandle *outHandle,
                                FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSCloseFile)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSErrorFlag errorMask);
    FSStatus (*FSCloseFileAsync)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSOpenFileEx)(FSClient *client, FSCmdBlock *block, const char *path, const char *mode, FSMode createMode, FSOpenFileFlags openFlag,
                             uint32_t preallocSize, FSFileHandle *handle, FSErrorFlag errorMask);
    FSStatus (*FSOpenFileExAsync)(FSClient *client, FSCmdBlock *block, const char *path, const char *mode, FSMode createMode,
                                  FSOpenFileFlags openFlag, uint32_t preallocSize, FSFileHandle *handle, FSErrorFlag errorMask,
                                  FSAsyncData *asyncData);
    FSStatus (*FSOpenDir)(FSClient *client, FSCmdBlock *block, const char *path, FSDirectoryHandle *handle, FSErrorFlag errorMask);
    FSStatus (*FSOpenDirAsync)(FSClient *client, FSCmdBlock *block, const char *path, FSDirectoryHandle *handle, FSErrorFlag errorMask,
                               FSAsyncData *asyncData);
    FSStatus (*FSMakeDir)(FSClient *client, FSCmdBlock *block, const char *path, FSErrorFlag errorMask);
    FSStatus (*FSMakeDirAsync)(FSClient *client, FSCmdBlock *block, const char *path, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSReadDir)(FSClient *client, FSCmdBlock *block, FSDirectoryHandle handle, FSDirectoryEntry *entry, FSErrorFlag errorMask);
    FSStatus (*FSReadDirAsync)(FSClient *client, FSCmdBlock *block, FSDirectoryHandle handle, FSDirectoryEntry *entry, FSErrorFlag errorMask,
                               FSAsyncData *asyncData);
    FSStatus (*FSCloseDir)(FSClient *client, FSCmdBlock *block, FSDirectoryHandle handle, FSErrorFlag errorMask);
    FSStatus (*FSCloseDirAsync)(FSClient *client, FSCmdBlock *block, FSDirectoryHandle handle, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSChangeMode)(FSClient *client, FSCmdBlock *block, const char *path, FSMode mode, FSMode modeMask, FSErrorFlag errorMask);
    FSStatus (*FSChangeModeAsync)(FSClient *client, FSCmdBlock *block, const char *path, FSMode mode, FSMode modeMask, FSErrorFlag errorMask,
                                  FSAsyncData *asyncData);
    FSStatus (*FSGetFreeSpaceSize)(FSClient *client, FSCmdBlock *block, const char *path, uint64_t *outSize, FSErrorFlag errorMask);
    FSStatus (*FSGetFreeSpaceSizeAsync)(FSClient *client, FSCmdBlock *block, const char *path, uint64_t *outSize, FSErrorFlag errorMask,
                                        FSAsyncData *asyncData);
    FSStatus (*FSGetStatFile)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSStat *stat, FSErrorFlag errorMask);
    FSStatus (*FSGetStatFileAsync)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSStat *stat, FSErrorFlag errorMask,
                                   FSAsyncData *asyncData);
    FSStatus (*FSReadFile)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, FSFileHandle handle, uint32_t unk1,
                           FSErrorFlag errorMask);
    FSStatus (*FSReadFileAsync)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, FSFileHandle handle,
                                uint32_t unk1, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSReadFileWithPos)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, uint32_t pos,
                                  FSFileHandle handle, uint32_t unk1, FSErrorFlag errorMask);
    FSStatus (*FSReadFileWithPosAsync)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, uint32_t pos,
                                       FSFileHandle handle, uint32_t unk1, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSWriteFile)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, FSFileHandle handle, uint32_t unk1,
                            FSErrorFlag errorMask);
    FSStatus (*FSWriteFileAsync)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, FSFileHandle handle,
                                 uint32_t unk1, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSWriteFileWithPos)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, uint32_t pos,
                                   FSFileHandle handle, uint32_t unk1, FSErrorFlag errorMask);
    FSStatus (*FSWriteFileWithPosAsync)(FSClient *client, FSCmdBlock *block, uint8_t *buffer, uint32_t size, uint32_t count, uint32_t pos,
                                        FSFileHandle handle, uint32_t unk1, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSGetPosFile)(FSClient *client, FSCmdBlock *block, FSFileHandle fileHandle, uint32_t *pos, FSErrorFlag errorMask);
    FSStatus (*FSGetPosFileAsync)(FSClient *client, FSCmdBlock *block, FSFileHandle fileHandle, uint32_t *pos, FSErrorFlag errorMask,
                                  FSAsyncData *asyncData);
    FSStatus (*FSSetPosFile)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, uint32_t pos, FSErrorFlag errorMask);
    FSStatus (*FSSetPosFileAsync)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, uint32_t pos, FSErrorFlag errorMask,
                                  FSAsyncData *asyncData);
    FSStatus (*FSFlushFile)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSErrorFlag errorMask);
    FSStatus (*FSFlushFileAsync)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSTruncateFile)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSErrorFlag errorMask);
    FSStatus (*FSTruncateFileAsync)(FSClient *client, FSCmdBlock *block, FSFileHandle handle, FSErrorFlag errorMask, FSAsyncData *asyncData);
    FSStatus (*FSRename)(FSClient *client, FSCmdBlock *block, const char *oldPath, const char *newPath, FSErrorFlag errorMask);
    FSStatus (*FSRenameAsync)(FSClient *client, FSCmdBlock *block, const char *oldPath, const char *newPath, FSErrorFlag errorMask,
                              FSAsyncData *asyncData);
    FSVolumeState (*FSGetVolumeState)(FSClient *client);
    FSError (*FSGetLastErrorCodeForViewer)(FSClient *client);
    FSStatus (*FSGetMountSource)(FSClient *client, FSCmdBlock *cmd, FSMountSourceType type, FSMountSource *out, FSErrorFlag errorMask);
    FSStatus (*FSMount)(FSClient *client, FSCmdBlock *cmd, FSMountSource *source, const char *target, uint32_t bytes, FSErrorFlag errorMask);
    FSStatus (*FSBindMount)(FSClient *client, FSCmdBlock *cmd, const char *source, const char *target, FSErrorFlag errorMask);
} ImportsCoreInitFilesystem;

#ifdef __cplusplus
}
#endif
