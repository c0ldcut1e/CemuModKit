#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*DisassemblyPrintFn)(const char *fmt, ...);

typedef uint32_t (*DisassemblyFindSymbolFn)(uint32_t addr, char *symbolNameBuf, uint32_t symbolNameBufSize);

typedef enum DisassemblePPCFlags
{
    DISASSEMBLE_PPC_FLAGS_NONE = 0,
} DisassemblePPCFlags;

CUT_IMPORT void (*OSReport)(const char *fmt, ...);

CUT_IMPORT void (*OSFatal)(const char *msg);

CUT_IMPORT uint32_t (*OSGetSymbolName)(uint32_t addr, char *symbolNameBuf, uint32_t symbolNameBufSize);

CUT_IMPORT uint32_t (*OSGetUPID)();

CUT_IMPORT BOOL (*OSIsDebuggerPresent)();

CUT_IMPORT BOOL (*DisassemblePPCOpcode)(uint32_t *opcode, char *buffer, uint32_t bufferSize, DisassemblyFindSymbolFn findSymbolFn,
                                        DisassemblePPCFlags flags);

CUT_IMPORT void (*DisassemblePPCRange)(void *start, void *end, DisassemblyPrintFn printFn, DisassemblyFindSymbolFn findSymbolFn,
                                       DisassemblePPCFlags flags);

#ifdef __cplusplus
}
#endif
