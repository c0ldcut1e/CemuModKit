#include "devoptab_fsa.h"
#include <mutex>

int __cut_fsa_fstat(struct _reent *r, void *fd, struct stat *st)
{
    FSError status;
    FSAStat fsStat;
    __cut_fsa_file_t *file;
    __cut_fsa_device_t *deviceData;

    if (!fd || !st)
    {
        r->_errno = EINVAL;
        return -1;
    }

    file       = (__cut_fsa_file_t *) fd;
    deviceData = (__cut_fsa_device_t *) r->deviceData;

    std::scoped_lock lock(file->mutex);

    status = FSAGetStatFile(deviceData->clientHandle, file->fd, &fsStat);
    if (status < 0)
    {
        OSReport("FSAGetStatFile(0x%08X, 0x%08X, %p) (%s) failed: %s\n", deviceData->clientHandle, file->fd, &fsStat, file->fullPath,
                 FSAGetStatusStr(status));
        r->_errno = __cut_fsa_translate_error(status);
        return -1;
    }

    ino_t ino = __cut_fsa_hashstring(file->fullPath);
    __cut_fsa_translate_stat(deviceData->clientHandle, &fsStat, ino, st);

    return 0;
}
