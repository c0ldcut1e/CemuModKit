#include <cstdint>
#include <cstring>

#include <coreinit/title.h>

#include <fmt/format_wiiu.h>

struct STBIMem2AllocationHeader
{
    uint32_t size;
};

static void *STBIMem2Malloc(size_t size)
{
    if (size == 0)
    {
        return nullptr;
    }

    uint32_t totalSize = (uint32_t) (sizeof(STBIMem2AllocationHeader) + size);

    // Allocate memory using the game's heap (currently using Minecraft's method to allocate MEM2)
    // Renderer::MemoryAllocMEM2
    void *rawMemory = ((void *(*) (void *, uint32_t, uint32_t) ) 0x034174FC)(*(void **) 0x104CEAD8, totalSize, 0x40);
    if (!rawMemory)
    {
        fmt::wiiu_debug_println("[STBImage] STBIMem2Malloc failed size={} totalSize={}", (uint32_t) size, totalSize);
        return nullptr;
    }

    STBIMem2AllocationHeader *header = (STBIMem2AllocationHeader *) rawMemory;
    header->size                     = (uint32_t) size;

    return (void *) (header + 1);
}

static void STBIMem2Free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    STBIMem2AllocationHeader *header = ((STBIMem2AllocationHeader *) ptr) - 1;

    // Free memory from the game's heap (currently using Minecraft's method to free MEM2)
    // Renderer::MemoryFreeMEM2
    ((void (*)(void *, void *)) 0x03417520)(*(void **) 0x104CEAD8, header);
}

static void *STBIMem2Realloc(void *ptr, size_t newSize)
{
    if (!ptr)
    {
        return STBIMem2Malloc(newSize);
    }

    if (newSize == 0)
    {
        STBIMem2Free(ptr);
        return nullptr;
    }

    STBIMem2AllocationHeader *oldHeader = ((STBIMem2AllocationHeader *) ptr) - 1;
    uint32_t oldSize                    = oldHeader->size;

    void *newPtr = STBIMem2Malloc(newSize);
    if (!newPtr)
    {
        fmt::wiiu_debug_println("[STBImage] STBIMem2Realloc failed oldSize={} newSize={}", oldSize, (uint32_t) newSize);
        return nullptr;
    }

    uint32_t copySize = oldSize < (uint32_t) newSize ? oldSize : (uint32_t) newSize;
    memcpy(newPtr, ptr, copySize);

    STBIMem2Free(ptr);

    return newPtr;
}

#define STBI_MALLOC(sz)     STBIMem2Malloc(sz)
#define STBI_FREE(p)        STBIMem2Free(p)
#define STBI_REALLOC(p, sz) STBIMem2Realloc(p, sz)

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_THREAD_LOCALS
#define STBI_NO_SIMD
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STBI_NO_FAILURE_STRINGS
#include "stb_image.h"
