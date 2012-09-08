#ifndef _GRAPH_H_
#define _GRAPH_H_

struct graph_node
{
        int weigth;
        struct graph_node *adjacent, *neighbourg;
};

struct graph_edge
{
        int weight;
        struct graph_node *next, *prev;
};

int graph_node_add (struct graph_node *node);

#endif

