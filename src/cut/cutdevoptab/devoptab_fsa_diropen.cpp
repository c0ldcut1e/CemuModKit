#include "devoptab_fsa.h"
#include <mutex>

DIR_ITER *__cut_fsa_diropen(struct _reent *r, DIR_ITER *dirState, const char *path)
{
    FSADirectoryHandle fd;
    FSError status;
    __cut_fsa_dir_t *dir;
    __cut_fsa_device_t *deviceData;

    if (!dirState || !path)
    {
        r->_errno = EINVAL;
        return NULL;
    }

    char *fixedPath = __cut_fsa_fixpath(r, path);
    if (!fixedPath)
    {
        return NULL;
    }
    dir        = (__cut_fsa_dir_t *) (dirState->dirStruct);
    deviceData = (__cut_fsa_device_t *) r->deviceData;

    // Remove trailing '/'
    if (fixedPath[0] != '\0')
    {
        if (fixedPath[strlen(fixedPath) - 1] == '/')
        {
            fixedPath[strlen(fixedPath) - 1] = 0;
        }
    }

    if (snprintf(dir->fullPath, sizeof(dir->fullPath), "%s", fixedPath) >= (int) sizeof(dir->fullPath))
    {
        OSReport("__cut_fsa_diropen: snprintf result was truncated\n");
    }

    free(fixedPath);

    dir->mutex.init(dir->fullPath);
    std::scoped_lock lock(dir->mutex);

    status = FSAOpenDir(deviceData->clientHandle, dir->fullPath, &fd);
    if (status < 0)
    {
        OSReport("FSAOpenDir(0x%08X, %s, %p) failed: %s\n", deviceData->clientHandle, dir->fullPath, &fd, FSAGetStatusStr(status));
        r->_errno = __cut_fsa_translate_error(status);
        return NULL;
    }

    dir->magic = FSA_DIRITER_MAGIC;
    dir->fd    = fd;
    memset(&dir->entry_data, 0, sizeof(dir->entry_data));
    return dirState;
}
