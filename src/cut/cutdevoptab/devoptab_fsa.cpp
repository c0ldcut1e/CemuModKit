#include "devoptab_fsa.h"

#include <cstdio>

static devoptab_t __cut_fsa_devoptab = {
        .name         = "fs",
        .structSize   = sizeof(__cut_fsa_file_t),
        .open_r       = __cut_fsa_open,
        .close_r      = __cut_fsa_close,
        .write_r      = __cut_fsa_write,
        .read_r       = __cut_fsa_read,
        .seek_r       = __cut_fsa_seek,
        .fstat_r      = __cut_fsa_fstat,
        .stat_r       = __cut_fsa_stat,
        .unlink_r     = __cut_fsa_unlink,
        .chdir_r      = __cut_fsa_chdir,
        .rename_r     = __cut_fsa_rename,
        .mkdir_r      = __cut_fsa_mkdir,
        .dirStateSize = sizeof(__cut_fsa_dir_t),
        .diropen_r    = __cut_fsa_diropen,
        .dirreset_r   = __cut_fsa_dirreset,
        .dirnext_r    = __cut_fsa_dirnext,
        .dirclose_r   = __cut_fsa_dirclose,
        .statvfs_r    = __cut_fsa_statvfs,
        .ftruncate_r  = __cut_fsa_ftruncate,
        .fsync_r      = __cut_fsa_fsync,
        .deviceData   = nullptr,
        .chmod_r      = __cut_fsa_chmod,
        .rmdir_r      = __cut_fsa_rmdir,
        .lstat_r      = __cut_fsa_stat,
};

__cut_fsa_device_t __cut_fsa_device_data = {};

FSError __init_cut_devoptab()
{
    FSError rc;

    if (__cut_fsa_device_data.setup)
    {
        return FS_ERROR_OK;
    }

    __cut_fsa_device_data = {};
    memcpy(&__cut_fsa_device_data.device, &__cut_fsa_devoptab, sizeof(__cut_fsa_devoptab));
    __cut_fsa_device_data.device.deviceData = &__cut_fsa_device_data;
    snprintf(__cut_fsa_device_data.name, sizeof(__cut_fsa_device_data.name), "fs");
    __cut_fsa_device_data.device.name = __cut_fsa_device_data.name;
    __cut_fsa_device_data.setup       = false;
    __cut_fsa_device_data.mounted     = false;
    __cut_fsa_device_data.isSDCard    = false;

    FSAInit();
    __cut_fsa_device_data.clientHandle = FSAAddClient(nullptr);
    if (__cut_fsa_device_data.clientHandle == 0)
    {
        OSReport("FSAAddClient() failed");
        return FS_ERROR_MAX_CLIENTS;
    }

    int dev = AddDevice(&__cut_fsa_device_data.device);

    if (dev != -1)
    {
        setDefaultDevice(dev);
        __cut_fsa_device_data.setup = true;
        snprintf(__cut_fsa_device_data.mountPath, sizeof(__cut_fsa_device_data.mountPath), "/vol/external01");

        rc = FSAMount(__cut_fsa_device_data.clientHandle, "/dev/sdcard01", __cut_fsa_device_data.mountPath, (FSAMountFlags) 0, nullptr, 0);

        if (rc < 0 && rc != FS_ERROR_ALREADY_EXISTS)
        {
            OSReport("FSAMount(0x%08X, \"/dev/sdcard01\", %s, 0, NULL, 0) failed: %s\n", __cut_fsa_device_data.clientHandle,
                     __cut_fsa_device_data.mountPath, FSAGetStatusStr(rc));
            return rc;
        }

        __cut_fsa_device_data.isSDCard = true;
        __cut_fsa_device_data.mounted  = true;
        __cut_fsa_device_data.cwd[0]   = '/';
        __cut_fsa_device_data.cwd[1]   = '\0';
        // chdir("fs:/vol/external01");

        // FSADeviceInfo deviceInfo;
        // if ((rc = FSAGetDeviceInfo(__cut_fsa_device_data.clientHandle,
        //                            __cut_fsa_device_data.mountPath, &deviceInfo)) >= 0)
        // {
        //     __cut_fsa_device_data.deviceSizeInSectors = deviceInfo.deviceSizeInSectors;
        //     __cut_fsa_device_data.deviceSectorSize    = deviceInfo.deviceSectorSize;
        // }
        // else
        // {
        __cut_fsa_device_data.deviceSizeInSectors = 0xFFFFFFFF;
        __cut_fsa_device_data.deviceSectorSize    = 512;
        // OSReport("Failed to get DeviceInfo for %s: %s\n", __cut_fsa_device_data.mountPath,
        //          FSAGetStatusStr(rc));
        // }
    }
    else
    {
        FSADelClient(__cut_fsa_device_data.clientHandle);
        __cut_fsa_device_data.clientHandle = 0;
        return FS_ERROR_MAX_CLIENTS;
    }

    return FS_ERROR_OK;
}

FSError __fini_cut_devoptab()
{
    FSError rc = FS_ERROR_OK;

    if (!__cut_fsa_device_data.setup)
    {
        return rc;
    }

    if (__cut_fsa_device_data.mounted)
    {
        FSAUnmount(__cut_fsa_device_data.clientHandle, __cut_fsa_device_data.mountPath, FSA_UNMOUNT_FLAG_BIND_MOUNT);
        __cut_fsa_device_data.mounted = false;
    }

    FSADelClient(__cut_fsa_device_data.clientHandle);

    RemoveDevice(__cut_fsa_device_data.device.name);

    __cut_fsa_device_data = {};

    return rc;
}
