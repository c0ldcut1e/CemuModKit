#include "gfd.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static char sLastError[1024] = {0};

static void __attribute__((format(printf, 1, 2))) GFDSetLastError(const char *fmt, ...)
{
    va_list va;

    va_start(va, fmt);
    vsnprintf(sLastError, sizeof(sLastError), fmt, va);
    va_end(va);
}

char *GFDGetLastErrorString(void) { return sLastError; }

static uint32_t GFDCleanTag(uint32_t tag) { return tag & ~GFD_PATCH_MASK; }

static BOOL GFDCheckTagDAT(uint32_t tag) { return (tag & GFD_PATCH_MASK) == GFD_PATCH_DATA; }

static BOOL GFDCheckTagSTR(uint32_t tag) { return (tag & GFD_PATCH_MASK) == GFD_PATCH_TEXT; }

static BOOL GFDCheckHeaderVersions(const void *file)
{
    const GFDHeader *header = (const GFDHeader *) file;

    if (!header)
    {
        GFDSetLastError("%s: file == NULL", __FUNCTION__);
        return FALSE;
    }

    if (header->magic != GFD_HEADER_MAGIC)
    {
        GFDSetLastError("%s: header->magic %08X != %08X", __FUNCTION__, header->magic, GFD_HEADER_MAGIC);
        return FALSE;
    }

    if (header->majorVersion != GFD_FILE_VERSION_MAJOR || header->minorVersion != GFD_FILE_VERSION_MINOR)
    {
        GFDSetLastError("%s: version %u.%u != %u.%u", __FUNCTION__, header->majorVersion, header->minorVersion, GFD_FILE_VERSION_MAJOR,
                        GFD_FILE_VERSION_MINOR);
        return FALSE;
    }

    return TRUE;
}

static BOOL GFDCheckBlockHeader(const GFDBlockHeader *header)
{
    if (header->magic != GFD_BLOCK_HEADER_MAGIC)
    {
        GFDSetLastError("%s: block magic %08X != %08X", __FUNCTION__, header->magic, GFD_BLOCK_HEADER_MAGIC);
        return FALSE;
    }

    if (header->majorVersion != GFD_BLOCK_VERSION_MAJOR)
    {
        GFDSetLastError("%s: block major version %u != %u", __FUNCTION__, header->majorVersion, GFD_BLOCK_VERSION_MAJOR);
        return FALSE;
    }

    return TRUE;
}

static const GFDBlockHeader *GFDGetFirstBlock(const void *file)
{
    const GFDHeader *fileHeader = (const GFDHeader *) file;
    return (const GFDBlockHeader *) ((const uint8_t *) file + fileHeader->headerSize);
}

static const GFDBlockHeader *GFDGetNextBlock(const GFDBlockHeader *blockHeader)
{
    return (const GFDBlockHeader *) ((const uint8_t *) blockHeader + blockHeader->headerSize + blockHeader->dataSize);
}

static const void *GFDGetBlockData(const GFDBlockHeader *blockHeader) { return (const uint8_t *) blockHeader + blockHeader->headerSize; }

static BOOL GFDGetBlockPointer(GFDBlockType type, uint32_t index, const void *file, const GFDBlockHeader **blockHeaderOut, const void **blockDataOut)
{
    const GFDBlockHeader *blockHeader;
    uint32_t count = 0;

    if (!GFDCheckHeaderVersions(file))
    {
        return FALSE;
    }

    blockHeader = GFDGetFirstBlock(file);
    while (GFDCheckBlockHeader(blockHeader))
    {
        if (blockHeader->type == type)
        {
            if (count == index)
            {
                *blockHeaderOut = blockHeader;
                *blockDataOut   = GFDGetBlockData(blockHeader);
                return TRUE;
            }
            count++;
        }
        else if (blockHeader->type == GFD_BLOCK_END_OF_FILE)
        {
            break;
        }

        blockHeader = GFDGetNextBlock(blockHeader);
    }

    return FALSE;
}

static uint32_t GFDGetBlockCount(GFDBlockType type, const void *file)
{
    const GFDBlockHeader *blockHeader;
    uint32_t count = 0;

    if (!GFDCheckHeaderVersions(file))
    {
        return 0;
    }

    blockHeader = GFDGetFirstBlock(file);
    while (GFDCheckBlockHeader(blockHeader))
    {
        if (blockHeader->type == type)
        {
            count++;
        }
        else if (blockHeader->type == GFD_BLOCK_END_OF_FILE)
        {
            break;
        }

        blockHeader = GFDGetNextBlock(blockHeader);
    }

    return count;
}

