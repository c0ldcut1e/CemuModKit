#include "devoptab_fsa.h"
#include <mutex>

int __cut_fsa_fsync(struct _reent *r, void *fd)
{
    FSError status;
    __cut_fsa_file_t *file;
    __cut_fsa_device_t *deviceData;

    if (!fd)
    {
        r->_errno = EINVAL;
        return -1;
    }

    file = (__cut_fsa_file_t *) fd;

    deviceData = (__cut_fsa_device_t *) r->deviceData;

    std::scoped_lock lock(file->mutex);

    status = FSAFlushFile(deviceData->clientHandle, file->fd);
    if (status < 0)
    {
        OSReport("FSAFlushFile(0x%08X, 0x%08X) (%s) failed: %s\n", deviceData->clientHandle, file->fd, file->fullPath, FSAGetStatusStr(status));
        r->_errno = __cut_fsa_translate_error(status);
        return -1;
    }

    return 0;
}
