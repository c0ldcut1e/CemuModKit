#include "cut_socket.h"

int listen(int sockfd, int backlog)
{
    int rc;
    sockfd = __cut_get_nsysnet_fd(sockfd);
    if (sockfd == -1)
    {
        return -1;
    }
    rc = RPLWRAP(listen)(sockfd, backlog);
    return __cut_get_nsysnet_result(NULL, rc);
}
