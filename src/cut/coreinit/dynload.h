
#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSDynLoad_NotifyData OSDynLoad_NotifyData;
typedef struct OSDynLoad_LoaderHeapStatistics OSDynLoad_LoaderHeapStatistics;
typedef void *OSDynLoad_Module;

typedef struct OSDynLoad_LoaderUserFileInfo OSDynLoad_LoaderUserFileInfo;
typedef struct OSDynLoad_LoaderSectionInfo OSDynLoad_LoaderSectionInfo;
typedef struct OSDynLoad_InternalData OSDynLoad_InternalData;

typedef enum OSDynLoad_Error
{
    OS_DYNLOAD_OK                      = 0,
    OS_DYNLOAD_OUT_OF_MEMORY           = 0xBAD10002,
    OS_DYNLOAD_INVALID_NOTIFY_PTR      = 0xBAD1000E,
    OS_DYNLOAD_INVALID_MODULE_NAME_PTR = 0xBAD1000F,
    OS_DYNLOAD_INVALID_MODULE_NAME     = 0xBAD10010,
    OS_DYNLOAD_INVALID_ACQUIRE_PTR     = 0xBAD10011,
    OS_DYNLOAD_EMPTY_MODULE_NAME       = 0xBAD10012,
    OS_DYNLOAD_INVALID_ALLOCATOR_PTR   = 0xBAD10017,
    OS_DYNLOAD_OUT_OF_SYSTEM_MEMORY    = 0xBAD1002F,
    OS_DYNLOAD_TLS_ALLOCATOR_LOCKED    = 0xBAD10031,
    OS_DYNLOAD_MODULE_NOT_FOUND        = 0xFFFFFFFA,
} OSDynLoad_Error;

typedef OSDynLoad_Error (*OSDynLoadAllocFn)(int size, int align, void **outAddr);
typedef void (*OSDynLoadFreeFn)(void *addr);

typedef enum OSDynLoad_ExportType
{
    OS_DYNLOAD_EXPORT_FUNC = 0,
    OS_DYNLOAD_EXPORT_DATA = 1,
} OSDynLoad_ExportType;

typedef enum OSDynLoad_EntryReason
{
    OS_DYNLOAD_LOADED   = 1,
    OS_DYNLOAD_UNLOADED = 2,
} OSDynLoad_EntryReason;

struct OSDynLoad_NotifyData
{
    char *name;

    uint32_t textAddr;
    uint32_t textOffset;
    uint32_t textSize;

    uint32_t dataAddr;
    uint32_t dataOffset;
    uint32_t dataSize;

    uint32_t readAddr;
    uint32_t readOffset;
    uint32_t readSize;
};
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x00, name);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x04, textAddr);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x08, textOffset);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x0C, textSize);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x10, dataAddr);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x14, dataOffset);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x18, dataSize);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x1C, readAddr);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x20, readOffset);
CUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x24, readSize);
CUT_CHECK_SIZE(OSDynLoad_NotifyData, 0x28);

struct OSDynLoad_LoaderHeapStatistics
{
    uint32_t codeHeapUsed;
    uint32_t unk_0x04;
    uint32_t codeHeapFree;
    uint32_t codeHeapLargestFree;
    uint32_t dataHeapUsed;
    uint32_t unk_0x14;
};
CUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x00, codeHeapUsed);
CUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x04, unk_0x04);
CUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x08, codeHeapFree);
CUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x0C, codeHeapLargestFree);
CUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x10, dataHeapUsed);
CUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x14, unk_0x14);
CUT_CHECK_SIZE(OSDynLoad_LoaderHeapStatistics, 0x18);