static uint32_t GFDGetBlockDataSize(GFDBlockType type, uint32_t index, const void *file)
{
    const GFDBlockHeader *blockHeader;
    const void *blockData;

    if (!GFDGetBlockPointer(type, index, file, &blockHeader, &blockData))
    {
        return 0;
    }

    return blockHeader->dataSize;
}

static BOOL GFDRelocateBlockEx(const GFDRelocationHeader *relocationHeader, const uint32_t *patchTable, uint8_t *dst)
{
    for (uint32_t i = 0; i < relocationHeader->patchCount; ++i)
    {
        uint32_t offset = patchTable[i];
        uint32_t *target;

        if (offset == 0)
        {
            continue;
        }

        if (!GFDCheckTagDAT(offset) && !GFDCheckTagSTR(offset))
        {
            GFDSetLastError("%s: bad patch offset %08X", __FUNCTION__, offset);
            return FALSE;
        }

        target = (uint32_t *) (dst + GFDCleanTag(offset));
        if (!GFDCheckTagDAT(*target) && !GFDCheckTagSTR(*target))
        {
            GFDSetLastError("%s: bad patch target %08X", __FUNCTION__, *target);
            return FALSE;
        }

        *target = (uintptr_t) (dst + GFDCleanTag(*target));
    }

    return TRUE;
}

static BOOL GFDRelocateBlock(const GFDBlockHeader *blockHeader, void *dst)
{
    const uint8_t *blockData;
    const GFDRelocationHeader *relocationHeader;
    const uint32_t *patchTable;

    if (!blockHeader || !dst)
    {
        return FALSE;
    }

    blockData        = (const uint8_t *) GFDGetBlockData(blockHeader);
    relocationHeader = (const GFDRelocationHeader *) (blockData + blockHeader->dataSize - sizeof(GFDRelocationHeader));

    if (relocationHeader->magic != GFD_RELOCATION_HEADER_MAGIC)
    {
        GFDSetLastError("%s: relocation magic %08X != %08X", __FUNCTION__, relocationHeader->magic, GFD_RELOCATION_HEADER_MAGIC);
        return FALSE;
    }

    if (!GFDCheckTagDAT(relocationHeader->patchOffset))
    {
        GFDSetLastError("%s: bad patch table offset %08X", __FUNCTION__, relocationHeader->patchOffset);
        return FALSE;
    }

    patchTable = (const uint32_t *) (blockData + GFDCleanTag(relocationHeader->patchOffset));
    return GFDRelocateBlockEx(relocationHeader, patchTable, (uint8_t *) dst);
}

static BOOL GFDCheckShaderAlign(void *program) { return (((uintptr_t) program) & (GX2_SHADER_PROGRAM_ALIGNMENT - 1)) == 0; }

static BOOL GFDGetGenericBlock(GFDBlockType headerType, void *header, GFDBlockType programType1, void **outProgramPtr1, void *program1,
                               GFDBlockType programType2, void **outProgramPtr2, void *program2, uint32_t index, const void *file)
{
    const GFDBlockHeader *blockHeader;
    uint32_t headerCount   = 0;
    uint32_t program1Count = 0;
    uint32_t program2Count = 0;

    if (!header || !file)
    {
        return FALSE;
    }

    if (!GFDCheckHeaderVersions(file))
    {
        return FALSE;
    }

    blockHeader = GFDGetFirstBlock(file);
    while (GFDCheckBlockHeader(blockHeader))
    {
        const void *blockData = GFDGetBlockData(blockHeader);

        if (blockHeader->type == headerType)
        {
            if (headerCount == index)
            {
                memcpy(header, blockData, blockHeader->dataSize);
                if (headerType != GFD_BLOCK_TEXTURE_HEADER && !GFDRelocateBlock(blockHeader, header))
                {
                    return FALSE;
                }
            }
            headerCount++;
        }
        else if (blockHeader->type == programType1)
        {
            if (program1Count == index)
            {
                *outProgramPtr1 = program1;
                memcpy(program1, blockData, blockHeader->dataSize);
            }
            program1Count++;
        }
        else if (program2 && blockHeader->type == programType2)
        {
            if (program2Count == index)
            {
                *outProgramPtr2 = program2;
                memcpy(program2, blockData, blockHeader->dataSize);
            }
            program2Count++;
        }
        else if (blockHeader->type == GFD_BLOCK_END_OF_FILE)
        {
            break;
        }

        if (headerCount > index && program1Count > index && (!program2 || program2Count > index))
        {
            return TRUE;
        }

        blockHeader = GFDGetNextBlock(blockHeader);
    }

    return FALSE;
}

uint32_t GFDGetGeometryShaderCount(const void *file) { return GFDGetBlockCount(GFD_BLOCK_GEOMETRY_SHADER_HEADER, file); }

uint32_t GFDGetGeometryShaderHeaderSize(uint32_t index, const void *file)
{
    return GFDGetBlockDataSize(GFD_BLOCK_GEOMETRY_SHADER_HEADER, index, file);
}

