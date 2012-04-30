/* Taken from http://maxnoy.com/interviews.html */

#include <stdio.h>
#include <stdlib.h>

struct aNode
{
    int data;
    struct aNode* next;
};

typedef struct aNode node;


node* buildSinglyLinkedList()
{
    node* head = malloc( sizeof( node ) );
    node* second = malloc( sizeof( node ) );
    node* third = malloc( sizeof( node ) );
    node* fourth = malloc( sizeof( node ) );
    node* fifth = malloc( sizeof( node ) );

    head->data = -2;
    head->next = second;
    second->data = 1;
    second->next = third;
    third->data = 4;
    third->next = fourth;
    fourth->data = 6;
    fourth->next = fifth;
    fifth->data = 7;
    fifth->next = NULL;

    return head;
}


void printList( node* head )
{
    node* current = head;
    for (current = head; current; current = current->next)
    {
        printf( "%d, ", current->data );
    }
}


void insert( node** headRef, int data )
{
    node* newNode = malloc( sizeof( node ) );
    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;
}


void delete( node** headRef, int iDelete )
{
    node* current = *headRef;
    int i;

    for (i = 0; i < iDelete - 1; i++)
    {
        current = current->next;
    }

    node* deletionNode = current->next;
    current->next = (current->next)->next;
    free( deletionNode );
}


void insertIntoOrderedList( node** headRef, int data )
{
    node* current = *headRef;
    node* prev = NULL;

    while (current && current->data < data)
    {
        prev = current;
        current = current->next;
    }

    node* newNode = malloc( sizeof( node ) );
    newNode->data = data;
    newNode->next = current;

    if (prev)
    {
        prev->next = newNode;
    }
    else
    {
        *headRef = newNode;
    }
}


int main( void )
{
    printf( "We create a singly-linked list\n" );
    node* head = buildSinglyLinkedList();
    printList( head );

    printf( "\n\nNow we insert 99 at the head\n" );
    insert( &head, 99 );
    printList( head );

    printf( "\n\nWe delete the second node\n" );
    delete( &head, 1 );
    printList( head );

    printf( "\n\nReset the linked list\n" );
    head = buildSinglyLinkedList();
    printList( head );
    printf( "\n\nAdd 5 and preserve the order\n" );
    insertIntoOrderedList( &head, 5 );
    printList( head );


    printf( "\n\n" );
    return 0;
}
