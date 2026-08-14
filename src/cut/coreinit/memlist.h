#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMMemoryLink MEMMemoryLink;
typedef struct MEMMemoryList MEMMemoryList;

struct MEMMemoryLink
{
    void *prev;
    void *next;
};
CUT_CHECK_OFFSET(MEMMemoryLink, 0x0, prev);
CUT_CHECK_OFFSET(MEMMemoryLink, 0x4, next);
CUT_CHECK_SIZE(MEMMemoryLink, 0x8);

struct MEMMemoryList
{
    void *head;
    void *tail;
    uint16_t count;
    uint16_t offsetToMemoryLink;
};
CUT_CHECK_OFFSET(MEMMemoryList, 0x0, head);
CUT_CHECK_OFFSET(MEMMemoryList, 0x4, tail);
CUT_CHECK_OFFSET(MEMMemoryList, 0x8, count);
CUT_CHECK_OFFSET(MEMMemoryList, 0xa, offsetToMemoryLink);
CUT_CHECK_SIZE(MEMMemoryList, 0xc);

CUT_IMPORT void *(*MEMGetNextListObject)(MEMMemoryList *list, void *object);

#ifdef __cplusplus
}
#endif
