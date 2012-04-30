#include <stdio.h>
#include <stdlib.h>


struct aNode
{
    int data;
    struct aNode* next;
};


typedef struct aNode node;


/*
 * Build the list {1, 2, 3} in the heap and store its head pointer in a local stack variable.
 * Returns the head pointer to the caller.
 */
node* buildOneTwoThree()
{
    node* head = NULL;
    node* second = NULL;
    node* third = NULL;

    head = malloc( sizeof( node ) );     // allocate 3 nodes in heap
    second = malloc( sizeof( node ) );
    third = malloc( sizeof( node ) );

    head->data = 1;             // setup first node
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    // At this point, the linked list referenced by "head"
    // matches the list in the drawing.
    return head;
}


/*
 * Given a linked list head pointer, traverse and print out each node's data.
 */
void printList( node* head )
{
    node* current = NULL;
    for( current = head; current; current = current->next )
    {
        printf( "%d, ", current->data );
    }
}


/*
 * Given a linked list head pointer, compute and return the number of nodes in the list.
 */
int length( node* head )
{
    node* current = head;
    int count = 0;

    for( current = head; current; current = current->next )
    {
        count++;
    }

    return count;
}


/* Takes a list and a data value. Creates a new link with the given data and pushes
 * it onto the front of the list. The list is not passed in by its head pointer.
 * Instead the list is passed in as a "reference" pointer to the header pointer --
 * this allows us to modify the caller's memory.
 */
void push( node** headRef, int data )
{
    node* newNode = malloc( sizeof( node ) );

    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;
}


void append( node** headRef, int data )
{
    node* current = *headRef;

    // special case for the empty list
    if (current == NULL)
    {
        push( headRef, data );
    }
    else
    {
        // Locate the last node
        while (current->next)
        {
            current = current->next;
        }

        // Build the node after the last node
        push( &(current->next), data );
    }
}


node* copy( node* head )
{
    node* current = head;
    node* newList = NULL;
    node** lastPtr;

    lastPtr = &newList;

    while (current)
    {
        push( lastPtr, current->data );
        lastPtr = &( (*lastPtr)->next );
        current = current->next;
    }

    return newList;
}


int insert( node** headRef, int data )
{
    node* newNode = malloc( sizeof( node ) );
    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;
    return 0;
}

int main( void )
{
    printf( "We construct a linked list (1, 2, 3)\n\n" );
    node* head = buildOneTwoThree();

    printf( "Node values: \n" );
    printList( head );

    printf( "We call the length function on it: %d\n\n", length( head ) );

    printf( "We now push 31 onto the list\n" );
    push( &head, 31 );
    printf( "We now push 28 onto the list\n" );
    push( &head, 28 );
    printList( head );

    printf( "\n\nWe now append 9 to the end of the list\n" );
    append( &head, 9 );
    printList( head );

    printf( "\n\nWe copy the list\n" );
    node* copiedList = copy( head );
    printList( copiedList );

    printf( "\n\nWe insert 11 at the head\n" );
    insert( &head, 11 );
    printList( head );

    printf( "\n\n" );
    return 0;
}

