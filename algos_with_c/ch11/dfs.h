#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "../ch5/list.h"


/* Define a structure for vertices in a depth-first search */
typedef struct DfsVertex_ {
    void *data;
    VertexColor color;
} DfsVertex;


int dfs(Graph *graph, List *ordered);

#endif

