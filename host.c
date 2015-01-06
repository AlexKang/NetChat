#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "chat.h"

#define BACKLOG 1

int main(int argc, char *argv[]) {
    struct addrinfo *res;
    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    int bind_status, listen_status, sockfd, clientfd, yes = 1;

    res = getaddr(NULL);

    // Create socket for our host connection
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // Allow host to reuse port if already in use
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    // Bind socket
    bind_status = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind_status == -1) {
        printf("ERROR: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("Successfully binded\n");
    }

    freeaddrinfo(res); // res no longer needed

    // Listen for clients
    listen_status = listen(sockfd, BACKLOG);
    if (listen_status == -1) {
        printf("ERROR: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("Listening for incoming connections...\n");
    }

    // Accept connections (use an array if more than 1 connection needed)
    addr_size = sizeof client_addr;
    clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_size);

    printf("New user connected\n");

    runchat(clientfd);

    return 0;
}
