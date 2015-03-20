#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>      // for fprintf
#include <string.h>     // for memcpy
#include <netdb.h>
#include <arpa/inet.h>
#include "port.h"

#define BUFLEN 2048
#define NUM_MSGS 5


int main(int argc, char **argv) {
    struct sockaddr_in myaddr, remaddr;
    int fd, i, slen = sizeof(remaddr);
    char *server = "127.0.0.1";
    char buf[BUFLEN];  // message buffer
    int recvlen;       // number of bytes in acknowledgement message

    // Create a UDP/IP socket
    // Request the IP protocol and a datagram interface = UDP
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket");
        return 0;
    }

    printf("created a socket: descriptor = %d\n", fd);

    // Bind myaddr to all local addresses and pick any port number
    memset((char *) &myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(0);

    if (bind(fd, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0) {
        perror("bind failed");
        return 0;
    }

    // Now define remaddr, the address to whom we want to send messages.
    // For convenience, the host address is expressed as a numeric IP address
    // that we will convert to a binary format via inet_aton.
    memset((char *) &remaddr, 0, slen);
    // Specify the IP address family, IP address, and port
    remaddr.sin_family = AF_INET;
    remaddr.sin_port = htons(SERVICE_PORT);
    if (inet_aton(server, &remaddr.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failned\n");
        exit(1);
    }

    // Now let's send the messages
    for (i = 0; i < NUM_MSGS; i++) {
        printf("Sending packet %d to %s:%d\n", i, server, SERVICE_PORT);
        sprintf(buf, "This is packet %d", i);
        // sendto params: socket file descriptor; buffer indicating the starting address
        // of the message; flags (0 for none); sockaddr struct indicating IP address
        // family, IP address, and port, length of address structure
        if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *) &remaddr, slen) < 0) {
            perror("sendto failed");
            exit(1);
        }

        // Now receive an acknowledgement from the server
        recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *) &remaddr, &slen);
        if (recvlen >= 0) {
            buf[recvlen] = 0;
            printf("Received message: \"%s\"\n", buf);
        }
    }

    close(fd);
    return 0;
}

