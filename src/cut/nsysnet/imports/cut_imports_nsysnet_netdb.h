#pragma once

#include "../_netdb.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsNSysNetNetDb
{
    struct hostent *(*gethostbyaddr)(const void *addr, size_t len, int type);
    struct hostent *(*gethostbyname)(const char *name);
    int (*getaddrinfo)(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
    void (*freeaddrinfo)(struct addrinfo *res);
    int (*getnameinfo)(const struct sockaddr *addr, socklen_t addrlen, char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags);
    const char *(*gai_strerror)(int ecode);
    int *(*get_h_errno)(void);
} ImportsNSysNetNetDb;

#ifdef __cplusplus
}
#endif
