#include <stdio.h>      // for fprintf
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include "port.h"

#define BUFSIZE 2048


int main(int argc, char **argv) {
    struct sockaddr_in myaddr;  // our address
    struct sockaddr_in remaddr; // remote address
    socklen_t addrlen = sizeof(remaddr); // length of addresses
    int recvlen;                // # bytes received
    int fd;                     // our socket
    int msg_count = 0;          // number of messages we received
    unsigned char buf[BUFSIZE]; // receive buffer

    unsigned int alen; // length of address for getsockname


    // create a UDP socket
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Cannot create socket\n");
        return 0;
    }

    // Bind the socket to any valid IP address (ie all interfaces)
    // and a specific port
    memset((char *) &myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(SERVICE_PORT);

    if (bind(fd, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0) {
        perror("Bind failed.");
        return 0;
    }

    alen = sizeof(myaddr);
    if (getsockname(fd, (struct sockaddr *) &myaddr, &alen) < 0) {
        perror("getsockname failed");
        return 0;
    }

    printf("bind complete. Port number = %d\n", ntohs(myaddr.sin_port));

    // Now loop, receiving data and printing what we received
    for (;;) {
        printf("Waiting on port %d\n", SERVICE_PORT);
        recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *) &remaddr, &addrlen);
        printf("received %d bytes\n", recvlen);
        if (recvlen > 0) {
            buf[recvlen] = 0;
            printf("received message: \"%s\"\n", buf);
        } else {
            printf("uh oh - something went wrong!\n");
        }

        sprintf(buf, "ack %d", msg_count++);
        printf("sending response \"%s\"\n", buf);
        if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *) &remaddr, addrlen) < 0) {
            perror("sendto");
        }
    }
}

