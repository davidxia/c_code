#include <stdio.h>

char *my_strcpy(char *destination, const char *source)
{
    char *p = destination;
    while (*source != '\0')
    {
        *p++ = *source++;
    }
    *p = '\0';
    return destination;
}

char *my_strcpy2(char dest[], char source[])
{
    int i = 0;
    while (source[i] != '\0')
    {
        dest[i] = source[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}


int main(void)
{
    char strA[80] = "A string to be used for demonstration purposes";
    char strB[80];
    char strC[80];

    puts(strA);
    puts(strB);
    putchar('\n');

    my_strcpy(strB, strA);
    puts(strA);
    puts(strB);
    putchar('\n');

    my_strcpy2(strC, strA);
    puts(strA);
    puts(strC);

    return 0;
}

