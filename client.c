#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "chat.h"

int main(int argc, char *argv[]) {
    struct addrinfo *res;
    int status, sockfd;

    if (argc < 2) {
        printf("ERROR: Missing argument\n");
        return 1;
    }

    res = getaddr(argv[1]);

    // Create socket for our host connection
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // Connect to the host
    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        printf("ERROR: %s\n", strerror(errno));
        return 3;
    } else {
        printf("Connected\n");
    }

    runchat(sockfd);

    return 0;
}
