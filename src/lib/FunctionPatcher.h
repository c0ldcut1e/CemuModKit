#pragma once

#include <cstddef>
#include <cstdint>

// Might be overkill
#define FUNCTION_PATCHER_EXECUTABLE_SPACE_SIZE 0x20000

enum FunctionPatcherResult
{
    FUNCTION_PATCHER_RESULT_SUCCESS                   = 0x00000000,
    FUNCTION_PATCHER_RESULT_DRIVER_HANDLE_NOT_FOUND   = -0x00000001,
    FUNCTION_PATCHER_RESULT_DRIVER_FUNCTION_NOT_FOUND = -0x00000002,
    FUNCTION_PATCHER_RESULT_EXECUTABLE_SPACE_FULL     = -0x00000100,
    FUNCTION_PATCHER_RESULT_INVALID_ALIGNMENT         = -0x000000200,
};

struct FunctionPatchData
{
    uint32_t replaceAddress;
    uint32_t *replaceCall;
};

const char *FunctionPatcher_ResultToStr(FunctionPatcherResult result);

FunctionPatcherResult FunctionPatcher_AllocateExecutableSpace(size_t size, uint32_t *outExecutableSpace);

void FunctionPatcher_ClearCaches();

FunctionPatcherResult FunctionPatcher_GetEffectiveAddressOfFunction(const char *driverName, const char *functionName, uint32_t *outAddress);

FunctionPatcherResult FunctionPatcher_PatchFunction(FunctionPatchData data, uint32_t *outRealFunctionAddress);

#define DECL_FUNCTION(type, function_name, ...)                                                                                                      \
    type (*real_##function_name)(__VA_ARGS__);                                                                                                       \
    type my_##function_name(__VA_ARGS__)

#define REPLACE_FUNCTION(replacement_function_name, driver_name, function)                                                                           \
    (                                                                                                                                                \
            [&]() -> FunctionPatcherResult                                                                                                           \
            {                                                                                                                                        \
                uint32_t address;                                                                                                                    \
                FunctionPatcherResult result = FunctionPatcher_GetEffectiveAddressOfFunction(#driver_name, #replacement_function_name, &address);    \
                if (result != FUNCTION_PATCHER_RESULT_SUCCESS)                                                                                       \
                {                                                                                                                                    \
                    return result;                                                                                                                   \
                }                                                                                                                                    \
                                                                                                                                                     \
                return FunctionPatcher_PatchFunction({address, (uint32_t *) &my_##function}, (uint32_t *) &real_##function);                         \
            }())

#define REPLACE_FUNCTION_VIA_ADDRESS(replacement_function_address, function)                                                                         \
    FunctionPatcher_PatchFunction({replacement_function_address, (uint32_t *) &my_##function}, (uint32_t *) &real_##function);
