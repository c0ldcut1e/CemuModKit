#include "cut_imports.h"

void cut_setAllImports(const Imports *imports)
{
    // coreinit/atomic
    OSCompareAndSwapAtomicEx = imports->coreinit.atomic.OSCompareAndSwapAtomicEx;

    // coreinit/cache
    DCInvalidateRange  = imports->coreinit.cache.DCInvalidateRange;
    DCFlushRange       = imports->coreinit.cache.DCFlushRange;
    DCStoreRange       = imports->coreinit.cache.DCStoreRange;
    DCFlushRangeNoSync = imports->coreinit.cache.DCFlushRangeNoSync;
    DCStoreRangeNoSync = imports->coreinit.cache.DCStoreRangeNoSync;
    DCZeroRange        = imports->coreinit.cache.DCZeroRange;
    DCTouchRange       = imports->coreinit.cache.DCTouchRange;
    ICInvalidateRange  = imports->coreinit.cache.ICInvalidateRange;
    OSMemoryBarrier    = imports->coreinit.cache.OSMemoryBarrier;

    // coreinit/debug
    OSReport             = imports->coreinit.debug.OSReport;
    OSFatal              = imports->coreinit.debug.OSFatal;
    OSGetSymbolName      = imports->coreinit.debug.OSGetSymbolName;
    OSGetUPID            = imports->coreinit.debug.OSGetUPID;
    OSIsDebuggerPresent  = imports->coreinit.debug.OSIsDebuggerPresent;
    DisassemblePPCOpcode = imports->coreinit.debug.DisassemblePPCOpcode;
    DisassemblePPCRange  = imports->coreinit.debug.DisassemblePPCRange;

    // coreinit/dynload
    OSDynLoad_Acquire    = imports->coreinit.dynLoad.OSDynLoad_Acquire;
    OSDynLoad_FindExport = imports->coreinit.dynLoad.OSDynLoad_FindExport;
    OSDynLoad_Release    = imports->coreinit.dynLoad.OSDynLoad_Release;

    // coreinit/exception
    OSSetExceptionCallback   = imports->coreinit.exception.OSSetExceptionCallback;
    OSSetExceptionCallbackEx = imports->coreinit.exception.OSSetExceptionCallbackEx;

    // coreinit/fastcondition
    OSFastCond_Init   = imports->coreinit.fastCondition.OSFastCond_Init;
    OSFastCond_Wait   = imports->coreinit.fastCondition.OSFastCond_Wait;
    OSFastCond_Signal = imports->coreinit.fastCondition.OSFastCond_Signal;

    // coreinit/fastmutex
    OSFastMutex_Init    = imports->coreinit.fastMutex.OSFastMutex_Init;
    OSFastMutex_Lock    = imports->coreinit.fastMutex.OSFastMutex_Lock;
    OSFastMutex_Unlock  = imports->coreinit.fastMutex.OSFastMutex_Unlock;
    OSFastMutex_TryLock = imports->coreinit.fastMutex.OSFastMutex_TryLock;

    // coreinit/internal
    __os_snprintf = imports->coreinit.internal.__os_snprintf;

    // coreinit/memory
    OSGetSharedData               = imports->coreinit.memory.OSGetSharedData;
    __OSRootLoadShared            = imports->coreinit.memory.__OSRootLoadShared;
    OSBlockMove                   = imports->coreinit.memory.OSBlockMove;
    OSBlockSet                    = imports->coreinit.memory.OSBlockSet;
    OSAllocFromSystem             = imports->coreinit.memory.OSAllocFromSystem;
    OSFreeToSystem                = imports->coreinit.memory.OSFreeToSystem;
    OSGetForegroundBucket         = imports->coreinit.memory.OSGetForegroundBucket;
    OSGetForegroundBucketFreeArea = imports->coreinit.memory.OSGetForegroundBucketFreeArea;
    OSGetMemBound                 = imports->coreinit.memory.OSGetMemBound;
    __OSZeroProcessMemory         = imports->coreinit.memory.__OSZeroProcessMemory;

    // coreinit/memorymap
    OSEffectiveToPhysical           = imports->coreinit.memoryMap.OSEffectiveToPhysical;
    __OSPhysicalToEffectiveCached   = imports->coreinit.memoryMap.__OSPhysicalToEffectiveCached;
    __OSPhysicalToEffectiveUncached = imports->coreinit.memoryMap.__OSPhysicalToEffectiveUncached;
    OSIsAddressValid                = imports->coreinit.memoryMap.OSIsAddressValid;
    __OSValidateAddressSpaceRange   = imports->coreinit.memoryMap.__OSValidateAddressSpaceRange;
    OSAllocVirtAddr                 = imports->coreinit.memoryMap.OSAllocVirtAddr;
    OSFreeVirtAddr                  = imports->coreinit.memoryMap.OSFreeVirtAddr;
    OSQueryVirtAddr                 = imports->coreinit.memoryMap.OSQueryVirtAddr;
    OSMapMemory                     = imports->coreinit.memoryMap.OSMapMemory;
    OSUnmapMemory                   = imports->coreinit.memoryMap.OSUnmapMemory;
    OSGetMapVirtAddrRange           = imports->coreinit.memoryMap.OSGetMapVirtAddrRange;
    OSGetAvailPhysAddrRange         = imports->coreinit.memoryMap.OSGetAvailPhysAddrRange;
    OSGetDataPhysAddrRange          = imports->coreinit.memoryMap.OSGetDataPhysAddrRange;

    // coreinit/memdefaultheap
    {
        void *addr = NULL;

        OSDynLoad_Module coreinitModule = NULL;
        OSDynLoad_Acquire("coreinit.rpl", &coreinitModule);

        OSDynLoad_FindExport(coreinitModule, OS_DYNLOAD_EXPORT_DATA, "MEMAllocFromDefaultHeapEx", &addr);
        MEMAllocFromDefaultHeapEx = *(MEMAllocFromDefaultHeapExFn *) addr;

        OSDynLoad_FindExport(coreinitModule, OS_DYNLOAD_EXPORT_DATA, "MEMAllocFromDefaultHeap", &addr);
        MEMAllocFromDefaultHeap = *(MEMAllocFromDefaultHeapFn *) addr;

        OSDynLoad_FindExport(coreinitModule, OS_DYNLOAD_EXPORT_DATA, "MEMFreeToDefaultHeap", &addr);
        MEMFreeToDefaultHeap = *(MEMFreeToDefaultHeapFn *) addr;

        OSDynLoad_Release(coreinitModule);
    }

    // coreinit/memexpheap
    MEMAllocFromExpHeapEx             = imports->coreinit.memExpHeap.MEMAllocFromExpHeapEx;
    MEMCreateExpHeapEx                = imports->coreinit.memExpHeap.MEMCreateExpHeapEx;
    MEMFreeToExpHeap                  = imports->coreinit.memExpHeap.MEMFreeToExpHeap;
    MEMGetTotalFreeSizeForExpHeap     = imports->coreinit.memExpHeap.MEMGetTotalFreeSizeForExpHeap;
    MEMGetAllocatableSizeForExpHeapEx = imports->coreinit.memExpHeap.MEMGetAllocatableSizeForExpHeapEx;
    MEMGetSizeForMBlockExpHeap        = imports->coreinit.memExpHeap.MEMGetSizeForMBlockExpHeap;
    MEMVisitAllocatedForExpHeap       = imports->coreinit.memExpHeap.MEMVisitAllocatedForExpHeap;

    // coreinit/memheap
    MEMGetBaseHeapHandle = imports->coreinit.memHeap.MEMGetBaseHeapHandle;

    // coreinit/memlist
    MEMGetNextListObject = imports->coreinit.memList.MEMGetNextListObject;

    // coreinit/mutex
    OSInitMutex    = imports->coreinit.mutex.OSInitMutex;
    OSInitMutexEx  = imports->coreinit.mutex.OSInitMutexEx;
    OSLockMutex    = imports->coreinit.mutex.OSLockMutex;
    OSTryLockMutex = imports->coreinit.mutex.OSTryLockMutex;
    OSUnlockMutex  = imports->coreinit.mutex.OSUnlockMutex;

    // coreinit/spinlock
    OSInitSpinLock                    = imports->coreinit.spinlock.OSInitSpinLock;
    OSUninterruptibleSpinLock_Acquire = imports->coreinit.spinlock.OSUninterruptibleSpinLock_Acquire;
    OSUninterruptibleSpinLock_Release = imports->coreinit.spinlock.OSUninterruptibleSpinLock_Release;

    // coreinit/systeminfo
    OSGetSystemInfo           = imports->coreinit.systemInfo.OSGetSystemInfo;
    OSEnableHomeButtonMenu    = imports->coreinit.systemInfo.OSEnableHomeButtonMenu;
    OSIsHomeButtonMenuEnabled = imports->coreinit.systemInfo.OSIsHomeButtonMenuEnabled;
    __OSGetProcessSDKVersion  = imports->coreinit.systemInfo.__OSGetProcessSDKVersion;

    // coreinit/thread
    OSCancelThread             = imports->coreinit.thread.OSCancelThread;
    OSCheckActiveThreads       = imports->coreinit.thread.OSCheckActiveThreads;
    OSCheckThreadStackUsage    = imports->coreinit.thread.OSCheckThreadStackUsage;
    OSClearThreadStackUsage    = imports->coreinit.thread.OSClearThreadStackUsage;
    OSContinueThread           = imports->coreinit.thread.OSContinueThread;
    OSCreateThread             = imports->coreinit.thread.OSCreateThread;
    OSDetachThread             = imports->coreinit.thread.OSDetachThread;
    OSExitThread               = imports->coreinit.thread.OSExitThread;
    OSGetActiveThreadLink      = imports->coreinit.thread.OSGetActiveThreadLink;
    OSGetCurrentThread         = imports->coreinit.thread.OSGetCurrentThread;
    OSGetDefaultThread         = imports->coreinit.thread.OSGetDefaultThread;
    OSGetStackPointer          = imports->coreinit.thread.OSGetStackPointer;
    OSGetThreadAffinity        = imports->coreinit.thread.OSGetThreadAffinity;
    OSGetThreadName            = imports->coreinit.thread.OSGetThreadName;
    OSGetThreadPriority        = imports->coreinit.thread.OSGetThreadPriority;
    OSGetThreadSpecific        = imports->coreinit.thread.OSGetThreadSpecific;
    OSIsThreadSuspended        = imports->coreinit.thread.OSIsThreadSuspended;
    OSIsThreadTerminated       = imports->coreinit.thread.OSIsThreadTerminated;
    OSJoinThread               = imports->coreinit.thread.OSJoinThread;
    OSResumeThread             = imports->coreinit.thread.OSResumeThread;
    OSRunThread                = imports->coreinit.thread.OSRunThread;
    OSSetThreadAffinity        = imports->coreinit.thread.OSSetThreadAffinity;
    OSSetThreadCancelState     = imports->coreinit.thread.OSSetThreadCancelState;
    OSSetThreadCleanupCallback = imports->coreinit.thread.OSSetThreadCleanupCallback;
    OSSetThreadDeallocator     = imports->coreinit.thread.OSSetThreadDeallocator;
    OSSetThreadName            = imports->coreinit.thread.OSSetThreadName;
    OSSetThreadPriority        = imports->coreinit.thread.OSSetThreadPriority;
    OSSetThreadRunQuantum      = imports->coreinit.thread.OSSetThreadRunQuantum;
    OSSetThreadSpecific        = imports->coreinit.thread.OSSetThreadSpecific;
    OSSetThreadStackUsage      = imports->coreinit.thread.OSSetThreadStackUsage;
    OSSleepThread              = imports->coreinit.thread.OSSleepThread;
    OSSleepTicks               = imports->coreinit.thread.OSSleepTicks;
    OSSuspendThread            = imports->coreinit.thread.OSSuspendThread;
    __OSSuspendThreadNolock    = imports->coreinit.thread.__OSSuspendThreadNolock;
    OSTestThreadCancel         = imports->coreinit.thread.OSTestThreadCancel;
    OSWakeupThread             = imports->coreinit.thread.OSWakeupThread;
    OSYieldThread              = imports->coreinit.thread.OSYieldThread;

    // coreinit/core
    OSGetCoreId = imports->coreinit.core.OSGetCoreId;

    // coreinit/alarm
    OSCancelAlarm      = imports->coreinit.alarm.OSCancelAlarm;
    OSCreateAlarm      = imports->coreinit.alarm.OSCreateAlarm;
    OSGetAlarmUserData = imports->coreinit.alarm.OSGetAlarmUserData;
    OSSetAlarm         = imports->coreinit.alarm.OSSetAlarm;
    OSSetAlarmUserData = imports->coreinit.alarm.OSSetAlarmUserData;

    // coreinit/time
    OSGetTime             = imports->coreinit.time.OSGetTime;
    OSGetSystemTime       = imports->coreinit.time.OSGetSystemTime;
    OSGetTick             = imports->coreinit.time.OSGetTick;
    OSGetSystemTick       = imports->coreinit.time.OSGetSystemTick;
    OSCalendarTimeToTicks = imports->coreinit.time.OSCalendarTimeToTicks;
    OSTicksToCalendarTime = imports->coreinit.time.OSTicksToCalendarTime;

    // coreinit/messagequeue
    OSInitMessageQueue      = imports->coreinit.messageQueue.OSInitMessageQueue;
    OSInitMessageQueueEx    = imports->coreinit.messageQueue.OSInitMessageQueueEx;
    OSSendMessage           = imports->coreinit.messageQueue.OSSendMessage;
    OSReceiveMessage        = imports->coreinit.messageQueue.OSReceiveMessage;
    OSPeekMessage           = imports->coreinit.messageQueue.OSPeekMessage;
    OSGetSystemMessageQueue = imports->coreinit.messageQueue.OSGetSystemMessageQueue;

    // coreinit/ios
    IOS_Open        = imports->coreinit.ios.IOS_Open;
    IOS_Close       = imports->coreinit.ios.IOS_Close;
    IOS_Ioctl       = imports->coreinit.ios.IOS_Ioctl;
    IOS_IoctlAsync  = imports->coreinit.ios.IOS_IoctlAsync;
    IOS_Ioctlv      = imports->coreinit.ios.IOS_Ioctlv;
    IOS_IoctlvAsync = imports->coreinit.ios.IOS_IoctlvAsync;

    // coreinit/filesystem
    FSInit                      = imports->coreinit.filesystem.FSInit;
    FSShutdown                  = imports->coreinit.filesystem.FSShutdown;
    FSAddClient                 = imports->coreinit.filesystem.FSAddClient;
    FSDelClient                 = imports->coreinit.filesystem.FSDelClient;
    FSGetClientNum              = imports->coreinit.filesystem.FSGetClientNum;
    FSInitCmdBlock              = imports->coreinit.filesystem.FSInitCmdBlock;
    FSGetAsyncResult            = imports->coreinit.filesystem.FSGetAsyncResult;
    FSGetCwd                    = imports->coreinit.filesystem.FSGetCwd;
    FSGetCwdAsync               = imports->coreinit.filesystem.FSGetCwdAsync;
    FSChangeDir                 = imports->coreinit.filesystem.FSChangeDir;
    FSChangeDirAsync            = imports->coreinit.filesystem.FSChangeDirAsync;
    FSGetStat                   = imports->coreinit.filesystem.FSGetStat;
    FSGetStatAsync              = imports->coreinit.filesystem.FSGetStatAsync;
    FSRemove                    = imports->coreinit.filesystem.FSRemove;
    FSRemoveAsync               = imports->coreinit.filesystem.FSRemoveAsync;
    FSOpenFile                  = imports->coreinit.filesystem.FSOpenFile;
    FSOpenFileAsync             = imports->coreinit.filesystem.FSOpenFileAsync;
    FSCloseFile                 = imports->coreinit.filesystem.FSCloseFile;
    FSCloseFileAsync            = imports->coreinit.filesystem.FSCloseFileAsync;
    FSOpenFileEx                = imports->coreinit.filesystem.FSOpenFileEx;
    FSOpenFileExAsync           = imports->coreinit.filesystem.FSOpenFileExAsync;
    FSOpenDir                   = imports->coreinit.filesystem.FSOpenDir;
    FSOpenDirAsync              = imports->coreinit.filesystem.FSOpenDirAsync;
    FSMakeDir                   = imports->coreinit.filesystem.FSMakeDir;
    FSMakeDirAsync              = imports->coreinit.filesystem.FSMakeDirAsync;
    FSReadDir                   = imports->coreinit.filesystem.FSReadDir;
    FSReadDirAsync              = imports->coreinit.filesystem.FSReadDirAsync;
    FSCloseDir                  = imports->coreinit.filesystem.FSCloseDir;
    FSCloseDirAsync             = imports->coreinit.filesystem.FSCloseDirAsync;
    FSChangeMode                = imports->coreinit.filesystem.FSChangeMode;
    FSChangeModeAsync           = imports->coreinit.filesystem.FSChangeModeAsync;
    FSGetFreeSpaceSize          = imports->coreinit.filesystem.FSGetFreeSpaceSize;
    FSGetFreeSpaceSizeAsync     = imports->coreinit.filesystem.FSGetFreeSpaceSizeAsync;
    FSGetStatFile               = imports->coreinit.filesystem.FSGetStatFile;
    FSGetStatFileAsync          = imports->coreinit.filesystem.FSGetStatFileAsync;
    FSReadFile                  = imports->coreinit.filesystem.FSReadFile;
    FSReadFileAsync             = imports->coreinit.filesystem.FSReadFileAsync;
    FSReadFileWithPos           = imports->coreinit.filesystem.FSReadFileWithPos;
    FSReadFileWithPosAsync      = imports->coreinit.filesystem.FSReadFileWithPosAsync;
    FSWriteFile                 = imports->coreinit.filesystem.FSWriteFile;
    FSWriteFileAsync            = imports->coreinit.filesystem.FSWriteFileAsync;
    FSWriteFileWithPos          = imports->coreinit.filesystem.FSWriteFileWithPos;
    FSWriteFileWithPosAsync     = imports->coreinit.filesystem.FSWriteFileWithPosAsync;
    FSGetPosFile                = imports->coreinit.filesystem.FSGetPosFile;
    FSGetPosFileAsync           = imports->coreinit.filesystem.FSGetPosFileAsync;
    FSSetPosFile                = imports->coreinit.filesystem.FSSetPosFile;
    FSSetPosFileAsync           = imports->coreinit.filesystem.FSSetPosFileAsync;
    FSFlushFile                 = imports->coreinit.filesystem.FSFlushFile;
    FSFlushFileAsync            = imports->coreinit.filesystem.FSFlushFileAsync;
    FSTruncateFile              = imports->coreinit.filesystem.FSTruncateFile;
    FSTruncateFileAsync         = imports->coreinit.filesystem.FSTruncateFileAsync;
    FSRename                    = imports->coreinit.filesystem.FSRename;
    FSRenameAsync               = imports->coreinit.filesystem.FSRenameAsync;
    FSGetVolumeState            = imports->coreinit.filesystem.FSGetVolumeState;
    FSGetLastErrorCodeForViewer = imports->coreinit.filesystem.FSGetLastErrorCodeForViewer;
    FSGetMountSource            = imports->coreinit.filesystem.FSGetMountSource;
    FSMount                     = imports->coreinit.filesystem.FSMount;
    FSBindMount                 = imports->coreinit.filesystem.FSBindMount;

    // coreinit/filesystem_fsa
    FSAInit             = imports->coreinit.filesystemFsa.FSAInit;
    FSAAddClient        = imports->coreinit.filesystemFsa.FSAAddClient;
    FSADelClient        = imports->coreinit.filesystemFsa.FSADelClient;
    FSAGetStatusStr     = imports->coreinit.filesystemFsa.FSAGetStatusStr;
    FSAMount            = imports->coreinit.filesystemFsa.FSAMount;
    FSAUnmount          = imports->coreinit.filesystemFsa.FSAUnmount;
    FSAChangeDir        = imports->coreinit.filesystemFsa.FSAChangeDir;
    FSAChangeMode       = imports->coreinit.filesystemFsa.FSAChangeMode;
    FSAOpenFileEx       = imports->coreinit.filesystemFsa.FSAOpenFileEx;
    FSAGetStatFile      = imports->coreinit.filesystemFsa.FSAGetStatFile;
    FSAGetStat          = imports->coreinit.filesystemFsa.FSAGetStat;
    FSACloseFile        = imports->coreinit.filesystemFsa.FSACloseFile;
    FSAFlushFile        = imports->coreinit.filesystemFsa.FSAFlushFile;
    FSASetPosFile       = imports->coreinit.filesystemFsa.FSASetPosFile;
    FSATruncateFile     = imports->coreinit.filesystemFsa.FSATruncateFile;
    FSAWriteFile        = imports->coreinit.filesystemFsa.FSAWriteFile;
    FSAReadFile         = imports->coreinit.filesystemFsa.FSAReadFile;
    FSARemove           = imports->coreinit.filesystemFsa.FSARemove;
    FSARename           = imports->coreinit.filesystemFsa.FSARename;
    FSAOpenDir          = imports->coreinit.filesystemFsa.FSAOpenDir;
    FSAReadDir          = imports->coreinit.filesystemFsa.FSAReadDir;
    FSARewindDir        = imports->coreinit.filesystemFsa.FSARewindDir;
    FSACloseDir         = imports->coreinit.filesystemFsa.FSACloseDir;
    FSAMakeDir          = imports->coreinit.filesystemFsa.FSAMakeDir;
    FSAGetFreeSpaceSize = imports->coreinit.filesystemFsa.FSAGetFreeSpaceSize;
    FSAGetDeviceInfo    = imports->coreinit.filesystemFsa.FSAGetDeviceInfo;

    // gx2/aperture
    GX2AllocateTilingApertureEx = imports->gx2.aperture.GX2AllocateTilingApertureEx;
    GX2FreeTilingAperture       = imports->gx2.aperture.GX2FreeTilingAperture;

    // gx2/clear
    GX2ClearColor           = imports->gx2.clear.GX2ClearColor;
    GX2ClearDepthStencilEx  = imports->gx2.clear.GX2ClearDepthStencilEx;
    GX2ClearBuffersEx       = imports->gx2.clear.GX2ClearBuffersEx;
    GX2SetClearDepth        = imports->gx2.clear.GX2SetClearDepth;
    GX2SetClearStencil      = imports->gx2.clear.GX2SetClearStencil;
    GX2SetClearDepthStencil = imports->gx2.clear.GX2SetClearDepthStencil;

    // gx2/context
    GX2SetupContextStateEx        = imports->gx2.context.GX2SetupContextStateEx;
    GX2GetContextStateDisplayList = imports->gx2.context.GX2GetContextStateDisplayList;
    GX2SetContextState            = imports->gx2.context.GX2SetContextState;
    GX2SetDefaultState            = imports->gx2.context.GX2SetDefaultState;

    // gx2/debug
    _GX2DebugSetCaptureInterface = imports->gx2.debug._GX2DebugSetCaptureInterface;
    GX2DebugCaptureStart         = imports->gx2.debug.GX2DebugCaptureStart;
    GX2DebugCaptureEnd           = imports->gx2.debug.GX2DebugCaptureEnd;
    GX2DebugCaptureFrame         = imports->gx2.debug.GX2DebugCaptureFrame;
    GX2DebugCaptureFrames        = imports->gx2.debug.GX2DebugCaptureFrames;

    // gx2/display
    GX2SetTVEnable            = imports->gx2.display.GX2SetTVEnable;
    GX2SetDRCEnable           = imports->gx2.display.GX2SetDRCEnable;
    GX2CalcTVSize             = imports->gx2.display.GX2CalcTVSize;
    GX2CalcDRCSize            = imports->gx2.display.GX2CalcDRCSize;
    GX2SetTVBuffer            = imports->gx2.display.GX2SetTVBuffer;
    GX2SetDRCBuffer           = imports->gx2.display.GX2SetDRCBuffer;
    GX2SetTVScale             = imports->gx2.display.GX2SetTVScale;
    GX2SetDRCScale            = imports->gx2.display.GX2SetDRCScale;
    GX2GetSystemTVAspectRatio = imports->gx2.display.GX2GetSystemTVAspectRatio;
    GX2GetSystemTVScanMode    = imports->gx2.display.GX2GetSystemTVScanMode;
    GX2GetSystemDRCScanMode   = imports->gx2.display.GX2GetSystemDRCScanMode;
    GX2GetSystemDRCMode       = imports->gx2.display.GX2GetSystemDRCMode;
    GX2SetDRCConnectCallback  = imports->gx2.display.GX2SetDRCConnectCallback;

    // gx2/displaylist
    GX2BeginDisplayListEx        = imports->gx2.displayList.GX2BeginDisplayListEx;
    GX2EndDisplayList            = imports->gx2.displayList.GX2EndDisplayList;
    GX2DirectCallDisplayList     = imports->gx2.displayList.GX2DirectCallDisplayList;
    GX2CallDisplayList           = imports->gx2.displayList.GX2CallDisplayList;
    GX2GetDisplayListWriteStatus = imports->gx2.displayList.GX2GetDisplayListWriteStatus;
    GX2GetCurrentDisplayList     = imports->gx2.displayList.GX2GetCurrentDisplayList;
    GX2CopyDisplayList           = imports->gx2.displayList.GX2CopyDisplayList;

    // gx2/draw
    GX2SetAttribBuffer          = imports->gx2.draw.GX2SetAttribBuffer;
    GX2DrawEx                   = imports->gx2.draw.GX2DrawEx;
    GX2DrawEx2                  = imports->gx2.draw.GX2DrawEx2;
    GX2DrawIndexedEx            = imports->gx2.draw.GX2DrawIndexedEx;
    GX2DrawIndexedEx2           = imports->gx2.draw.GX2DrawIndexedEx2;
    GX2DrawIndexedImmediateEx   = imports->gx2.draw.GX2DrawIndexedImmediateEx;
    GX2SetPrimitiveRestartIndex = imports->gx2.draw.GX2SetPrimitiveRestartIndex;

    // gx2/event
    GX2DrawDone                  = imports->gx2.event.GX2DrawDone;
    GX2WaitForVsync              = imports->gx2.event.GX2WaitForVsync;
    GX2WaitForFlip               = imports->gx2.event.GX2WaitForFlip;
    GX2SetEventCallback          = imports->gx2.event.GX2SetEventCallback;
    GX2GetEventCallback          = imports->gx2.event.GX2GetEventCallback;
    GX2GetRetiredTimeStamp       = imports->gx2.event.GX2GetRetiredTimeStamp;
    GX2GetLastSubmittedTimeStamp = imports->gx2.event.GX2GetLastSubmittedTimeStamp;
    GX2GetSwapStatus             = imports->gx2.event.GX2GetSwapStatus;
    GX2WaitTimeStamp             = imports->gx2.event.GX2WaitTimeStamp;

    // gx2/mem
    GX2Invalidate = imports->gx2.mem.GX2Invalidate;

    // gx2/registers
    GX2SetAAMask                     = imports->gx2.registers.GX2SetAAMask;
    GX2InitAAMaskReg                 = imports->gx2.registers.GX2InitAAMaskReg;
    GX2GetAAMaskReg                  = imports->gx2.registers.GX2GetAAMaskReg;
    GX2SetAAMaskReg                  = imports->gx2.registers.GX2SetAAMaskReg;
    GX2SetAlphaTest                  = imports->gx2.registers.GX2SetAlphaTest;
    GX2InitAlphaTestReg              = imports->gx2.registers.GX2InitAlphaTestReg;
    GX2GetAlphaTestReg               = imports->gx2.registers.GX2GetAlphaTestReg;
    GX2SetAlphaTestReg               = imports->gx2.registers.GX2SetAlphaTestReg;
    GX2SetAlphaToMask                = imports->gx2.registers.GX2SetAlphaToMask;
    GX2InitAlphaToMaskReg            = imports->gx2.registers.GX2InitAlphaToMaskReg;
    GX2GetAlphaToMaskReg             = imports->gx2.registers.GX2GetAlphaToMaskReg;
    GX2SetAlphaToMaskReg             = imports->gx2.registers.GX2SetAlphaToMaskReg;
    GX2SetBlendConstantColor         = imports->gx2.registers.GX2SetBlendConstantColor;
    GX2InitBlendConstantColorReg     = imports->gx2.registers.GX2InitBlendConstantColorReg;
    GX2GetBlendConstantColorReg      = imports->gx2.registers.GX2GetBlendConstantColorReg;
    GX2SetBlendConstantColorReg      = imports->gx2.registers.GX2SetBlendConstantColorReg;
    GX2SetBlendControl               = imports->gx2.registers.GX2SetBlendControl;
    GX2InitBlendControlReg           = imports->gx2.registers.GX2InitBlendControlReg;
    GX2GetBlendControlReg            = imports->gx2.registers.GX2GetBlendControlReg;
    GX2SetBlendControlReg            = imports->gx2.registers.GX2SetBlendControlReg;
    GX2SetColorControl               = imports->gx2.registers.GX2SetColorControl;
    GX2InitColorControlReg           = imports->gx2.registers.GX2InitColorControlReg;
    GX2GetColorControlReg            = imports->gx2.registers.GX2GetColorControlReg;
    GX2SetColorControlReg            = imports->gx2.registers.GX2SetColorControlReg;
    GX2SetDepthOnlyControl           = imports->gx2.registers.GX2SetDepthOnlyControl;
    GX2SetDepthStencilControl        = imports->gx2.registers.GX2SetDepthStencilControl;
    GX2InitDepthStencilControlReg    = imports->gx2.registers.GX2InitDepthStencilControlReg;
    GX2GetDepthStencilControlReg     = imports->gx2.registers.GX2GetDepthStencilControlReg;
    GX2SetDepthStencilControlReg     = imports->gx2.registers.GX2SetDepthStencilControlReg;
    GX2SetStencilMask                = imports->gx2.registers.GX2SetStencilMask;
    GX2InitStencilMaskReg            = imports->gx2.registers.GX2InitStencilMaskReg;
    GX2GetStencilMaskReg             = imports->gx2.registers.GX2GetStencilMaskReg;
    GX2SetStencilMaskReg             = imports->gx2.registers.GX2SetStencilMaskReg;
    GX2SetLineWidth                  = imports->gx2.registers.GX2SetLineWidth;
    GX2InitLineWidthReg              = imports->gx2.registers.GX2InitLineWidthReg;
    GX2GetLineWidthReg               = imports->gx2.registers.GX2GetLineWidthReg;
    GX2SetLineWidthReg               = imports->gx2.registers.GX2SetLineWidthReg;
    GX2SetPointSize                  = imports->gx2.registers.GX2SetPointSize;
    GX2InitPointSizeReg              = imports->gx2.registers.GX2InitPointSizeReg;
    GX2GetPointSizeReg               = imports->gx2.registers.GX2GetPointSizeReg;
    GX2SetPointSizeReg               = imports->gx2.registers.GX2SetPointSizeReg;
    GX2SetPointLimits                = imports->gx2.registers.GX2SetPointLimits;
    GX2InitPointLimitsReg            = imports->gx2.registers.GX2InitPointLimitsReg;
    GX2GetPointLimitsReg             = imports->gx2.registers.GX2GetPointLimitsReg;
    GX2SetPointLimitsReg             = imports->gx2.registers.GX2SetPointLimitsReg;
    GX2SetCullOnlyControl            = imports->gx2.registers.GX2SetCullOnlyControl;
    GX2SetPolygonControl             = imports->gx2.registers.GX2SetPolygonControl;
    GX2InitPolygonControlReg         = imports->gx2.registers.GX2InitPolygonControlReg;
    GX2GetPolygonControlReg          = imports->gx2.registers.GX2GetPolygonControlReg;
    GX2SetPolygonControlReg          = imports->gx2.registers.GX2SetPolygonControlReg;
    GX2SetPolygonOffset              = imports->gx2.registers.GX2SetPolygonOffset;
    GX2InitPolygonOffsetReg          = imports->gx2.registers.GX2InitPolygonOffsetReg;
    GX2GetPolygonOffsetReg           = imports->gx2.registers.GX2GetPolygonOffsetReg;
    GX2SetPolygonOffsetReg           = imports->gx2.registers.GX2SetPolygonOffsetReg;
    GX2SetScissor                    = imports->gx2.registers.GX2SetScissor;
    GX2InitScissorReg                = imports->gx2.registers.GX2InitScissorReg;
    GX2GetScissorReg                 = imports->gx2.registers.GX2GetScissorReg;
    GX2SetScissorReg                 = imports->gx2.registers.GX2SetScissorReg;
    GX2SetTargetChannelMasks         = imports->gx2.registers.GX2SetTargetChannelMasks;
    GX2InitTargetChannelMasksReg     = imports->gx2.registers.GX2InitTargetChannelMasksReg;
    GX2GetTargetChannelMasksReg      = imports->gx2.registers.GX2GetTargetChannelMasksReg;
    GX2SetTargetChannelMasksReg      = imports->gx2.registers.GX2SetTargetChannelMasksReg;
    GX2SetViewport                   = imports->gx2.registers.GX2SetViewport;
    GX2InitViewportReg               = imports->gx2.registers.GX2InitViewportReg;
    GX2GetViewportReg                = imports->gx2.registers.GX2GetViewportReg;
    GX2SetViewportReg                = imports->gx2.registers.GX2SetViewportReg;
    GX2SetRasterizerClipControl      = imports->gx2.registers.GX2SetRasterizerClipControl;
    GX2SetRasterizerClipControlEx    = imports->gx2.registers.GX2SetRasterizerClipControlEx;
    GX2SetRasterizerClipControlHalfZ = imports->gx2.registers.GX2SetRasterizerClipControlHalfZ;

    // gx2/sampler
    GX2InitSampler             = imports->gx2.sampler.GX2InitSampler;
    GX2InitSamplerBorderType   = imports->gx2.sampler.GX2InitSamplerBorderType;
    GX2InitSamplerClamping     = imports->gx2.sampler.GX2InitSamplerClamping;
    GX2InitSamplerDepthCompare = imports->gx2.sampler.GX2InitSamplerDepthCompare;
    GX2InitSamplerFilterAdjust = imports->gx2.sampler.GX2InitSamplerFilterAdjust;
    GX2InitSamplerLOD          = imports->gx2.sampler.GX2InitSamplerLOD;
    GX2InitSamplerLODAdjust    = imports->gx2.sampler.GX2InitSamplerLODAdjust;
    GX2InitSamplerRoundingMode = imports->gx2.sampler.GX2InitSamplerRoundingMode;
    GX2InitSamplerXYFilter     = imports->gx2.sampler.GX2InitSamplerXYFilter;
    GX2InitSamplerZMFilter     = imports->gx2.sampler.GX2InitSamplerZMFilter;

    // gx2/semaphore
    GX2SetSemaphore = imports->gx2.semaphore.GX2SetSemaphore;

    // gx2/shaders
    GX2CalcGeometryShaderInputRingBufferSize  = imports->gx2.shaders.GX2CalcGeometryShaderInputRingBufferSize;
    GX2CalcGeometryShaderOutputRingBufferSize = imports->gx2.shaders.GX2CalcGeometryShaderOutputRingBufferSize;
    GX2CalcFetchShaderSizeEx                  = imports->gx2.shaders.GX2CalcFetchShaderSizeEx;
    GX2InitFetchShaderEx                      = imports->gx2.shaders.GX2InitFetchShaderEx;
    GX2SetFetchShader                         = imports->gx2.shaders.GX2SetFetchShader;
    GX2SetVertexShader                        = imports->gx2.shaders.GX2SetVertexShader;
    GX2SetPixelShader                         = imports->gx2.shaders.GX2SetPixelShader;
    GX2SetGeometryShader                      = imports->gx2.shaders.GX2SetGeometryShader;
    GX2SetVertexSampler                       = imports->gx2.shaders.GX2SetVertexSampler;
    GX2SetPixelSampler                        = imports->gx2.shaders.GX2SetPixelSampler;
    GX2SetGeometrySampler                     = imports->gx2.shaders.GX2SetGeometrySampler;
    GX2SetVertexUniformReg                    = imports->gx2.shaders.GX2SetVertexUniformReg;
    GX2SetPixelUniformReg                     = imports->gx2.shaders.GX2SetPixelUniformReg;
    GX2SetVertexUniformBlock                  = imports->gx2.shaders.GX2SetVertexUniformBlock;
    GX2SetPixelUniformBlock                   = imports->gx2.shaders.GX2SetPixelUniformBlock;
    GX2SetGeometryUniformBlock                = imports->gx2.shaders.GX2SetGeometryUniformBlock;
    GX2SetShaderModeEx                        = imports->gx2.shaders.GX2SetShaderModeEx;
    GX2SetStreamOutEnable                     = imports->gx2.shaders.GX2SetStreamOutEnable;
    GX2SetGeometryShaderInputRingBuffer       = imports->gx2.shaders.GX2SetGeometryShaderInputRingBuffer;
    GX2SetGeometryShaderOutputRingBuffer      = imports->gx2.shaders.GX2SetGeometryShaderOutputRingBuffer;
    GX2GetPixelShaderGPRs                     = imports->gx2.shaders.GX2GetPixelShaderGPRs;
    GX2GetPixelShaderStackEntries             = imports->gx2.shaders.GX2GetPixelShaderStackEntries;
    GX2GetVertexShaderGPRs                    = imports->gx2.shaders.GX2GetVertexShaderGPRs;
    GX2GetVertexShaderStackEntries            = imports->gx2.shaders.GX2GetVertexShaderStackEntries;
    GX2GetGeometryShaderGPRs                  = imports->gx2.shaders.GX2GetGeometryShaderGPRs;
    GX2GetGeometryShaderStackEntries          = imports->gx2.shaders.GX2GetGeometryShaderStackEntries;

    // gx2/state
    GX2Init          = imports->gx2.state.GX2Init;
    GX2Shutdown      = imports->gx2.state.GX2Shutdown;
    GX2Flush         = imports->gx2.state.GX2Flush;
    GX2ResetGPU      = imports->gx2.state.GX2ResetGPU;
    GX2GetMainCoreId = imports->gx2.state.GX2GetMainCoreId;

    // gx2/surface
    GX2CalcSurfaceSizeAndAlignment = imports->gx2.surface.GX2CalcSurfaceSizeAndAlignment;
    GX2CalcDepthBufferHiZInfo      = imports->gx2.surface.GX2CalcDepthBufferHiZInfo;
    GX2CalcColorBufferAuxInfo      = imports->gx2.surface.GX2CalcColorBufferAuxInfo;
    GX2SetColorBuffer              = imports->gx2.surface.GX2SetColorBuffer;
    GX2SetDepthBuffer              = imports->gx2.surface.GX2SetDepthBuffer;
    GX2InitColorBufferRegs         = imports->gx2.surface.GX2InitColorBufferRegs;
    GX2InitDepthBufferRegs         = imports->gx2.surface.GX2InitDepthBufferRegs;
    GX2InitDepthBufferHiZEnable    = imports->gx2.surface.GX2InitDepthBufferHiZEnable;
    GX2GetSurfaceSwizzle           = imports->gx2.surface.GX2GetSurfaceSwizzle;
    GX2SetSurfaceSwizzle           = imports->gx2.surface.GX2SetSurfaceSwizzle;
    GX2CopySurface                 = imports->gx2.surface.GX2CopySurface;
    GX2CopySurfaceEx               = imports->gx2.surface.GX2CopySurfaceEx;
    GX2ResolveAAColorBuffer        = imports->gx2.surface.GX2ResolveAAColorBuffer;

    // gx2/swap
    GX2CopyColorBufferToScanBuffer = imports->gx2.swap.GX2CopyColorBufferToScanBuffer;
    GX2GetCurrentScanBuffer        = imports->gx2.swap.GX2GetCurrentScanBuffer;
    GX2SwapScanBuffers             = imports->gx2.swap.GX2SwapScanBuffers;
    GX2GetLastFrame                = imports->gx2.swap.GX2GetLastFrame;
    GX2GetLastFrameGamma           = imports->gx2.swap.GX2GetLastFrameGamma;
    GX2GetSwapInterval             = imports->gx2.swap.GX2GetSwapInterval;
    GX2SetSwapInterval             = imports->gx2.swap.GX2SetSwapInterval;

    // gx2/temp
    GX2TempGetGPUVersion = imports->gx2.temp.GX2TempGetGPUVersion;

    // gx2/tessellation
    GX2SetTessellation         = imports->gx2.tessellation.GX2SetTessellation;
    GX2SetMinTessellationLevel = imports->gx2.tessellation.GX2SetMinTessellationLevel;
    GX2SetMaxTessellationLevel = imports->gx2.tessellation.GX2SetMaxTessellationLevel;

    // gx2/texture
    GX2InitTextureRegs    = imports->gx2.texture.GX2InitTextureRegs;
    GX2SetPixelTexture    = imports->gx2.texture.GX2SetPixelTexture;
    GX2SetVertexTexture   = imports->gx2.texture.GX2SetVertexTexture;
    GX2SetGeometryTexture = imports->gx2.texture.GX2SetGeometryTexture;

    // snd_core/core
    AXInit                       = imports->snd_core.core.AXInit;
    AXInitEx                     = imports->snd_core.core.AXInitEx;
    AXQuit                       = imports->snd_core.core.AXQuit;
    AXIsInit                     = imports->snd_core.core.AXIsInit;
    AXSetDefaultMixerSelect      = imports->snd_core.core.AXSetDefaultMixerSelect;
    AXGetDefaultMixerSelect      = imports->snd_core.core.AXGetDefaultMixerSelect;
    AXRegisterAppFrameCallback   = imports->snd_core.core.AXRegisterAppFrameCallback;
    AXDeregisterAppFrameCallback = imports->snd_core.core.AXDeregisterAppFrameCallback;
    AXRegisterFrameCallback      = imports->snd_core.core.AXRegisterFrameCallback;
    AXRegisterCallback           = imports->snd_core.core.AXRegisterCallback;
    AXGetInputSamplesPerFrame    = imports->snd_core.core.AXGetInputSamplesPerFrame;
    AXGetInputSamplesPerSec      = imports->snd_core.core.AXGetInputSamplesPerSec;

    // snd_core/device
    AXGetDeviceMode                  = imports->snd_core.device.AXGetDeviceMode;
    AXGetDeviceFinalMixCallback      = imports->snd_core.device.AXGetDeviceFinalMixCallback;
    AXRegisterDeviceFinalMixCallback = imports->snd_core.device.AXRegisterDeviceFinalMixCallback;
    AXGetAuxCallback                 = imports->snd_core.device.AXGetAuxCallback;
    AXRegisterAuxCallback            = imports->snd_core.device.AXRegisterAuxCallback;
    AXSetAuxReturnVolume             = imports->snd_core.device.AXSetAuxReturnVolume;
    AXSetDeviceUpsampleStage         = imports->snd_core.device.AXSetDeviceUpsampleStage;
    AXGetDeviceUpsampleStage         = imports->snd_core.device.AXGetDeviceUpsampleStage;
    AXSetDeviceRemixMatrix           = imports->snd_core.device.AXSetDeviceRemixMatrix;
    AXGetDeviceRemixMatrix           = imports->snd_core.device.AXGetDeviceRemixMatrix;
    AXGetDeviceFinalOutput           = imports->snd_core.device.AXGetDeviceFinalOutput;

    // snd_core/voice
    AXUserIsProtected         = imports->snd_core.voice.AXUserIsProtected;
    AXUserBegin               = imports->snd_core.voice.AXUserBegin;
    AXUserEnd                 = imports->snd_core.voice.AXUserEnd;
    AXVoiceBegin              = imports->snd_core.voice.AXVoiceBegin;
    AXVoiceEnd                = imports->snd_core.voice.AXVoiceEnd;
    AXVoiceIsProtected        = imports->snd_core.voice.AXVoiceIsProtected;
    AXAcquireVoice            = imports->snd_core.voice.AXAcquireVoice;
    AXAcquireVoiceEx          = imports->snd_core.voice.AXAcquireVoiceEx;
    AXCheckVoiceOffsets       = imports->snd_core.voice.AXCheckVoiceOffsets;
    AXFreeVoice               = imports->snd_core.voice.AXFreeVoice;
    AXGetMaxVoices            = imports->snd_core.voice.AXGetMaxVoices;
    AXGetVoiceCurrentOffsetEx = imports->snd_core.voice.AXGetVoiceCurrentOffsetEx;
    AXGetVoiceLoopCount       = imports->snd_core.voice.AXGetVoiceLoopCount;
    AXGetVoiceOffsets         = imports->snd_core.voice.AXGetVoiceOffsets;
    AXIsVoiceRunning          = imports->snd_core.voice.AXIsVoiceRunning;
    AXSetVoiceAdpcm           = imports->snd_core.voice.AXSetVoiceAdpcm;
    AXSetVoiceAdpcmLoop       = imports->snd_core.voice.AXSetVoiceAdpcmLoop;
    AXSetVoiceCurrentOffset   = imports->snd_core.voice.AXSetVoiceCurrentOffset;
    AXSetVoiceCurrentOffsetEx = imports->snd_core.voice.AXSetVoiceCurrentOffsetEx;
    AXSetVoiceDeviceMix       = imports->snd_core.voice.AXSetVoiceDeviceMix;
    AXSetVoiceEndOffset       = imports->snd_core.voice.AXSetVoiceEndOffset;
    AXSetVoiceEndOffsetEx     = imports->snd_core.voice.AXSetVoiceEndOffsetEx;
    AXSetVoiceLoopOffset      = imports->snd_core.voice.AXSetVoiceLoopOffset;
    AXSetVoiceLoopOffsetEx    = imports->snd_core.voice.AXSetVoiceLoopOffsetEx;
    AXSetVoiceLoop            = imports->snd_core.voice.AXSetVoiceLoop;
    AXSetVoiceOffsets         = imports->snd_core.voice.AXSetVoiceOffsets;
    AXSetVoiceOffsetsEx       = imports->snd_core.voice.AXSetVoiceOffsetsEx;
    AXSetVoiceSamplesAddr     = imports->snd_core.voice.AXSetVoiceSamplesAddr;
    AXSetVoiceSrc             = imports->snd_core.voice.AXSetVoiceSrc;
    AXSetVoiceSrcRatio        = imports->snd_core.voice.AXSetVoiceSrcRatio;
    AXSetVoiceSrcType         = imports->snd_core.voice.AXSetVoiceSrcType;
    AXSetVoiceState           = imports->snd_core.voice.AXSetVoiceState;
    AXSetVoiceType            = imports->snd_core.voice.AXSetVoiceType;
    AXSetVoiceVe              = imports->snd_core.voice.AXSetVoiceVe;
    AXComputeLpfCoefs         = imports->snd_core.voice.AXComputeLpfCoefs;
    AXSetVoiceLpf             = imports->snd_core.voice.AXSetVoiceLpf;
    AXSetVoiceLpfCoefs        = imports->snd_core.voice.AXSetVoiceLpfCoefs;
    AXSetVoiceBiquad          = imports->snd_core.voice.AXSetVoiceBiquad;
    AXSetVoiceBiquadCoefs     = imports->snd_core.voice.AXSetVoiceBiquadCoefs;

    // nsysnet/_netdb
    cut_gethostbyaddr = imports->nsysnet.netDb.gethostbyaddr;
    cut_gethostbyname = imports->nsysnet.netDb.gethostbyname;
    cut_getaddrinfo   = imports->nsysnet.netDb.getaddrinfo;
    cut_freeaddrinfo  = imports->nsysnet.netDb.freeaddrinfo;
    cut_getnameinfo   = imports->nsysnet.netDb.getnameinfo;
    cut_gai_strerror  = imports->nsysnet.netDb.gai_strerror;
    cut_get_h_errno   = imports->nsysnet.netDb.get_h_errno;

    // nsysnet/_socket
    socket_lib_init   = imports->nsysnet.socket.socket_lib_init;
    socket_lib_finish = imports->nsysnet.socket.socket_lib_finish;
    cut_accept        = imports->nsysnet.socket.accept;
    cut_bind          = imports->nsysnet.socket.bind;
    cut_socketclose   = imports->nsysnet.socket.socketclose;
    cut_connect       = imports->nsysnet.socket.connect;
    cut_getpeername   = imports->nsysnet.socket.getpeername;
    cut_getsockname   = imports->nsysnet.socket.getsockname;
    cut_getsockopt    = imports->nsysnet.socket.getsockopt;
    cut_listen        = imports->nsysnet.socket.listen;
    cut_recv          = imports->nsysnet.socket.recv;
    cut_recvfrom      = imports->nsysnet.socket.recvfrom;
    cut_send          = imports->nsysnet.socket.send;
    cut_sendto        = imports->nsysnet.socket.sendto;
    cut_setsockopt    = imports->nsysnet.socket.setsockopt;
    cut_shutdown      = imports->nsysnet.socket.shutdown;
    cut_socket        = imports->nsysnet.socket.socket;
    cut_select        = imports->nsysnet.socket.select;
    cut_inet_ntop     = imports->nsysnet.socket.inet_ntop;
    cut_inet_pton     = imports->nsysnet.socket.inet_pton;
    cut_socketlasterr = imports->nsysnet.socket.socketlasterr;

    // input/vpad
    VPADRead                          = imports->vpad.input.VPADRead;
    VPADGetTPCalibrationParam         = imports->vpad.input.VPADGetTPCalibrationParam;
    VPADSetTPCalibrationParam         = imports->vpad.input.VPADSetTPCalibrationParam;
    VPADGetTPCalibratedPoint          = imports->vpad.input.VPADGetTPCalibratedPoint;
    VPADGetTPCalibratedPointEx        = imports->vpad.input.VPADGetTPCalibratedPointEx;
    VPADSetAccParam                   = imports->vpad.input.VPADSetAccParam;
    VPADGetAccParam                   = imports->vpad.input.VPADGetAccParam;
    VPADSetBtnRepeat                  = imports->vpad.input.VPADSetBtnRepeat;
    VPADEnableStickCrossClamp         = imports->vpad.input.VPADEnableStickCrossClamp;
    VPADDisableStickCrossClamp        = imports->vpad.input.VPADDisableStickCrossClamp;
    VPADSetLStickClampThreshold       = imports->vpad.input.VPADSetLStickClampThreshold;
    VPADSetRStickClampThreshold       = imports->vpad.input.VPADSetRStickClampThreshold;
    VPADGetGyroZeroDriftMode          = imports->vpad.input.VPADGetGyroZeroDriftMode;
    VPADGetLStickClampThreshold       = imports->vpad.input.VPADGetLStickClampThreshold;
    VPADGetRStickClampThreshold       = imports->vpad.input.VPADGetRStickClampThreshold;
    VPADSetCrossStickEmulationParamsL = imports->vpad.input.VPADSetCrossStickEmulationParamsL;
    VPADSetCrossStickEmulationParamsR = imports->vpad.input.VPADSetCrossStickEmulationParamsR;
    VPADGetCrossStickEmulationParamsL = imports->vpad.input.VPADGetCrossStickEmulationParamsL;
    VPADGetCrossStickEmulationParamsR = imports->vpad.input.VPADGetCrossStickEmulationParamsR;
    VPADSetGyroDirReviseBase          = imports->vpad.input.VPADSetGyroDirReviseBase;
    VPADSetGyroDirReviseParam         = imports->vpad.input.VPADSetGyroDirReviseParam;
    VPADSetGyroDirection              = imports->vpad.input.VPADSetGyroDirection;
    VPADSetGyroZeroDriftMode          = imports->vpad.input.VPADSetGyroZeroDriftMode;
    VPADDisableGyroDirRevise          = imports->vpad.input.VPADDisableGyroDirRevise;
    VPADControlMotor                  = imports->vpad.input.VPADControlMotor;
    VPADStopMotor                     = imports->vpad.input.VPADStopMotor;
    VPADSetLcdMode                    = imports->vpad.input.VPADSetLcdMode;
    VPADGetLcdMode                    = imports->vpad.input.VPADGetLcdMode;
    VPADSetSamplingCallback           = imports->vpad.input.VPADSetSamplingCallback;
    VPADGetButtonProcMode             = imports->vpad.input.VPADGetButtonProcMode;

    // nlibcurl
    curl_global_init_mem = imports->nlibcurl.curl_global_init_mem;
    curl_global_init     = imports->nlibcurl.curl_global_init;

    curl_slist_append   = imports->nlibcurl.curl_slist_append;
    curl_slist_free_all = imports->nlibcurl.curl_slist_free_all;

    curl_easy_strerror = imports->nlibcurl.curl_easy_strerror;

    curl_share_init    = imports->nlibcurl.curl_share_init;
    curl_share_setopt  = imports->nlibcurl.curl_share_setopt;
    curl_share_cleanup = imports->nlibcurl.curl_share_cleanup;

    mw_curl_easy_init = imports->nlibcurl.mw_curl_easy_init;
    curl_easy_init    = imports->nlibcurl.curl_easy_init;
    curl_easy_reset   = imports->nlibcurl.curl_easy_reset;
    curl_easy_setopt  = imports->nlibcurl.curl_easy_setopt;
    curl_easy_getinfo = imports->nlibcurl.curl_easy_getinfo;
    curl_easy_perform = imports->nlibcurl.curl_easy_perform;
    curl_easy_cleanup = imports->nlibcurl.curl_easy_cleanup;
    curl_easy_pause   = imports->nlibcurl.curl_easy_pause;

    curl_multi_init          = imports->nlibcurl.curl_multi_init;
    curl_multi_add_handle    = imports->nlibcurl.curl_multi_add_handle;
    curl_multi_perform       = imports->nlibcurl.curl_multi_perform;
    curl_multi_info_read     = imports->nlibcurl.curl_multi_info_read;
    curl_multi_remove_handle = imports->nlibcurl.curl_multi_remove_handle;
    curl_multi_setopt        = imports->nlibcurl.curl_multi_setopt;
    curl_multi_fdset         = imports->nlibcurl.curl_multi_fdset;
    curl_multi_cleanup       = imports->nlibcurl.curl_multi_cleanup;
    curl_multi_timeout       = imports->nlibcurl.curl_multi_timeout;

    // nn_act
    nn::act::Initialize             = imports->nn_act.Initialize__Q2_2nn3actFv;
    nn::act::AcquireNexServiceToken = imports->nn_act.AcquireNexServiceToken__Q2_2nn3actFP26ACTNexAuthenticationResultUi;
    nn::act::GetAccountId           = imports->nn_act.GetAccountId__Q2_2nn3actFPc;
    nn::act::GetPrincipalId         = imports->nn_act.GetPrincipalId__Q2_2nn3actFv;

    // nn_fp
    nn::fp::Initialize = imports->nn_fp.Initialize__Q2_2nn2fpFv;
    nn::fp::LoginAsync = imports->nn_fp.LoginAsync__Q2_2nn2fpFPFQ2_2nn6ResultPv_vPv;
}
