#include <stdio.h>

#include "graphalg.h"
#include "../ch11/graph.h"


int intcmp(int x, int y) {
    if (x == y)
        return 1;
    else
        return 0;
}


int main() {
    Graph graph;
    char dataA = 'a', dataB = 'b', dataC = 'c', dataD = 'd', dataE = 'e', dataF = 'f';
    List span;
    ListElmt *element;
    MstVertex *mst_vertex;

    MstVertex vA = { .data = &dataA };
    MstVertex vB = { .data = &dataB };
    MstVertex vC = { .data = &dataC };
    MstVertex vD = { .data = &dataD };
    MstVertex vE = { .data = &dataE };
    MstVertex vF = { .data = &dataF };
    MstVertex *start = &vA;

    graph_init(&graph, (int (*)(const void *, const void *)) intcmp, NULL);
    graph_ins_vertex(&graph, &vA);
    graph_ins_vertex(&graph, &vB);
    graph_ins_vertex(&graph, &vC);
    graph_ins_vertex(&graph, &vD);
    graph_ins_vertex(&graph, &vE);
    graph_ins_vertex(&graph, &vF);

    /* Book says to indicate edge's weight by setting weight for
     * second vertex passed into graph_ins_edge()
     * but this rewrites it everytime
     */
    vB.weight = 7;
    graph_ins_edge(&graph, &vA, &vB);
    vA.weight = 7;
    graph_ins_edge(&graph, &vB, &vA);
    vC.weight = 4;
    graph_ins_edge(&graph, &vA, &vC);
    vA.weight = 4;
    graph_ins_edge(&graph, &vC, &vA);
    vC.weight = 6;
    graph_ins_edge(&graph, &vB, &vC);
    vB.weight = 6;
    graph_ins_edge(&graph, &vC, &vB);
    graph_ins_edge(&graph, &vB, &vD);
    graph_ins_edge(&graph, &vD, &vB);
    graph_ins_edge(&graph, &vB, &vF);
    graph_ins_edge(&graph, &vF, &vB);
    graph_ins_edge(&graph, &vC, &vE);
    graph_ins_edge(&graph, &vE, &vC);
    graph_ins_edge(&graph, &vC, &vF);
    graph_ins_edge(&graph, &vF, &vC);
    graph_ins_edge(&graph, &vD, &vF);
    graph_ins_edge(&graph, &vF, &vD);
    graph_ins_edge(&graph, &vE, &vF);
    graph_ins_edge(&graph, &vF, &vE);

    printf("is a adjacent to b? %d\n", graph_is_adjacent(&graph, &vA, &vB));
    printf("is b adjacent to c? %d\n", graph_is_adjacent(&graph, &vB, &vC));

    mst(&graph, start, &span, (int (*)(const void *key1, const void *key2)) intcmp);

    for (element = list_head(&span); element != NULL; element = list_next(element)) {
        mst_vertex = ((MstVertex *) list_data(element));
        if (mst_vertex->parent) {
            printf("node %c has parent %c\n", *((char *) (mst_vertex->data)), *((char *) mst_vertex->parent->data));
        } else {
            printf("node %c\n", *((char *) (mst_vertex->data)));
        }
    }

    return 0;
}


