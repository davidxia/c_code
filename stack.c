#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100


/* Array implementation of stack */
typedef struct {
    size_t size;
    int items[ STACKSIZE ];
} STACK;


void push( STACK *ps, int x );
int pop( STACK *ps );
int peek( STACK *ps );
int is_empty( STACK *ps );


/* Linked list implementation of stack */
typedef struct stack {
    int data;
    struct stack* next;
} STACK_LIST;


main()
{
    STACK* stack = malloc( sizeof( STACK ) );
    push( stack, 1 );
    push( stack, 2 );
    push( stack, 3 );
    push( stack, 4 );
    push( stack, 5 );

    printf( "stack size: %lu\n", stack->size );

    printf( "pop: %d\n", pop( stack ) );
    printf( "pop: %d\n", pop( stack ) );
    printf( "pop: %d\n", pop( stack ) );

    printf( "peek: %d\n", peek( stack ) );
    printf( "pop: %d\n", pop( stack ) );
    printf( "is empty? %d\n", is_empty( stack ) );

    printf( "\n" );
}


void push( STACK *ps, int x )
{
    if (ps->size == STACKSIZE) {
        fputs( "Error: stack overflow\n", stderr );
        abort();
    } else
        ps->items[ ps->size++ ] = x;
}


int pop( STACK *ps )
{
    if (ps->size == 0) {
        fputs( "Error: stack underflow\n", stderr );
        abort();
    } else
        return ps->items[ --ps->size ];
}


int peek( STACK *ps )
{
    if (ps->size == 0) {
        fputs( "Error: stack underflow\n", stderr );
        abort();
    } else
        return ps->items[ ps->size - 1 ];
}


int is_empty( STACK *ps )
{
    if (ps->size == 0)
        return 1;
    else
        return 0;
}

