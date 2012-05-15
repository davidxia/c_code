#include <stdio.h>


#define STACKSIZE 4


/* Use a single array to implement three stacks. */
int buffer[ 3 * STACKSIZE ];
int stack_pointers[ 3 ] = { 0 };


void print_buffer()
{
    int i;
    for (i = 0; i < 3 * STACKSIZE; ++i)
        printf( "%d ", buffer[ i ] );
}


void push( int stack_num, int value )
{
    /* Find the index of the top element in the array + 1, and increment the stack pointer. */
    int index = stack_num * STACKSIZE + stack_pointers[ stack_num ];
    stack_pointers[ stack_num ]++;
    buffer[ index ] = value;
}


int pop( int stack_num )
{
    int index = stack_num * STACKSIZE + stack_pointers[ stack_num ] - 1;
    stack_pointers[ stack_num ]--;
    int value = buffer[ index ];
    buffer[ index ] = 0;
    return value;
}


int peek( int stack_num )
{
    int i = stack_num * STACKSIZE + stack_pointers[ stack_num ] - 1;
    return buffer[ i ];
}

int is_empty( int stack_num )
{
    return !stack_pointers[ stack_num ];
}


main()
{
    push( 1, 3 );
    push( 0, 3 );
    push( 2, 3 );

    print_buffer();

    printf( "\n\n" );
    printf( "%d\n", pop( 2 ) );
    printf( "%d\n", pop( 1 ) );
    printf( "%d\n", peek( 0 ) );
    printf( "Is stack 0 empty? %d\n", is_empty( 0 ) );
}

