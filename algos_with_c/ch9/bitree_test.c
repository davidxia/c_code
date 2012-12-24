#include <stdio.h>
#include "bitree.h"


int main() {
    BiTree tree;
    BiTreeNode *node;

    int data1 = 5;
    int data2 = 3;
    int data3 = 8;
    int data4 = 1;

    bitree_init(&tree, free);
    bitree_ins_left(&tree, NULL, &data1);
    bitree_ins_left(&tree, bitree_root(&tree), &data2);
    bitree_ins_right(&tree, bitree_root(&tree), &data3);
    bitree_ins_left(&tree, bitree_root(&tree)->left, &data4);

    for (node = bitree_root(&tree); node != NULL; node = bitree_left(node)) {
        printf("%d\n", *((int *) bitree_data(node)));
    }

    return 0;
}

