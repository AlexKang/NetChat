#include "chat.h"

#define PORT "3490"
#define MESSAGE_LEN 256

struct addrinfo *getaddr(char *addr) {
    struct addrinfo hints, *res;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // Don't care if IPv4 or IPv6 
    hints.ai_socktype = SOCK_STREAM; // TCP connection

    if (addr == NULL) {
        hints.ai_flags = AI_PASSIVE; // Fill in host IP for us
    }

    status = getaddrinfo(addr, PORT, &hints, &res);
    if (status != 0) {
       printf("ERROR: %s\n", gai_strerror(status));
       exit(1);
    } else {
        printf("Found address info\n");
    }

    return res;
}

void runchat(int sockfd) {
    pid_t childPID = fork(); // Start a separate process to receive messages
    
    if (childPID >= 0) {
        if (childPID == 0) { // Child process
            char buff[MESSAGE_LEN + 1]; // Account for null char

            while (1) {
                if (recv(sockfd, buff, MESSAGE_LEN, 0) == 0) { // Check if socket connection has ended
                    printf("\rConnection closed | Press RETURN to exit\n");
                    close(sockfd);
                    _exit(0);
                } 

                printf("\rStranger: %s", buff); // fgets() already include the '\n' from pressing return
            }
        } else { // Parent process
            char message[MESSAGE_LEN + 1];

            while (1) {
                if (waitpid(0, NULL, WNOHANG) != 0) { // Check if child process has died
                    exit(0);
                }

                printf("You: ");
                fgets((char * __restrict__) message, MESSAGE_LEN, stdin);
                send(sockfd, message, MESSAGE_LEN, 0);
            }
        }
    } else {
        printf("ERROR: Forking failed");
        exit(1);
    }
}