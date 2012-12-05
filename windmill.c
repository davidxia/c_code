#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char s[] = {'|', '\\', '-', '/'};


int main()
{
    int i = 0;

    while (1) {
        i %= 4;
        printf("%c ", s[i++]);
        fflush(stdout);
        usleep(250000);
        printf("%s", "\b\b");
        fflush(stdout);
    }
}

