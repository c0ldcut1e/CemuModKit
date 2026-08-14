#pragma once

#include "cut_imports_nsysnet_netdb.h"
#include "cut_imports_nsysnet_socket.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsNSysNet
{
    ImportsNSysNetNetDb netDb;
    ImportsNSysNetSocket socket;
} ImportsNSysNet;

#ifdef __cplusplus
}
#endif
