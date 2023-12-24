#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 19132

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Failed to create a socket");
        exit(EXIT_FAILURE);
    }

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "ERROR: Could not resolve hostname!\n");
        exit(EXIT_FAILURE);
    }
  
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    portno = PORT;
    serv_addr.sin_port = htons(portno);

    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("Failed to connect to the server");
        exit(EXIT_FAILURE);
    }

    sprintf(buffer, "status %s%s%s", "%34s", "<ldap://localhost:1098/>", "your minecraft account is connected");

    send(sockfd, buffer, strlen(buffer), 0);

    close(sockfd);
}
