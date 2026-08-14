#pragma once

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#include <utils/CThread.h>

#define DRC_WIDTH           854
#define DRC_HEIGHT          480
#define TV_WIDTH            1280
#define TV_HEIGHT           720

#define SD_CARD_PATH        "fs:/vol/external01"

#define DEPRECATED(msg)     __attribute__((deprecated(msg)))

#define UNUSED_PARAMETER(x) (void) (x)

// Cannot write to cached addresses due to a bug in Cemu with ICInvalidateRange
void WriteU32(uint32_t address, uint32_t value);

// Cannot write to cached addresses due to a bug in Cemu with ICInvalidateRange
void WriteU32Arr(uint32_t address, const uint32_t *values, size_t size);
