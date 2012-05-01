#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 100;

void generateRandomArray( int arr[], int len );
void printArray( int arr[], int len );
void maxHeapify( int arr[], int len, int iNode );
void buildMaxHeap( int arr[], int len, int iNode );
void insert( int arr[], int* lenPointer, int data );


int main( void )
{
    int len;
    printf( "Enter desired size of heap up to 100:\n" );
    scanf( "%d", &len );

    int heapArr[ MAX_SIZE ];
    generateRandomArray( heapArr, len );
    printArray( heapArr, len );

    printf( "\n\nWe turn this heap into a max heap.\n" );
    buildMaxHeap( heapArr, len, 0 );
    printArray( heapArr, len );

    printf( "\n\nEnter number to insert into heap.\n" );
    int newData;
    scanf( "%d", &newData );
    insert( heapArr, &len, newData );
    printArray( heapArr, len );

    printf( "\n\nWe extract the root value from the heap:\n" );
    printf( "%d\n", delete( heapArr, &len ) );
    printArray( heapArr, len );

    printf( "\n\n" );
    return 0;
}


void generateRandomArray( int arr[], int len )
{
    int i;
    for (i = 0; i < len; i++)
        arr[ i ] = arc4random() % 100;
    for (i; i < MAX_SIZE; i++)
        arr[ i ] = -1;
}


void printArray( int arr[], int len )
{
    int i;

    for (i = 0; i < len; i++)
        printf( "%d, ", arr[ i ] );
}


void maxHeapify( int arr[], int len, int iNode )
{
    int iLeft = 2 * iNode + 1;
    int iRight = 2 * iNode + 2;
    int iLargest = iNode;

    if (iLeft < len && arr[ iLeft ] > arr[ iLargest ])
        iLargest = iLeft;
    if (iRight < len && arr[ iRight ] > arr[ iLargest ])
        iLargest = iRight;

    if (iNode != iLargest) {
        int temp = arr[ iNode ];
        arr[ iNode ] = arr[ iLargest ];
        arr[ iLargest ] = temp;
        maxHeapify( arr, len, iLargest );
    }
}

void buildMaxHeap( int arr[], int len, int iNode )
{
    int i;
    for (i = len/2; i >= 0; i--)
        maxHeapify( arr, len, i );
}

void insert( int arr[], int* lenPointer, int data )
{
    int iNew = *lenPointer;
    int iParent = iNew / 2;

    arr[ iNew ] = data;

    while (iNew > 0) {

        if (arr[ iParent ] < arr[ iNew ]) {
            data = arr[ iNew ];
            arr[ iNew ] = arr[ iParent ];
            arr[ iParent ] = data;
        }

        iNew = iNew / 2;
        iParent = iParent / 2;
    }

    *lenPointer = *lenPointer + 1;
}


int delete( int arr[], int* lenPointer )
{
    int rootVal = arr[ 0 ];
    *lenPointer = *lenPointer - 1;
    arr[ 0 ] = arr[ *lenPointer ];
    maxHeapify( arr, *lenPointer, 0 );

    return rootVal;
}

