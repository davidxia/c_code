#include <stdio.h>
#include <stdlib.h>

#include "directls.h"


int main() {
    Directory **dir;
    char *path = "/home/david/";
    int i;

    if ((dir = (Directory **) malloc(sizeof(Directory *))) == NULL)
        return -1;

    int count = directls(path, dir);
    printf("number of entries in %s: %d\n", path, count);

    for (i = 0; i < count; i++) {
        printf("%s\n", (*dir)[i].name);
    }

    return 0;
}

