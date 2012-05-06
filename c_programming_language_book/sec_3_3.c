#include <stdio.h>
#include <sys/time.h>

#define MAX_SIZE 1000000
/* #define MAX_SIZE 4294967295 */

/* binsearch: find x in v[ 0 ] <= v[ 1 ] <= ... <= v[ n - 1 ] */
int binsearch( int x, int v[], int n )
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;

        if (x < v[ mid ])
            high = mid - 1;
        else if (x > v[ mid ])
            low = mid + 1;
        // Found match
        else
            return mid;
    }
    // No match
    return -1;
}


int binsearch2( int x, int v[], int n )
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;

        if (x < v[ mid ])
            high = mid - 1;
        else
            low = mid;
    }

    if ( (high == low) && (v[ low ] == x) )
        return low;
    else
        // No match
        return -1;
}


main()
{
    unsigned int x = arc4random() % MAX_SIZE;
    printf( "%d\n", x );
    int v[ MAX_SIZE ];
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
        v[ i ] = i;

    clock_t start, end;
    double elapsed;

    start = clock();
    printf( "binsearch( %d, v[], %d) = %d\n", x, MAX_SIZE, binsearch( x, v, MAX_SIZE ) );
    end = clock();
    elapsed = (double) (end - start) / CLOCKS_PER_SEC * 1e6;
    printf( "%.2f microseconds elapsed", elapsed );

    start = clock();
    printf( "\nbinsearch2( %d, v[], %d) = %d\n", x, MAX_SIZE, binsearch2( x, v, MAX_SIZE ) );
    end = clock();
    elapsed = (double) (end - start) / CLOCKS_PER_SEC * 1e6;
    printf( "%.2f microseconds elapsed", elapsed );

    printf( "\n\n" );
}

