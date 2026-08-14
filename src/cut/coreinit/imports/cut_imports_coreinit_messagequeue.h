#pragma once

#include "../messagequeue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsCoreInitMessagequeue
{
    void (*OSInitMessageQueue)(OSMessageQueue *queue, OSMessage *messages, int size);
    void (*OSInitMessageQueueEx)(OSMessageQueue *queue, OSMessage *messages, int size, const char *name);
    BOOL (*OSSendMessage)(OSMessageQueue *queue, OSMessage *message, OSMessageFlags flags);
    BOOL (*OSReceiveMessage)(OSMessageQueue *queue, OSMessage *message, OSMessageFlags flags);
    BOOL (*OSPeekMessage)(OSMessageQueue *queue, OSMessage *message);
    OSMessageQueue *(*OSGetSystemMessageQueue)(void);
} ImportsCoreInitMessagequeue;

#ifdef __cplusplus
}
#endif
