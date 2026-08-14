#include "cut_socket.h"

int sockatmark(int sockfd)
{
    char buf[1];
    int rc;

    sockfd = __cut_get_nsysnet_fd(sockfd);

    rc = RPLWRAP(recv)(sockfd, buf, sizeof(buf), MSG_OOB | MSG_PEEK | MSG_DONTWAIT);
    if (rc > 0)
    {
        return 1;
    }

    rc = __cut_get_nsysnet_result(NULL, rc);

    return (errno == EWOULDBLOCK) ? 0 : rc;
}
