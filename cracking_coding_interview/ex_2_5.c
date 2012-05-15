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


main()
{
    node* head, * second, * third, * fourth, * fifth, * sixth, * seventh;
    node* eighth, * ninth, * tenth, * eleventh;
    head = malloc( sizeof( node ) );
    second = malloc( sizeof( node ) );
    third = malloc( sizeof( node ) );
    fourth = malloc( sizeof( node ) );
    fifth = malloc( sizeof( node ) );
    sixth = malloc( sizeof( node ) );
    seventh = malloc( sizeof( node ) );
    eighth = malloc( sizeof( node ) );
    ninth = malloc( sizeof( node ) );
    tenth = malloc( sizeof( node ) );
    eleventh = malloc( sizeof( node ) );

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
    sixth->next = seventh;
    seventh->data = 7;
    seventh->next = eighth;
    eighth->data = 8;
    eighth->next = ninth;
    ninth->data = 9;
    ninth->next = tenth;
    tenth->data = 10;
    tenth->next = eleventh;
    eleventh->data = 11;
    eleventh->next = fourth;

    node* slow = head;
    node* fast = head;

    while (fast && slow) {
        fast = fast->next->next;
        slow = slow->next;

        if (slow == fast)
            break;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    printf( "Loop starts at node %d", slow->data );

    puts( "\n" );
}

