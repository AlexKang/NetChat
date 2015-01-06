#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>

struct addrinfo *getaddr(char *addr);

void runchat(int sockfd);