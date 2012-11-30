#include <string.h>
#include <stdio.h>


int strend(char *s, char *t);


main()
{
    char s[] = "this is the end of the world!";
    char t[] = "end of the world!";

    printf("strend returned %d\n", strend(s, t));
}


int strend(char *s, char *t)
{
    int ls = strlen(s);
    int lt = strlen(t);
    if (ls < lt)
        return 0;

    int i;
    for (i = 0; i < lt; i++) {
        if (*(s + ls - i - 1) != *(t + lt - i - 1))
            return 0;
    }

    return 1;
}

