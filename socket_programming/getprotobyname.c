#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        printf( "usage: %s protocol", argv[0] );
        exit(1);
    }

    const char *protocol_name = argv[1];
    struct protoent *protocol = getprotobyname(protocol_name);

    if (!protocol) {
        fprintf(stderr, "Protocol %s not found", protocol_name);
        exit(1);
    }

    int protocol_number = protocol->p_proto;
    printf("Protocol number for %s is %d\n", protocol_name, protocol_number);
    return 0;
}

