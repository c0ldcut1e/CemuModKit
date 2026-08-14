#include "devoptab_fsa.h"
#include <mutex>

int __cut_fsa_dirreset(struct _reent *r, DIR_ITER *dirState)
{
    FSError status;
    __cut_fsa_dir_t *dir;
    __cut_fsa_device_t *deviceData;

    if (!dirState)
    {
        r->_errno = EINVAL;
        return -1;
    }

    dir        = (__cut_fsa_dir_t *) (dirState->dirStruct);
    deviceData = (__cut_fsa_device_t *) r->deviceData;

    std::scoped_lock lock(dir->mutex);

    status = FSARewindDir(deviceData->clientHandle, dir->fd);
    if (status < 0)
    {
        OSReport("FSARewindDir(0x%08X, 0x%08X) (%s) failed: %s\n", deviceData->clientHandle, dir->fd, dir->fullPath, FSAGetStatusStr(status));
        r->_errno = __cut_fsa_translate_error(status);
        return -1;
    }

    return 0;
}
