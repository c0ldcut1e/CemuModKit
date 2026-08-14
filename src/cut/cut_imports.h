#pragma once

#include "coreinit/imports/cut_imports_coreinit.h"
#include "gx2/imports/cut_imports_gx2.h"
#include "nlibcurl/imports/cut_imports_nlibcurl.h"
#include "nn_act/imports/cut_imports_nn_act.h"
#include "nn_fp/imports/cut_imports_nn_fp.h"
#include "nsysnet/imports/cut_imports_nsysnet.h"
#include "snd_core/imports/cut_imports_snd_core.h"
#include "vpad/imports/cut_imports_vpad.h"

#ifdef __cplusplus

typedef struct Imports
{
    ImportsCoreInit coreinit;
    ImportsGX2 gx2;
    ImportsSndCore snd_core;
    ImportsNSysNet nsysnet;
    ImportsVPAD vpad;
    ImportsNLibCurl nlibcurl;
    ImportsNNAct nn_act;
    ImportsNNFp nn_fp;
} Imports;

void cut_setAllImports(const Imports *imports);

#endif