uint32_t GFDGetGeometryShaderProgramSize(uint32_t index, const void *file)
{
    return GFDGetBlockDataSize(GFD_BLOCK_GEOMETRY_SHADER_PROGRAM, index, file);
}

uint32_t GFDGetGeometryShaderCopyProgramSize(uint32_t index, const void *file)
{
    return GFDGetBlockDataSize(GFD_BLOCK_GEOMETRY_SHADER_COPY_PROGRAM, index, file);
}

BOOL GFDGetGeometryShader(GX2GeometryShader *shader, void *program, void *copyProgram, uint32_t index, const void *file)
{
    if (!GFDCheckShaderAlign(program) || !GFDCheckShaderAlign(copyProgram))
    {
        return FALSE;
    }

    return GFDGetGenericBlock(GFD_BLOCK_GEOMETRY_SHADER_HEADER, shader, GFD_BLOCK_GEOMETRY_SHADER_PROGRAM, &shader->program, program,
                              GFD_BLOCK_GEOMETRY_SHADER_COPY_PROGRAM, &shader->vertexProgram, copyProgram, index, file);
}

uint32_t GFDGetPixelShaderCount(const void *file) { return GFDGetBlockCount(GFD_BLOCK_PIXEL_SHADER_HEADER, file); }

uint32_t GFDGetPixelShaderHeaderSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_PIXEL_SHADER_HEADER, index, file); }

uint32_t GFDGetPixelShaderProgramSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_PIXEL_SHADER_PROGRAM, index, file); }

BOOL GFDGetPixelShader(GX2PixelShader *shader, void *program, uint32_t index, const void *file)
{
    if (!GFDCheckShaderAlign(program))
    {
        return FALSE;
    }

    return GFDGetGenericBlock(GFD_BLOCK_PIXEL_SHADER_HEADER, shader, GFD_BLOCK_PIXEL_SHADER_PROGRAM, &shader->program, program, 0, NULL, NULL, index,
                              file);
}

uint32_t GFDGetVertexShaderCount(const void *file) { return GFDGetBlockCount(GFD_BLOCK_VERTEX_SHADER_HEADER, file); }

uint32_t GFDGetVertexShaderHeaderSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_VERTEX_SHADER_HEADER, index, file); }

uint32_t GFDGetVertexShaderProgramSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_VERTEX_SHADER_PROGRAM, index, file); }

BOOL GFDGetVertexShader(GX2VertexShader *shader, void *program, uint32_t index, const void *file)
{
    if (!GFDCheckShaderAlign(program))
    {
        return FALSE;
    }

    return GFDGetGenericBlock(GFD_BLOCK_VERTEX_SHADER_HEADER, shader, GFD_BLOCK_VERTEX_SHADER_PROGRAM, &shader->program, program, 0, NULL, NULL,
                              index, file);
}

uint32_t GFDGetTextureCount(const void *file) { return GFDGetBlockCount(GFD_BLOCK_TEXTURE_HEADER, file); }

uint32_t GFDGetTextureHeaderSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_TEXTURE_HEADER, index, file); }

uint32_t GFDGetTextureImageSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_TEXTURE_IMAGE, index, file); }

uint32_t GFDGetTextureMipImageSize(uint32_t index, const void *file) { return GFDGetBlockDataSize(GFD_BLOCK_TEXTURE_MIPMAP, index, file); }

uint32_t GFDGetTextureAlignmentSize(uint32_t index, const void *file)
{
    const GFDBlockHeader *blockHeader;
    const GX2Texture *texture;

    if (!GFDGetBlockPointer(GFD_BLOCK_TEXTURE_HEADER, index, file, &blockHeader, (const void **) &texture))
    {
        return 0;
    }

    return texture->surface.alignment;
}

BOOL GFDGetTexture(GX2Texture *texture, void *image, void *mipmap, uint32_t index, const void *file)
{
    return GFDGetGenericBlock(GFD_BLOCK_TEXTURE_HEADER, texture, GFD_BLOCK_TEXTURE_IMAGE, &texture->surface.image, image, GFD_BLOCK_TEXTURE_MIPMAP,
                              &texture->surface.mipmaps, mipmap, index, file);
}

const GX2Texture *GFDGetTexturePointer(uint32_t index, const void *file)
{
    const GFDBlockHeader *blockHeader;
    const GX2Texture *texture;

    if (!GFDGetBlockPointer(GFD_BLOCK_TEXTURE_HEADER, index, file, &blockHeader, (const void **) &texture))
    {
        return NULL;
    }

    if (blockHeader->dataSize < sizeof(GX2Texture))
    {
        return NULL;
    }

    return texture;
}
