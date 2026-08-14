#include "devoptab_fsa.h"

int __cut_fsa_unlink(struct _reent *r, const char *name)
{
    FSError status;
    char *fixedPath;
    __cut_fsa_device_t *deviceData;

    if (!name)
    {
        r->_errno = EINVAL;
        return -1;
    }

    fixedPath = __cut_fsa_fixpath(r, name);
    if (!fixedPath)
    {
        r->_errno = ENOMEM;
        return -1;
    }
    deviceData = (__cut_fsa_device_t *) r->deviceData;

    status = FSARemove(deviceData->clientHandle, fixedPath);
    if (status < 0)
    {
        OSReport("FSARemove(0x%08X, %s) failed: %s\n", deviceData->clientHandle, fixedPath, FSAGetStatusStr(status));
        free(fixedPath);
        r->_errno = __cut_fsa_translate_error(status);
        return -1;
    }

    free(fixedPath);

    return 0;
}
