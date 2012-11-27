#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100

double atof( char s[] );
int getLine( char line[], int max );
int to_power( int base, int exp);

// rudimentary calculator
main()
{
    double sum, atof( char[] );
    char line[ MAXLINE ];
    int getLine( char line[], int max );

    sum = 0;
    while (getLine( line, MAXLINE ) > 0)
        printf( "\t%g\n", sum += atof( line ) );
    return 0;
}


/* atof: convert string s to double */
double atof( char s[] )
{
    double val, power, exp;
    int i, sign, exp_sign;

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

    if (s[ i ] == 'e' || s[ i ] == 'E') {
        i++;
    } else {
        return sign * val / power;
    }

    exp_sign = (s[ i ] == '-') ? -1 : 1;
    if (s[ i ] == '+' || s[ i ] == '-')
        i++;

    for (exp = 0.0; isdigit( s[ i ] ); i++)
        exp = 10.0 * exp + (s[ i ] - '0');

    if (exp_sign == 1) {
        return sign * val / power * to_power( 10, exp );
    } else {
        return sign * val / power / to_power( 10, exp );
    }
}


/* getline: get line into s, return length */
int getLine( char s[], int lim )
{
    int c, i;
    i = 0;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[ i++ ] = c;
    if (c == '\n')
        s[ i++ ] = c;
    s[ i ] = '\0';

    return i;
}


/* to_power: calculate base^exp when both are positive ints */
int to_power( int base, int exp)
{
    int res = 1;
    int i;

    if (exp < 0)
        return 0;
    for (i = 0; i < exp; i++)
        res *= base;

    return res;
}

