#pragma once

#include "cut_imports_coreinit_alarm.h"
#include "cut_imports_coreinit_atomic.h"
#include "cut_imports_coreinit_cache.h"
#include "cut_imports_coreinit_core.h"
#include "cut_imports_coreinit_debug.h"
#include "cut_imports_coreinit_dynload.h"
#include "cut_imports_coreinit_exception.h"
#include "cut_imports_coreinit_fastcondition.h"
#include "cut_imports_coreinit_fastmutex.h"
#include "cut_imports_coreinit_filesystem.h"
#include "cut_imports_coreinit_filesystem_fsa.h"
#include "cut_imports_coreinit_internal.h"
#include "cut_imports_coreinit_ios.h"
#include "cut_imports_coreinit_memexpheap.h"
#include "cut_imports_coreinit_memheap.h"
#include "cut_imports_coreinit_memlist.h"
#include "cut_imports_coreinit_memory.h"
#include "cut_imports_coreinit_memorymap.h"
#include "cut_imports_coreinit_messagequeue.h"
#include "cut_imports_coreinit_mutex.h"
#include "cut_imports_coreinit_spinlock.h"
#include "cut_imports_coreinit_systeminfo.h"
#include "cut_imports_coreinit_thread.h"
#include "cut_imports_coreinit_time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInit
{
    ImportsCoreInitAtomic atomic;
    ImportsCoreInitCache cache;
    ImportsCoreInitDebug debug;
    ImportsCoreInitDynLoad dynLoad;
    ImportsCoreInitException exception;
    ImportsCoreInitFastCondition fastCondition;
    ImportsCoreInitFastMutex fastMutex;
    ImportsCoreInitInternal internal;
    ImportsCoreInitMemory memory;
    ImportsCoreInitMemorymap memoryMap;
    ImportsCoreInitMemexpheap memExpHeap;
    ImportsCoreInitMemheap memHeap;
    ImportsCoreInitMemlist memList;
    ImportsCoreInitMutex mutex;
    ImportsCoreInitSpinlock spinlock;
    ImportsCoreInitSysteminfo systemInfo;
    ImportsCoreInitThread thread;
    ImportsCoreInitCore core;
    ImportsCoreInitAlarm alarm;
    ImportsCoreInitTime time;
    ImportsCoreInitMessagequeue messageQueue;
    ImportsCoreInitIos ios;
    ImportsCoreInitFilesystem filesystem;
    ImportsCoreInitFilesystemFsa filesystemFsa;
} ImportsCoreInit;

#ifdef __cplusplus
}
#endif
