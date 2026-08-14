// TODO: Clean this entire file up and add some comments

#include "FunctionPatcher.h"

#include <string.h>
#include <string>
#include <vector>

#include <coreinit/cache.h>
#include <coreinit/debug.h>
#include <coreinit/dynload.h>
#include <coreinit/memory.h>

struct Driver
{
    std::string driverName;
    OSDynLoad_Module driverHandle;
};

struct DriverFunction
{
    std::string driverName;
    std::string functionName;
    uint32_t effectiveFunctionAddress;
};

static std::vector<Driver> s_driverCache;
static std::vector<DriverFunction> s_driverFunctionCache;

static inline uint8_t s_executableSpace[FUNCTION_PATCHER_EXECUTABLE_SPACE_SIZE] __attribute__((aligned(0x20))) = {};
static inline size_t s_currentExecutableSpaceOffset                                                            = 0;

static uint32_t FunctionPatcher_GetRegister2()
{
    uint32_t value;
    asm volatile("mr %0, 2" : "=r"(value));
    return value;
}

static uint32_t FunctionPatcher_GetRegister13()
{
    uint32_t value;
    asm volatile("mr %0, 13" : "=r"(value));
    return value;
}

static void FunctionPatcher_WriteCode(uint32_t address, const uint32_t *code, size_t size)
{
    OSBlockMove((void *) address, code, size, TRUE);
    OSMemoryBarrier();
    DCFlushRange((void *) address, size);
    ICInvalidateRange((void *) address, size);
}

const char *FunctionPatcher_ResultToStr(FunctionPatcherResult result)
{
    switch (result)
    {
        case FUNCTION_PATCHER_RESULT_SUCCESS: {
            return "FUNCTION_PATCHER_RESULT_SUCCESS";
        }

        case FUNCTION_PATCHER_RESULT_DRIVER_HANDLE_NOT_FOUND: {
            return "FUNCTION_PATCHER_RESULT_DRIVER_HANDLE_NOT_FOUND";
        }

        case FUNCTION_PATCHER_RESULT_DRIVER_FUNCTION_NOT_FOUND: {
            return "FUNCTION_PATCHER_RESULT_DRIVER_FUNCTION_NOT_FOUND";
        }

        case FUNCTION_PATCHER_RESULT_EXECUTABLE_SPACE_FULL: {
            return "FUNCTION_PATCHER_RESULT_EXECUTABLE_SPACE_FULL";
        }

        case FUNCTION_PATCHER_RESULT_INVALID_ALIGNMENT: {
            return "FUNCTION_PATCHER_RESULT_INVALID_ALIGNMENT";
        }
    }

    return "??";
}

static FunctionPatcherResult FunctionPatcher_GetDriver(const char *driverName, Driver *outDriver)
{
    for (Driver &driver : s_driverCache)
    {
        if (driver.driverName == driverName)
        {
            *outDriver = driver;
            return FUNCTION_PATCHER_RESULT_SUCCESS;
        }
    }

    OSDynLoad_Module driverHandle = nullptr;
    OSDynLoad_Error driverError   = OSDynLoad_Acquire(driverName, &driverHandle);
    if (driverError != OS_DYNLOAD_OK || !driverHandle)
    {
        return FUNCTION_PATCHER_RESULT_DRIVER_HANDLE_NOT_FOUND;
    }

    Driver driver;
    driver.driverName   = driverName;
    driver.driverHandle = driverHandle;
    s_driverCache.push_back(driver);
    *outDriver = driver;

    return FUNCTION_PATCHER_RESULT_SUCCESS;
}

