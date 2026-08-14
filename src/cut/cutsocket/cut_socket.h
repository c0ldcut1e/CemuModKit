#pragma once

#include <fcntl.h>
#include <poll.h>
#include <stdarg.h>
#include <string.h>
#include <sys/iosupport.h>
#include <sys/select.h>

#define __LINUX_ERRNO_EXTENSIONS__
#include <errno.h>

#include "../nsysnet/_netdb.h"
#include "../nsysnet/_socket.h"

#undef RPLWRAP
#define RPLWRAP(func) cut_##func

#ifdef __cplusplus
extern "C" {
#endif

int __cut_get_nsysnet_fd(int fd);
int __cut_get_nsysnet_result(struct _reent *r, int rc);

void __init_cut_socket(void);
void __fini_cut_socket(void);

int __cut_socket_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode);
int __cut_socket_close(struct _reent *r, void *fd);
ssize_t __cut_socket_write(struct _reent *r, void *fd, const char *ptr, size_t len);
ssize_t __cut_socket_read(struct _reent *r, void *fd, char *ptr, size_t len);

#ifdef __cplusplus
}
#endif
