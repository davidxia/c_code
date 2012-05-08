#include <stdio.h>


/* Reverse a string */
void reverse( char* str )
{
    char* end = str;
    char tmp;

    if (!str)
        return;

    while (*end)
        ++end;

    --end;

    while (str < end) {
        tmp = *str;
        *str++ = *end;
        *end-- = tmp;
    }
}


main()
{
    char str[] = "STRING";
    reverse( str );
    printf( "%s", str );
}

