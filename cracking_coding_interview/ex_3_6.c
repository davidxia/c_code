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
    STACK* stackA = malloc( sizeof( STACK ) );
    push( stackA, 2 );
    push( stackA, 99 );
    push( stackA, 3 );
    push( stackA, 1 );
    push( stackA, 4 );

    STACK* stackB = malloc( sizeof( STACK ) );

    while (!is_empty( stackA )) {
        int tmp = pop( stackA );
        while (!is_empty( stackB ) && peek( stackB ) > tmp)
            push( stackA, pop( stackB ) );
        push( stackB, tmp );
    }

    while (!is_empty( stackB ))
        printf( "pop: %d\n", pop( stackB ) );

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

