#include <stdio.h>
#include "../ch5/list.h"
#include "traverse.h"


int main() {
    BiTree tree;
    List list;
    ListElmt *node;

    int data1 = 5;
    int data2 = 3;
    int data3 = 8;
    int data4 = 1;
    int data5 = 4;
    int data6 = 2;
    int data7 = 7;

    bitree_init(&tree, free);
    bitree_ins_left(&tree, NULL, &data1);
    bitree_ins_left(&tree, bitree_root(&tree), &data2);
    bitree_ins_right(&tree, bitree_root(&tree), &data3);
    bitree_ins_left(&tree, bitree_root(&tree)->left, &data4);
    bitree_ins_right(&tree, bitree_root(&tree)->left, &data5);
    bitree_ins_left(&tree, bitree_root(&tree)->left->right, &data6);
    bitree_ins_left(&tree, bitree_root(&tree)->right, &data7);

    list_init(&list, NULL);
    if (preorder(bitree_root(&tree), &list) != 0) {
        printf("preorder traversal failed\n");
        return -1;
    }
    printf("preorder traversal:\n");
    for (node = list_head(&list); node != NULL; node = list_next(node)) {
        printf("%d\n", *((int *) list_data(node)));
    }

    list_destroy(&list);
    list_init(&list, NULL);
    if (inorder(bitree_root(&tree), &list) != 0) {
        printf("inorder traversal failed\n");
        return -1;
    }
    printf("\ninorder traversal:\n");
    for (node = list_head(&list); node != NULL; node = list_next(node)) {
        printf("%d\n", *((int *) list_data(node)));
    }

    list_destroy(&list);
    list_init(&list, NULL);
    if (postorder(bitree_root(&tree), &list) != 0) {
        printf("postorder traversal failed\n");
        return -1;
    }
    printf("\npostorder traversal:\n");
    for (node = list_head(&list); node != NULL; node = list_next(node)) {
        printf("%d\n", *((int *) list_data(node)));
    }

    return 0;
}

