#include <stdio.h>


void strCat(char *s, char *t);


main()
{
    char s[100] = "now is the time";
    char t[] = " to party";

    strCat(s, t);
    printf("s = %s\n", s);
}


/* strCat: concatenate t to end of s; s must be big enough */
void strCat(char *s, char *t)
{
    // Find end of s
    // Prefix instead of postfix incrementor absolutely necessary,
    // otherwise, null char will be left in the string
    while (*++s)
        ;

    // Copy t
    while (*s++ = *t++)
        ;
}

