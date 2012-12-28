#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bistree.h"
#include "../ch5/list.h"
#include "traverse.h"


int main() {
    BisTree tree;
    List list;
    ListElmt *node;

    bistree_init(&tree, (int (*)(const void *, const void *)) strcmp, free);

    char *data1 = "car";
    char *data2 = "baby";
    char *data3 = "dog";
    char *data4 = "apple";
    char *data5 = "aardvark";

    bistree_insert(&tree, data1);
    bistree_insert(&tree, data2);
    bistree_insert(&tree, data3);
    bistree_insert(&tree, data4);
    bistree_insert(&tree, data5);

    printf("tree size = %d\n", tree.size);

    list_init(&list, NULL);
    if (preorder(bitree_root(&tree), &list) != 0) {
        printf("preorder traversal failed\n");
        return -1;
    }
    printf("\npreorder traversal:\n");
    for (node = list_head(&list); node != NULL; node = list_next(node)) {
        printf("%s\n", (char *) ((BiTreeNode *) list_data(node))->data);
    }

    list_destroy(&list);
    list_init(&list, NULL);
    if (inorder(bitree_root(&tree), &list) != 0) {
        printf("inorder traversal failed\n");
        return -1;
    }
    printf("\ninorder traversal:\n");
    for (node = list_head(&list); node != NULL; node = list_next(node)) {
        printf("%s\n", (char *) ((BiTreeNode *) list_data(node))->data);
    }

    list_destroy(&list);
    list_init(&list, NULL);
    if (postorder(bitree_root(&tree), &list) != 0) {
        printf("postorder traversal failed\n");
        return -1;
    }
    printf("\npostorder traversal:\n");
    for (node = list_head(&list); node != NULL; node = list_next(node)) {
        printf("%s\n", (char *) ((BiTreeNode *) list_data(node))->data);
    }

    char *data6 = "apple";
    // Why won't this work? It's late. I'm going to bed.
    printf("lookup of apple returned %d\n", bistree_lookup(&tree, (void **) &data6));

    return 0;
}

