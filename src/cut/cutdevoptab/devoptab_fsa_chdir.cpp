#include "devoptab_fsa.h"
#include <cstdio>

int __cut_fsa_chdir(struct _reent *r, const char *path)
{
    FSError status;
    __cut_fsa_device_t *deviceData;

    if (!path)
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

    status = FSAChangeDir(deviceData->clientHandle, fixedPath);
    if (status < 0)
    {
        OSReport("FSAChangeDir(0x%08X, %s) failed: %s\n", deviceData->clientHandle, fixedPath, FSAGetStatusStr(status));
        free(fixedPath);
        r->_errno = __cut_fsa_translate_error(status);
        return -1;
    }

    // Remove trailing '/'
    if (fixedPath[0] != '\0')
    {
        if (fixedPath[strlen(fixedPath) - 1] == '/')
        {
            fixedPath[strlen(fixedPath) - 1] = 0;
        }
    }

    if (snprintf(deviceData->cwd, sizeof(deviceData->cwd), "%s", fixedPath) >= (int) sizeof(deviceData->cwd))
    {
        OSReport("__cut_fsa_chdir: snprintf result was truncated\n");
    }

    free(fixedPath);

    return 0;
}
