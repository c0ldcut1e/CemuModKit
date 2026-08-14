#include "cut_socket.h"

int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
    int rc;
    sockfd = __cut_get_nsysnet_fd(sockfd);
    if (sockfd == -1)
    {
        return -1;
    }
    rc = RPLWRAP(getsockopt)(sockfd, level, optname, optval, optlen);
    return __cut_get_nsysnet_result(NULL, rc);
}
