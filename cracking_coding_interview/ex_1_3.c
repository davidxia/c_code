#include <stdio.h>
#include <string.h>


/* Remove duplicate chars from string. */
void dedup( char* str )
{
    if (!str)
        return;

    int len = strlen( str );
    if (len < 2)
        return;

    int tail = 1;
    int i;

    for (i = 1; i < len; ++i) {
        int j;
        for (j = 0; j < tail; ++j) {
            if (str[ i ] == str[ j ])
                break;
        }

        if (j == tail) {
            str[ tail ] = str[ i ];
            ++tail;
        }
    }

    str[ tail ] = '\0';

}


/* With additional memory of constant size */
void dedup2( char* str )
{
    if (!str)
        return;

    int len = strlen( str );
    if (len < 2)
        return;

    int hit[ 256 ] = { 0 };
    int i;
    int tail = 0;

    for (i = 0; i < len; ++i) {
        if (!hit[ str[ i ] ]) {
            str[ tail ] = str[ i ];
            ++tail;
            hit[ str[ i ] ] = 1;
        }
    }

    str[ tail ] = '\0';
}


main()
{
    char str[] = "aabb";
    dedup2( str );
    printf( "%s", str );
}

