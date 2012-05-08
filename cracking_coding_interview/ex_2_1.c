#include <stdio.h>
#include <stdlib.h>


typedef struct aNode
{
    int data;
    struct aNode* next;
} node;


/* Remove duplicates from an unsorted linked list. */
void dedup( node** headRef )
{
    int arr[ 10 ] = { 0 };
    node* current = *headRef;
    node* prev = NULL;

    while (current) {
        if (arr[ current->data ])
            prev->next = current->next;
        else {
            arr[ current->data ] = 1;
            prev = current;
        }
        current = current->next;
    }
}


/* Without a buffer. */
void dedup2( node** headRef )
{
    if (!*headRef)
        return;

    node* current;
    node* tail = (*headRef)->next;

    for (current = (*headRef)->next; current; current = current->next) {
        node* runner;

        for (runner = *headRef; runner != tail; runner = runner->next) {
            if (runner->data == current->data) {
                break;
            }
        }

        if (runner == tail) {
            tail->data = current->data;
            tail = tail->next;
        }
    }

    for (current = *headRef; current->next != tail; current = current->next)
        ;
    current->next = NULL;
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
    third->data = 1;
    third->next = fourth;
    fourth->data = 2;
    fourth->next = fifth;
    fifth->data = 3;
    fifth->next = sixth;
    sixth->data = 4;
    sixth->next = NULL;

    node* current = head;
    puts( "Linked list:" );
    while (current) {
        printf( "%d ", current->data );
        current = current->next;
    }

    dedup2( &head );

    puts( "\n\nAfter dedup:" );
    current = head;
    while (current) {
        printf( "%d ", current->data );
        current = current->next;
    }

    puts( "\n\n" );
}

