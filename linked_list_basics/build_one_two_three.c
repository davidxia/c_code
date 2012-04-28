#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

/*
 * Build the list {1, 2, 3} in the heap and store
 * its head pointer in a local stack variable.
 * Returns the head pointer to the caller.
 */
struct node* BuildOneTwoThree() {
    struct node* head;
    struct node* second;
    struct node* third;

    head = malloc(sizeof(struct node));     // allocate 3 nodes in heap
    second = malloc(sizeof(struct node));
    third = malloc(sizeof(struct node));

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
 * Given a linked list head pointer, compute
 * and return the number of nodes in the list.
 */
int Length(struct node* head) {
    struct node* current = head;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

int main(void) {
    struct node* head = BuildOneTwoThree();
    printf("Length: %d", Length(head));

    printf("\nNode values: \n");
    struct node* current = head;
    while (current != NULL) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("\n\n");
    return 0;
}
