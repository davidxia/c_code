#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int comp( const void* s1, const void* s2 )
{
    char c1 = * (char*) s1;
    char c2 = * (char*) s2;
    return c1 - c2;
}


/* Sort chars in string then compare */
int anagram( char* str1, char* str2 )
{
    int max_strlen = (strlen( str1 ) > strlen( str2 ) ) ? strlen( str1 ) : strlen( str2 );

    qsort( str1, strlen( str1 ), sizeof( str1[ 0 ] ), comp );
    qsort( str2, strlen( str2 ), sizeof( str2[ 0 ] ), comp );

    if (strncmp( str1, str2, max_strlen ) == 0)
        return 1;
    else
        return 0;
}


/* Count occurrence of each char */
int anagram2( char* str1, char* str2 )
{
    int str1len = strlen( str1 );
    int str2len = strlen( str2 );

    if (str1len != str2len)
        return 0;

    int letters[ 256 ] = { 0 };
    int num_unique_chars = 0;
    int num_completed_str2 = 0;
    int i;

    for (i = 0; i < str1len; i++) {
        if (letters[ str1[ i ] ] == 0)
            ++num_unique_chars;
        ++letters[ str1[ i ] ];
    }

    for (i = 0; i < str2len; i++) {
        if (letters[ str2[ i ] ] == 0)
            return 0;

        --letters[ str2[ i ] ];
    }

    return 1;
}


main()
{
    char str1[] = "dormitory";
    char str2[] = "dirtyroom";

    puts( str1 );
    puts( str2 );

    if (anagram( str1, str2 ) )
        puts( "They are anagrams" );
    else
        puts( "Not anagrams" );

    puts( str1 );
    puts( str2 );

    int c = anagram2( str1, str2 );
    printf( "%d\n", c );

}

