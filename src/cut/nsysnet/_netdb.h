#pragma once

#include <netdb.h>

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

CUT_IMPORT struct hostent *(*cut_gethostbyaddr)(const void *addr, size_t len, int type);

CUT_IMPORT struct hostent *(*cut_gethostbyname)(const char *name);

CUT_IMPORT int (*cut_getaddrinfo)(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);

CUT_IMPORT void (*cut_freeaddrinfo)(struct addrinfo *res);

CUT_IMPORT int (*cut_getnameinfo)(const struct sockaddr *addr, socklen_t addrlen, char *host, socklen_t hostlen, char *serv, socklen_t servlen,
                                  int flags);

CUT_IMPORT const char *(*cut_gai_strerror)(int ecode);

CUT_IMPORT int *(*cut_get_h_errno)(void);

#ifdef __cplusplus
}
#endif