struct OSDynLoad_LoaderUserFileInfo
{
    uint32_t size;
    uint32_t magic;
    uint32_t pathStringLength;
    char *pathString;
    uint32_t fileInfoFlags;
    int16_t tlsModuleIndex;
    int16_t tlsAlignShift;
    void *tlsAddressStart;
    uint32_t tlsSectionSize;
    uint32_t shstrndx;
    uint32_t titleLocation;
    CUT_UNKNOWN_BYTES(0x60 - 0x28);
};
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x00, size);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x04, magic);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x08, pathStringLength);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x0C, pathString);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x10, fileInfoFlags);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x14, tlsModuleIndex);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x16, tlsAlignShift);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x18, tlsAddressStart);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x1C, tlsSectionSize);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x20, shstrndx);
CUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x24, titleLocation);
CUT_CHECK_SIZE(OSDynLoad_LoaderUserFileInfo, 0x60);

struct OSDynLoad_LoaderSectionInfo
{
    uint32_t type;
    uint32_t flags;
    void *address;

    union
    {
        //! Size of the section, set when type != SHT_RPL_IMPORTS
        uint32_t size;

        //! Name offset of the section, set when type == SHT_RPL_IMPORTS
        uint32_t name;
    };
};
CUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x00, type);
CUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x04, flags);
CUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x08, address);
CUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x0C, size);
CUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x0C, name);
CUT_CHECK_SIZE(OSDynLoad_LoaderSectionInfo, 0x10);

struct OSDynLoad_InternalData
{
    uint32_t handle;
    void *loaderHandle;
    char *moduleName;
    uint32_t moduleNameLen;
    uint32_t sectionInfoCount;
    OSDynLoad_LoaderSectionInfo *sectionInfo;
    OSDynLoad_InternalData **importModules;
    uint32_t importModuleCount;
    uint32_t userFileInfoSize;
    OSDynLoad_LoaderUserFileInfo *userFileInfo;
    OSDynLoad_NotifyData *notifyData;
    void *entryPoint;
    uint32_t dataSectionSize;
    void *dataSection;
    uint32_t loadSectionSize;
    void *loadSection;
    OSDynLoadFreeFn dynLoadFreeFn;
    void *codeExports;
    uint32_t numCodeExports;
    void *dataExports;
    uint32_t numDataExports;
    OSDynLoad_InternalData *next;
    CUT_UNKNOWN_BYTES(0x94 - 0x58);
};
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x00, handle);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x04, loaderHandle);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x08, moduleName);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x0C, moduleNameLen);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x10, sectionInfoCount);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x14, sectionInfo);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x18, importModules);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x1C, importModuleCount);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x20, userFileInfoSize);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x24, userFileInfo);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x28, notifyData);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x2C, entryPoint);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x30, dataSectionSize);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x34, dataSection);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x38, loadSectionSize);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x3C, loadSection);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x40, dynLoadFreeFn);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x44, codeExports);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x48, numCodeExports);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x4C, dataExports);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x50, numDataExports);
CUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x54, next);
CUT_CHECK_SIZE(OSDynLoad_InternalData, 0x94);

typedef enum OSDynLoad_NotifyReason
{
    OS_DYNLOAD_NOTIFY_UNLOADED = 0,
    OS_DYNLOAD_NOTIFY_LOADED   = 1
} OSDynLoad_NotifyReason;

typedef void (*OSDynLoadNotifyFunc)(OSDynLoad_Module module, void *userContext, OSDynLoad_NotifyReason notifyReason, OSDynLoad_NotifyData *infos);

/**
 * Load a module.
 *
 * If the module is already loaded, increase reference count.
 * Similar to LoadLibrary on Windows.
 */
CUT_IMPORT OSDynLoad_Error (*OSDynLoad_Acquire)(char const *name, OSDynLoad_Module *outModule);

/**
 * Retrieve the address of a function or data export from a module.
 *
 * Similar to GetProcAddress on Windows.
 */
CUT_IMPORT OSDynLoad_Error (*OSDynLoad_FindExport)(OSDynLoad_Module module, OSDynLoad_ExportType exportType, char const *name, void **outAddr);

/**
 * Free a module handle returned from OSDynLoad_Acquire.
 *
 * Will decrease reference count and only unload the module if count reaches 0.
 * Similar to FreeLibrary on Windows.
 */
CUT_IMPORT void (*OSDynLoad_Release)(OSDynLoad_Module module);

#ifdef __cplusplus
}
#endif
