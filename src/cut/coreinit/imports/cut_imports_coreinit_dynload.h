#pragma once

#include "../dynload.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitDynLoad
{
    OSDynLoad_Error (*OSDynLoad_Acquire)(char const *name, OSDynLoad_Module *outModule);
    OSDynLoad_Error (*OSDynLoad_FindExport)(OSDynLoad_Module module, OSDynLoad_ExportType exportType, char const *name, void **outAddr);
    void (*OSDynLoad_Release)(OSDynLoad_Module module);
} ImportsCoreInitDynLoad;

#ifdef __cplusplus
}
#endif
