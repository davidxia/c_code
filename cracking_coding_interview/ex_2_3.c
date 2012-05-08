#include <stdio.h>
#include <stdlib.h>


typedef struct aNode
{
    int data;
    struct aNode* next;
} node;


/* Implement an algorithm to find the nth to last element of a singly linked list. */
int delete_node( node* n )
{
    if (!n || !n->next)
        return 0;

    n->data = n->next->data;
    n->next = n->next->next;

    return 1;
}


main()
{
    node* head, * second, * third, * fourth, * fifth, * sixth;
    head = malloc( sizeof( node ) );
    second = malloc( sizeof( node ) );
    third = malloc( sizeof( node ) );
    fourth = malloc( sizeof( node ) );
    fifth = malloc( sizeof( node ) );
    sixth = malloc( sizeof( node ) );

    head->data = 1;
    head->next = second;
    second->data = 2;
    second->next = third;
    third->data = 3;
    third->next = fourth;
    fourth->data = 4;
    fourth->next = fifth;
    fifth->data = 5;
    fifth->next = sixth;
    sixth->data = 6;
    sixth->next = NULL;

    node* current = head;
    puts( "Linked list:" );
    while (current) {
        printf( "%d ", current->data );
        current = current->next;
    }

    delete_node( fourth );
    current = head;
    puts( "\n\nLinked list:" );
    while (current) {
        printf( "%d ", current->data );
        current = current->next;
    }

    puts( "\n" );
}

