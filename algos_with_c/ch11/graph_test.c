#include <stdio.h>

#include "graph.h"
#include "../ch5/list.h"
#include "../ch7/set.h"


int intcmp(int x, int y) {
    if (x == y)
        return 1;
    else
        return 0;
}


int main() {
    Graph graph;
    AdjList *adjlist;
    ListElmt *element;

    int v1 = 3;
    int v2 = 5;
    int v3 = 4;
    int v4 = 1;

    graph_init(&graph, (int (*)(const void *, const void *)) intcmp, NULL);
    graph_ins_vertex(&graph, &v1);
    graph_ins_vertex(&graph, &v2);
    graph_ins_vertex(&graph, &v3);
    graph_ins_vertex(&graph, &v4);
    graph_ins_edge(&graph, &v1, &v2);
    graph_ins_edge(&graph, &v1, &v3);
    graph_ins_edge(&graph, &v1, &v4);
    graph_ins_edge(&graph, &v3, &v4);

    printf("is 3 adjacent to 5? %d\n", graph_is_adjacent(&graph, &v1, &v2));
    printf("is 4 adjacent to 5? %d\n", graph_is_adjacent(&graph, &v3, &v2));

    return 0;
}