static FunctionPatcherResult FunctionPatcher_GetDriverFunction(Driver driver, const char *functionName, DriverFunction *outFunction)
{
    for (DriverFunction &function : s_driverFunctionCache)
    {
        if (function.driverName == driver.driverName && function.functionName == functionName)
        {
            *outFunction = function;
            return FUNCTION_PATCHER_RESULT_SUCCESS;
        }
    }

    uint32_t address            = 0;
    OSDynLoad_Error driverError = OSDynLoad_FindExport(driver.driverHandle, OS_DYNLOAD_EXPORT_FUNC, functionName, (void **) &address);
    if (driverError != OS_DYNLOAD_OK || address == 0)
    {
        return FUNCTION_PATCHER_RESULT_DRIVER_FUNCTION_NOT_FOUND;
    }

    uint32_t addressData = *((volatile uint32_t *) address);
    if ((addressData & 0xFC000003) == 0x48000000)
    {
        uint32_t addressDifference = addressData & 0x01FFFFFC;
        if ((addressData & 0x02000000) == 0x02000000)
        {
            addressDifference = 0xFE000000 + addressDifference;
        }

        address += addressDifference;
    }

    DriverFunction function;
    function.driverName               = driver.driverName;
    function.functionName             = functionName;
    function.effectiveFunctionAddress = address;
    s_driverFunctionCache.push_back(function);
    *outFunction = function;

    return FUNCTION_PATCHER_RESULT_SUCCESS;
}

FunctionPatcherResult FunctionPatcher_AllocateExecutableSpace(size_t size, uint32_t *outExecutableSpace)
{
    size = (size + 3) & ~3;
    if ((s_currentExecutableSpaceOffset + size) > sizeof(s_executableSpace))
    {
        return FUNCTION_PATCHER_RESULT_EXECUTABLE_SPACE_FULL;
    }

    *outExecutableSpace = (uint32_t) &s_executableSpace[s_currentExecutableSpaceOffset];
    s_currentExecutableSpaceOffset += size;

    size_t executableSpaceLeft = (sizeof(s_executableSpace) - s_currentExecutableSpaceOffset);
    if (executableSpaceLeft <= 0x100)
    {
        OSReport("Low executable space left: %d bytes left", executableSpaceLeft);
    }

    return FUNCTION_PATCHER_RESULT_SUCCESS;
}

void FunctionPatcher_ClearCaches()
{
    s_driverCache.clear();
    s_driverFunctionCache.clear();
}

FunctionPatcherResult FunctionPatcher_GetEffectiveAddressOfFunction(const char *driverName, const char *functionName, uint32_t *outAddress)
{
    Driver driver;
    FunctionPatcherResult result = FunctionPatcher_GetDriver(driverName, &driver);
    if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
    {
        return result;
    }

    DriverFunction function;
    result = FunctionPatcher_GetDriverFunction(driver, functionName, &function);
    if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
    {
        return result;
    }

    *outAddress = function.effectiveFunctionAddress;
    return FUNCTION_PATCHER_RESULT_SUCCESS;
}

