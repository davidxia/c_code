#include <stdio.h>
#include <stdlib.h>


typedef struct aNode
{
    int data;
    struct aNode* next;
} node;


void print_list( node* head )
{
    while (head) {
        printf( "%d ", head->data );
        head = head->next;
    }
}


node* add_lists( node* l1, node* l2, int carry )
{
    if (!l1 && !l2 && !carry)
        return NULL;

    int sum = carry;
    node* result = malloc( sizeof( node ) );

    if (l1)
        sum += l1->data;
    if (l2)
        sum += l2->data;
    result->data = sum % 10;

    node* more = add_lists( (l1) ? l1->next : NULL, (l2) ? l2->next : NULL, sum > 9 ? 1 : 0 );

    result->next = more;
    return result;
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

    head->data = 9;
    head->next = second;
    second->data = 1;
    second->next = third;
    third->data = 5;
    third->next = NULL;

    fourth->data = 5;
    fourth->next = fifth;
    fifth->data = 9;
    fifth->next = sixth;
    sixth->data = 9;
    sixth->next = NULL;

    node* current = head;
    puts( "First linked list:" );
    print_list( current );

    current = fourth;
    puts( "\n\nSecond linked list:" );
    print_list( current );

    puts( "\n\nNow we sum them:" );
    node* result = add_lists( head, fourth, 0 );
    print_list( result );

    puts( "\n" );
}

