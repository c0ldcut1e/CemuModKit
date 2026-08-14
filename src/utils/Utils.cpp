#include "Utils.h"

#include <coreinit/cache.h>
#include <coreinit/memory.h>

void WriteU32(uint32_t address, uint32_t value)
{
    *(uint32_t *) address = value;
    DCFlushRange((void *) address, sizeof(uint32_t));
    ICInvalidateRange((void *) address, sizeof(uint32_t));
}

void WriteU32Arr(uint32_t address, const uint32_t *values, size_t size)
{
    OSBlockMove((void *) address, values, size, TRUE);
    DCFlushRange((void *) address, size);
    ICInvalidateRange((void *) address, size);
}
