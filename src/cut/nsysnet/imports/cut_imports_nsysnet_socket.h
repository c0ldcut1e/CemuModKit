#pragma once

#include "../_socket.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsNSysNetSocket
{
    void (*socket_lib_init)(void);
    void (*socket_lib_finish)(void);
    int (*accept)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int (*bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int (*socketclose)(int sockfd);
    int (*connect)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int (*getpeername)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int (*getsockname)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int (*getsockopt)(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
    int (*listen)(int sockfd, int backlog);
    int (*recv)(int sockfd, void *buf, size_t len, int flags);
    int (*recvfrom)(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    int (*send)(int sockfd, const void *buf, size_t len, int flags);
    int (*sendto)(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
    int (*setsockopt)(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    int (*shutdown)(int sockfd, int how);
    int (*socket)(int domain, int type, int protocol);
    int (*select)(int nfds, nsysnet_fd_set *readfds, nsysnet_fd_set *writefds, nsysnet_fd_set *exceptfds, struct nsysnet_timeval *timeout);
    const char *(*inet_ntop)(int af, const void *src, char *dst, socklen_t size);
    int (*inet_pton)(int af, const char *src, void *dst);
    int (*socketlasterr)(void);
} ImportsNSysNetSocket;

#ifdef __cplusplus
}
#endif
