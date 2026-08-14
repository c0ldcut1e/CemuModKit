#pragma once

#include "../debug.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitDebug
{
    void (*OSReport)(const char *fmt, ...);
    void (*OSFatal)(const char *msg);
    uint32_t (*OSGetSymbolName)(uint32_t addr, char *symbolNameBuf, uint32_t symbolNameBufSize);
    uint32_t (*OSGetUPID)();
    BOOL (*OSIsDebuggerPresent)();
    BOOL (*DisassemblePPCOpcode)(uint32_t *opcode, char *buffer, uint32_t bufferSize, DisassemblyFindSymbolFn findSymbolFn,
                                 DisassemblePPCFlags flags);
    void (*DisassemblePPCRange)(void *start, void *end, DisassemblyPrintFn printFn, DisassemblyFindSymbolFn findSymbolFn, DisassemblePPCFlags flags);
} ImportsCoreInitDebug;

#ifdef __cplusplus
}
#endif
