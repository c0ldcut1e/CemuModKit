#pragma once

#include "../cut.h"
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSMessage OSMessage;
typedef struct OSMessageQueue OSMessageQueue;

typedef enum OSMessageFlags
{
    OS_MESSAGE_FLAGS_NONE          = 0,
    OS_MESSAGE_FLAGS_BLOCKING      = 1 << 0,
    OS_MESSAGE_FLAGS_HIGH_PRIORITY = 1 << 1,
} OSMessageFlags;

typedef enum OSFunctionType
{
    OS_FUNCTION_TYPE_HIO_OPEN                  = 1,
    OS_FUNCTION_TYPE_HIO_READ_ASYNC            = 2,
    OS_FUNCTION_TYPE_HIO_WRITE_ASYNC           = 3,
    OS_FUNCTION_TYPE_FSA_CMD_ASYNC             = 4,
    OS_FUNCTION_TYPE_FSA_PR_CMD_ASYNC          = 5,
    OS_FUNCTION_TYPE_FSA_PR_CMD_ASYNC_NO_ALLOC = 6,
    OS_FUNCTION_TYPE_FSA_ATTACH_EVENT          = 7,
    OS_FUNCTION_TYPE_FS_CMD_ASYNC              = 8,
    OS_FUNCTION_TYPE_FS_CMD_HANDLER            = 9,
    OS_FUNCTION_TYPE_FS_ATTACH_EVENT           = 10,
    OS_FUNCTION_TYPE_FS_STATE_CHANGE_EVENT     = 11,
} OSFunctionType;

struct OSMessage
{
    void *message;
    uint32_t args[3];
};
CUT_CHECK_OFFSET(OSMessage, 0x00, message);
CUT_CHECK_OFFSET(OSMessage, 0x04, args);
CUT_CHECK_SIZE(OSMessage, 0x10);

#define OS_MESSAGE_QUEUE_TAG 0x6D536751u

struct OSMessageQueue
{
    uint32_t tag;
    const char *name;
    CUT_UNKNOWN_BYTES(4);
    OSThreadQueue sendQueue;
    OSThreadQueue recvQueue;
    OSMessage *messages;
    uint32_t size;
    uint32_t first;
    uint32_t used;
};
CUT_CHECK_OFFSET(OSMessageQueue, 0x00, tag);
CUT_CHECK_OFFSET(OSMessageQueue, 0x04, name);
CUT_CHECK_OFFSET(OSMessageQueue, 0x0c, sendQueue);
CUT_CHECK_OFFSET(OSMessageQueue, 0x1c, recvQueue);
CUT_CHECK_OFFSET(OSMessageQueue, 0x2c, messages);
CUT_CHECK_OFFSET(OSMessageQueue, 0x30, size);
CUT_CHECK_OFFSET(OSMessageQueue, 0x34, first);
CUT_CHECK_OFFSET(OSMessageQueue, 0x38, used);
CUT_CHECK_SIZE(OSMessageQueue, 0x3c);

CUT_IMPORT void (*OSInitMessageQueue)(OSMessageQueue *queue, OSMessage *messages, int size);

CUT_IMPORT void (*OSInitMessageQueueEx)(OSMessageQueue *queue, OSMessage *messages, int size, const char *name);

CUT_IMPORT BOOL (*OSSendMessage)(OSMessageQueue *queue, OSMessage *message, OSMessageFlags flags);

CUT_IMPORT BOOL (*OSReceiveMessage)(OSMessageQueue *queue, OSMessage *message, OSMessageFlags flags);

CUT_IMPORT BOOL (*OSPeekMessage)(OSMessageQueue *queue, OSMessage *message);

CUT_IMPORT OSMessageQueue *(*OSGetSystemMessageQueue)();

#ifdef __cplusplus
}
#endif
