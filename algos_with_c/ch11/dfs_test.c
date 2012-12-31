#include <stdio.h>

#include "dfs.h"


int intcmp(int x, int y) {
    if (x == y)
        return 1;
    else
        return 0;
}


int main() {
    Graph graph;
    DfsVertex v1, v2, v3, v4, v5, v6, *dfs_vertex;
    List ordered;
    ListElmt *element;

    int v1data = 3;
    int v2data = 5;
    int v3data = 4;
    int v4data = 1;
    int v5data = 7;
    int v6data = 8;

    v1.data = &v1data;
    v2.data = &v2data;
    v3.data = &v3data;
    v4.data = &v4data;
    v5.data = &v5data;
    v6.data = &v6data;

    graph_init(&graph, (int (*)(const void *, const void *)) intcmp, NULL);
    graph_ins_vertex(&graph, &v1);
    graph_ins_vertex(&graph, &v2);
    graph_ins_vertex(&graph, &v3);
    graph_ins_vertex(&graph, &v4);
    graph_ins_vertex(&graph, &v5);
    graph_ins_vertex(&graph, &v6);
    graph_ins_edge(&graph, &v1, &v2);
    graph_ins_edge(&graph, &v1, &v3);
    graph_ins_edge(&graph, &v1, &v4);
    graph_ins_edge(&graph, &v3, &v4);
    graph_ins_edge(&graph, &v4, &v5);
    graph_ins_edge(&graph, &v5, &v6);

    if (dfs(&graph, &ordered) != 0)
        return -1;

    printf("Topological ordering of graph with depth-first search:\n");
    for (element = list_head(&ordered); element != NULL; element = list_next(element)) {
        dfs_vertex = list_data(element);
        printf("%d\n", *((int *) dfs_vertex->data));
    }

    return 0;
}

