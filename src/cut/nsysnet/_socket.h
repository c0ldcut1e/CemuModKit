#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * fd_set for select()
 */
#define NSYSNET_FD_SETSIZE     32

#define NSYSNET_FD_SET(n, p)   ((p)->fds_bits |= (1L << (n)))
#define NSYSNET_FD_CLR(n, p)   ((p)->fds_bits &= ~(1L << (n)))
#define NSYSNET_FD_ISSET(n, p) ((p)->fds_bits & (1L << (n)))
#define NSYSNET_FD_ZERO(p)     ((p)->fds_bits = 0L)

typedef uint32_t nsysnet_fd_mask;
typedef struct nsysnet_fd_set nsysnet_fd_set;

struct nsysnet_fd_set
{
    nsysnet_fd_mask fds_bits;
};

struct nsysnet_timeval
{
    long tv_sec;
    long tv_usec;
};

CUT_IMPORT void (*socket_lib_init)();

CUT_IMPORT void (*socket_lib_finish)();

CUT_IMPORT int (*cut_accept)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

CUT_IMPORT int (*cut_bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

CUT_IMPORT int (*cut_socketclose)(int sockfd);

CUT_IMPORT int (*cut_connect)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

CUT_IMPORT int (*cut_getpeername)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

CUT_IMPORT int (*cut_getsockname)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

CUT_IMPORT int (*cut_getsockopt)(int sockfd, int level, int optname, void *optval, socklen_t *optlen);

CUT_IMPORT int (*cut_listen)(int sockfd, int backlog);

CUT_IMPORT int (*cut_recv)(int sockfd, void *buf, size_t len, int flags);

CUT_IMPORT int (*cut_recvfrom)(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

CUT_IMPORT int (*cut_send)(int sockfd, const void *buf, size_t len, int flags);

CUT_IMPORT int (*cut_sendto)(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

CUT_IMPORT int (*cut_setsockopt)(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

CUT_IMPORT int (*cut_shutdown)(int sockfd, int how);

CUT_IMPORT int (*cut_socket)(int domain, int type, int protocol);

CUT_IMPORT int (*cut_select)(int nfds, nsysnet_fd_set *readfds, nsysnet_fd_set *writefds, nsysnet_fd_set *exceptfds, struct nsysnet_timeval *timeout);

CUT_IMPORT const char *(*cut_inet_ntop)(int af, const void *src, char *dst, socklen_t size);

CUT_IMPORT int (*cut_inet_pton)(int af, const char *src, void *dst);

CUT_IMPORT int (*cut_socketlasterr)();

#ifdef __cplusplus
}
#endif
