#include <stdio.h>

#include "bfs.h"


int intcmp(int x, int y) {
    if (x == y)
        return 1;
    else
        return 0;
}


int main() {
    Graph graph;
    BfsVertex v1, v2, v3, v4, v5, v6, *bfs_vertex;
    List hops;
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

    if (bfs(&graph, &v1, &hops) != 0)
        return -1;

    printf("Starting vertex is %d\n\n", *((int *) v1.data));

    for (element = list_head(&hops); element != NULL; element = list_next(element)) {
        bfs_vertex = list_data(element);
        printf("vertex %d is %d hops from the start\n", *((int *) bfs_vertex->data), bfs_vertex->hops);
    }

    return 0;
}