FunctionPatcherResult FunctionPatcher_PatchFunction(FunctionPatchData data, uint32_t *outRealFunctionAddress)
{
    const uint32_t replaceCall = (uint32_t) data.replaceCall;
    if ((data.replaceAddress % 4) != 0 || (replaceCall % 4) != 0)
    {
        return FUNCTION_PATCHER_RESULT_INVALID_ALIGNMENT;
    }

    uint32_t originalFunctionBuffer[2];
    uint32_t originalFunctionSpace;
    FunctionPatcherResult result = FunctionPatcher_AllocateExecutableSpace(sizeof(originalFunctionBuffer), &originalFunctionSpace);
    if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
    {
        return result;
    }

    originalFunctionBuffer[0] = *(uint32_t *) data.replaceAddress;
    originalFunctionBuffer[1] = 0x48000000 | (((data.replaceAddress + 4) - (originalFunctionSpace + 4)) & 0x03FFFFFC);
    FunctionPatcher_WriteCode(originalFunctionSpace, originalFunctionBuffer, sizeof(originalFunctionBuffer));

    uint32_t savedRegisterSpace;
    result = FunctionPatcher_AllocateExecutableSpace(0x20, &savedRegisterSpace);
    if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
    {
        return result;
    }

    uint32_t savedRegisterBuffer[8]{};
    FunctionPatcher_WriteCode(savedRegisterSpace, savedRegisterBuffer, sizeof(savedRegisterBuffer));

    const uint32_t pluginRegister2  = FunctionPatcher_GetRegister2();
    const uint32_t pluginRegister13 = FunctionPatcher_GetRegister13();

    uint32_t realWrapper[] = {
            0x9421FFC0,
            0x7C0802A6,
            0x90010044,
            0x90410008,
            0x91A1000C,
            0x3D600000 | ((savedRegisterSpace >> 16) & 0xFFFF),
            0x616B0000 | (savedRegisterSpace & 0xFFFF),
            0x804B0000,
            0x81AB0004,
            0x3D800000 | ((originalFunctionSpace >> 16) & 0xFFFF),
            0x618C0000 | (originalFunctionSpace & 0xFFFF),
            0x7D8903A6,
            0x4E800421,
            0x81A1000C,
            0x80410008,
            0x80010044,
            0x7C0803A6,
            0x38210040,
            0x4E800020,
    };

    uint32_t realWrapperSpace;
    result = FunctionPatcher_AllocateExecutableSpace(sizeof(realWrapper), &realWrapperSpace);
    if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
    {
        return result;
    }

    FunctionPatcher_WriteCode(realWrapperSpace, realWrapper, sizeof(realWrapper));

    uint32_t replacementWrapper[] = {
            0x9421FFC0,
            0x7C0802A6,
            0x90010044,
            0x90410008,
            0x91A1000C,
            0x3D600000 | ((savedRegisterSpace >> 16) & 0xFFFF),
            0x616B0000 | (savedRegisterSpace & 0xFFFF),
            0x904B0000,
            0x91AB0004,
            0x3C400000 | ((pluginRegister2 >> 16) & 0xFFFF),
            0x60420000 | (pluginRegister2 & 0xFFFF),
            0x3DA00000 | ((pluginRegister13 >> 16) & 0xFFFF),
            0x61AD0000 | (pluginRegister13 & 0xFFFF),
            0x3D800000 | ((replaceCall >> 16) & 0xFFFF),
            0x618C0000 | (replaceCall & 0xFFFF),
            0x7D8903A6,
            0x4E800421,
            0x81A1000C,
            0x80410008,
            0x80010044,
            0x7C0803A6,
            0x38210040,
            0x4E800020,
    };

    uint32_t replacementWrapperSpace;
    result = FunctionPatcher_AllocateExecutableSpace(sizeof(replacementWrapper), &replacementWrapperSpace);
    if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
    {
        return result;
    }

    FunctionPatcher_WriteCode(replacementWrapperSpace, replacementWrapper, sizeof(replacementWrapper));

    int jumpLength = (int) (replacementWrapperSpace - data.replaceAddress);
    if (jumpLength > 0x01FFFFFC || jumpLength < -0x02000000)
    {
        uint32_t longJump[] = {
                0x3D800000 | ((replacementWrapperSpace >> 16) & 0xFFFF),
                0x618C0000 | (replacementWrapperSpace & 0xFFFF),
                0x7D8903A6,
                0x4E800420,
        };

        uint32_t destinationSpace;
        result = FunctionPatcher_AllocateExecutableSpace(sizeof(longJump), &destinationSpace);
        if (result != FUNCTION_PATCHER_RESULT_SUCCESS)
        {
            return result;
        }

        FunctionPatcher_WriteCode(destinationSpace, longJump, sizeof(longJump));
        jumpLength = (int) (destinationSpace - data.replaceAddress);
    }

    *(uint32_t *) data.replaceAddress = 0x48000000 | ((uint32_t) jumpLength & 0x03FFFFFC);
    OSMemoryBarrier();
    DCFlushRange((void *) data.replaceAddress, sizeof(uint32_t));
    ICInvalidateRange((void *) data.replaceAddress, sizeof(uint32_t));

    *outRealFunctionAddress = realWrapperSpace;

    return FUNCTION_PATCHER_RESULT_SUCCESS;
}
