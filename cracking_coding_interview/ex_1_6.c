#include <stdio.h>

#define ROWS 3
#define COLS 3


/* Given an image represented by an NxN matrix, where each pixel in the image is 4
 * bytes, write a method to rotate the image by 90 degrees Can you do this in place?
 */
void rotate( int M[][ COLS ] )
{
    int layer;

    for (layer = 0; layer < n / 2; ++layer) {
        int first = layer;
        int last = n - 1 - layer;

        for (i = first; i < last; ++i) {

}


void printMatrix( int M[][ COLS ] )
{
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf( "%d ", M[ i ][ j ] );
        }
        printf( "\n" );
    }
}


main()
{
    int M[ ROWS ][ COLS ];
    int n = 1;
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            M[ i ][ j ] = n++;
        }
    }

    printMatrix( M );
}

