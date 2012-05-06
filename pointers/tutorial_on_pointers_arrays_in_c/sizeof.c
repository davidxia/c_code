#include <stdio.h>
#include <limits.h>
#include <time.h>

/* Display the platform-specific values of data type sizes and other stuff. */
main()
{
    printf( "Any type not listed below isn't valid.\n\n" );
    printf( "byte \t\t\t\t %d bits\n", CHAR_BIT );

    printf( "========================================\n" );

    printf( "void \t\t %lu bytes \t %lu bits\n", sizeof( void ), sizeof( void ) * CHAR_BIT );
    printf( "char \t\t %lu byte \t %lu bits\n", sizeof( char ), sizeof( char ) * CHAR_BIT );
    printf( "int \t\t %lu bytes \t %lu bits\n", sizeof( int ), sizeof( int ) * CHAR_BIT );
    printf( "float \t\t %lu bytes \t %lu bits\n", sizeof( float ), sizeof( float ) * CHAR_BIT );
    printf( "double \t\t %lu bytes \t %lu bits\n", sizeof( double ), sizeof( double ) * CHAR_BIT );
    /* Size of enum is compiler dependent and may differ between enums */

    printf( "========================================\n" );

    printf( "short int \t %lu bytes \t %lu bits\n", sizeof( short int ), sizeof( short int ) * CHAR_BIT );
    printf( "long int \t %lu bytes \t %lu bits\n", sizeof( long int ), sizeof( long int ) * CHAR_BIT );
    printf( "long double \t %lu bytes \t %lu bits\n", sizeof( long double ), sizeof( long double ) * CHAR_BIT );

    printf( "========================================\n" );

    printf( "CLOCKS_PER_SEC = %d", CLOCKS_PER_SEC );

    printf( "\n\n" );
}

