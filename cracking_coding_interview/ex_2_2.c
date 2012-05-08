#include <stdio.h>
#include <stdlib.h>


typedef struct aNode
{
    int data;
    struct aNode* next;
} node;


/* Implement an algorithm to find the nth to last element of a singly linked list. */
node* nth_to_last( node* head, int n)
{
    if (!head || n < 1)
        return NULL;

    node* p1 = head;
    node* p2 = head;
    int j;

    // Move p1 n - 1 steps ahead
    for (j = 0; j < n - 1; ++j) {
        if (!p2) {
            // If list length < n
            return NULL;
        }

        p2 = p2->next;
    }

    while (p2->next) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1;
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

    int n;
    puts( "Enter nth to last node to return:" );
    scanf( "%d", &n );
    node* p = nth_to_last( head, n );
    if (p)
        printf( "%d\n", p->data );
    else
        puts( "invalid selection" );
}

