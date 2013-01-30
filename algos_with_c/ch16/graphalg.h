#ifndef GRAPHALG_H
#define GRAPHALG_H

#include "../ch11/graph.h"
#include "../ch5/list.h"


/* Define a structure for vertices in minimum spanning trees */
typedef struct MstVertex_ {
    void *data;
    double weight;
    VertexColor color;
    double key;
    struct MstVertex_ *parent;
} MstVertex;

/* Define a structure for vertices in shortest-path problems */
typedef struct PathVertex_ {
    void *data;
    double weight;
    VertexColor color;
    double d;
    struct PathVertex_ *parent;
} PathVertex;

/* Define a structure for vertices in traveling-salesman problems */
typedef struct TspVertex_ {
    void *data;
    double x, y;
    VertexColor color;
} TspVertex;


int mst(Graph *graph, const MstVertex *start, List *span, int (*match)(const void *key1, const void *key2));
int shortest(Graph *graph, const PathVertex *start, List *paths, int (*match)(const void *key1, const void *key2));
int tsp(List *vertices, const TspVertex *start, List *tour, int (*match)(const void *key1, const void *key2));

#endif

