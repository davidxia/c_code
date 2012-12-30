#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "../ch5/list.h"
#include "../ch7/set.h"


void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data)) {
    /* Initialize graph */
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;

    /* Initialize list of adjacency-list structures */
    list_init(&graph->adjlists, NULL);
    return;
}


void graph_destroy(Graph *graph) {
    AdjList *adjlist;

    /* Remove each adjacency-list structure and destroy its adjacency list */
    while (list_size(&graph->adjlists) > 0) {
        if (list_rem_next(&graph->adjlists, NULL, (void **) &adjlist) == 0) {
            set_destroy(&adjlist->adjacent);

            if (graph->destroy != NULL)
                graph->destroy(adjlist->vertex);

            free(adjlist);
        }
    }

    /* Destroy the list of adjacency-list structures, which is now empty */
    list_destroy(&graph->adjlists);
    memset(graph, 0, sizeof(Graph));
    return;
}


int graph_ins_vertex(Graph *graph, const void *data) {
    ListElmt *element;
    AdjList *adjlist;
    int retval;

    /* Don't allow insertion of duplicate vertices */
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data, ((AdjList *) list_data(element))->vertex)) {
            return 1;
        }
    }

    /* Insert vertex */
    if ((adjlist = (AdjList *) malloc(sizeof(AdjList))) == NULL)
        return -1;

    adjlist->vertex = (void *) data;
    set_init(&adjlist->adjacent, graph->match, NULL);

    if ((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists), adjlist)) != 0)
        return retval;

    graph->vcount++;
    return 0;
}


int graph_ins_edge(Graph *graph, const void *data1, const void *data2) {
    ListElmt *element;
    int retval;

    /* Don't allow insertion of edge without both vertices being in graph */
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data2, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL)
        return -1;

    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data1, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL)
        return -1;

    /* Insert second vertex into adjacency list of the first */
    if ((retval = set_insert(&((AdjList *) list_data(element))->adjacent, data2)) != 0)
        return retval;

    /* Adjust edge count */
    graph->ecount++;
    return 0;
}


int graph_rem_vertex(Graph *graph, void **data) {
    ListElmt *element, *temp, *prev;
    AdjList *adjlist;
    int found;

    /* Traverse each adjacency list and the vertices it contains */
    prev = NULL;
    found = 0;

    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        /* Don't allow removal of vertex if it is in an adjacency list */
        if (set_is_member(&((AdjList *) list_data(element))->adjacent, *data))
            return -1;

        /* Keep a pointer to vertex to be removed */
        if (graph->match(*data, ((AdjList *) list_data(element))->vertex)) {
            temp = element;
            found = 1;
        }

        /* Keep a pointer to the vertex before the vertex to be removed */
        if (!found)
            prev = element;
    }

    /* Return if vertex not found */
    if (!found)
        return -1;

    /* Don't allow removal of vertex if its adjacency list not empty */
    if (set_size(&((AdjList *) list_data(temp))->adjacent) > 0)
        return -1;

    /* Remove vertex */
    if (list_rem_next(&graph->adjlists, prev, (void **) &adjlist) != 0)
        return -1;

    /* Free storage allocated by abstract datatype */
    *data = adjlist->vertex;
    free(adjlist);

    /* Adjust vertex count */
    graph->vcount--;
    return 0;
}


int graph_rem_edge(Graph *graph, void *data1, void **data2) {
    ListElmt *element;

    /* Locate adjacency list for first vertex */
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data1, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL)
        return -1;

    /* Remove second vertex from adjacency list of the first vertex */
    if (set_remove(&((AdjList *) list_data(element))->adjacent, data2) != 0)
        return -1;

    /* Adjust edge count */
    graph->ecount--;
    return 0;
}


int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist) {
    ListElmt *element, *prev;

    /* Locate adjacency list for the vertex */
    prev = NULL;
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data, ((AdjList *) list_data(element))->vertex))
            break;

        prev = element;
    }

    /* Return if vertex not found */
    if (element == NULL)
        return -1;

    /* Pass back the adjacency list for the vertex */
    *adjlist = list_data(element);
    return 0;
}


int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2) {
    ListElmt *element, *prev;

    /* Locate adjacency list of first vertex */
    prev = NULL;
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data1, ((AdjList *) list_data(element))->vertex))
            break;

        prev = element;
    }

    /* Return if first vertex not found */
    if (element == NULL)
        return 0;

    /* Return whether second vertex is in adjacency list of the first */
    return set_is_member(&((AdjList *) list_data(element))->adjacent, data2);
}

