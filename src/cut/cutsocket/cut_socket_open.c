#include "cut_socket.h"

int __cut_socket_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode)
{
    (void) fileStruct;
    (void) path;
    (void) flags;
    (void) mode;
    r->_errno = ENOSYS;
    return -1;
}
