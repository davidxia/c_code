#include <stdio.h>

int i;
long l;
char c;

int main(void)
{
    printf("A char is %lu bytes on this computer.\n", sizeof(c));
    printf("An int is %lu bytes on this computer.\n", sizeof(i));
    printf("A long is %lu bytes on this computer.\n", sizeof(l));
    printf("A long is %lu bytes on this computer.\n", sizeof(&i));

    return 0;
}

