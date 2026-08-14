#include "devoptab_fsa.h"

int __cut_fsa_stat(struct _reent *r, const char *path, struct stat *st)
{
    FSError status;
    FSAStat fsStat;
    __cut_fsa_device_t *deviceData;

    if (!path || !st)
    {
        r->_errno = EINVAL;
        return -1;
    }

    char *fixedPath = __cut_fsa_fixpath(r, path);
    if (!fixedPath)
    {
        r->_errno = ENOMEM;
        return -1;
    }

    deviceData = (__cut_fsa_device_t *) r->deviceData;

    status = FSAGetStat(deviceData->clientHandle, fixedPath, &fsStat);
    if (status < 0)
    {
        if (status != FS_ERROR_NOT_FOUND)
        {
            OSReport("FSAGetStat(0x%08X, %s, %p) failed: %s\n", deviceData->clientHandle, fixedPath, &fsStat, FSAGetStatusStr(status));
        }
        free(fixedPath);
        r->_errno = __cut_fsa_translate_error(status);
        return -1;
    }
    ino_t ino = __cut_fsa_hashstring(fixedPath);
    free(fixedPath);

    __cut_fsa_translate_stat(deviceData->clientHandle, &fsStat, ino, st);

    return 0;
}
