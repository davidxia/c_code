#include <ctype.h>
#include <stdio.h>


double atof( char s[] );


main()
{
    char s[] = "203.33";
    printf( "The converted double of %s is %f\n", s, atof( s ) );
}


/* atof: convert string s to double */
double atof( char s[] )
{
    double val, power;
    int i, sign;

    // Skip white space
    for (i = 0; isspace( s[ i ] ); i++)
        ;

    sign = (s[ i ] == '-') ? -1 : 1;
    if (s[ i ] == '+' || s[ i ] == '-')
        i++;

    for (val = 0.0; isdigit( s[ i ] ); i++)
        val = 10.0 * val + (s[ i ] - '0');

    if (s[ i ] == '.')
        i++;

    for (power = 1.0; isdigit( s[ i ] ); i++) {
        val = 10.0 * val + (s[ i ] - '0');
        power *= 10;
    }

    return sign * val / power;
}

