#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSThread OSThread;

typedef struct OSThreadLink OSThreadLink;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSThreadSimpleQueue OSThreadSimpleQueue;

struct OSThreadLink
{
    OSThread *next;
    OSThread *prev;
};
CUT_CHECK_OFFSET(OSThreadLink, 0x00, next);
CUT_CHECK_OFFSET(OSThreadLink, 0x04, prev);
CUT_CHECK_SIZE(OSThreadLink, 0x8);

struct OSThreadQueue
{
    OSThread *head;
    OSThread *tail;
    void *parent;
    CUT_UNKNOWN_BYTES(4);
};
CUT_CHECK_OFFSET(OSThreadQueue, 0x00, head);
CUT_CHECK_OFFSET(OSThreadQueue, 0x04, tail);
CUT_CHECK_OFFSET(OSThreadQueue, 0x08, parent);
CUT_CHECK_SIZE(OSThreadQueue, 0x10);

struct OSThreadSimpleQueue
{
    OSThread *head;
    OSThread *tail;
};
CUT_CHECK_OFFSET(OSThreadSimpleQueue, 0x00, head);
CUT_CHECK_OFFSET(OSThreadSimpleQueue, 0x04, tail);
CUT_CHECK_SIZE(OSThreadSimpleQueue, 0x08);

#ifdef __cplusplus
}
#endif
