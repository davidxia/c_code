#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

/* paddr: print the IP address in a standard decimal dotted format */
/* A character is 1 byte which is 8 bits which represents each part of an IP address.
 * That's why we use %d.
 */
void paddr(unsigned char *a) {
    printf("%d.%d.%d.%d\n", a[0], a[1], a[2], a[3]);
}

int main(int argc, char **argv) {
    struct hostent *hp;
    char *host = "google.com";
    int i;

    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "could not obtain address of %s\n", host);
        return 0;
    }
    // I can use gdb to examine hp:
    // p hp
    // (struct hostent *) 0x7ffff7dd7ee0
    // p *(struct hostent *) 0x7ffff7dd7ee0
    // {h_name = 0x60220b "google.com", h_aliases = 0x602010, h_addrtype = 2, h_length = 4, h_addr_list = 0x6021a0}
    // printf "%d.%d.%d.%d\n", *(char *)(*(char **) 0x6021a0), *(char *)((*(char **) 0x6021a0) + 1), *(char *)((*(char **) 0x6021a0) + 2), *(char *)((*(char **) 0x6021a0) + 3)
    // 74.125.-30.72
    // TODO (dxia) Sometimes I see a negative number, why does paddr take 2's complement?
    // TODO (dxia) What sets the end of h_addr_list to 0?
    for (i=0; hp->h_addr_list[i] != 0; i++)
        paddr((unsigned char*) hp->h_addr_list[i]);
    exit(0);
}

