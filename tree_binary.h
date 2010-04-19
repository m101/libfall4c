#ifndef ARBRES_BINAIRES_H
#define ARBRES_BINAIRES_H

#include <stddef.h>             /* pour size_t */

#include "tree_t.h"
#include "arbres_binaires.h"
#include "pathfinding.h"

struct tree_t* binary_search_tree_add (struct tree_t *node,
                    long integer);
void binary_tree_display (struct tree_t *racine);
void binary_tree_display_right (struct tree_t *racine);

// AVL
struct tree_t
{
    // root of the tree
    struct tree_node_t *root;
    // balance of the tree
    int balance;
    // height of the tree
    int height;
    // number of nodes
    size_t n;

    // functions
    int (*comparator)(void *data1, void *data2);
    size_t (*get_data_size)(void *data);
};

struct tree_node_t
{
    void *data;
    int weight;
    struct t_tree *left, *right;
    struct t_tree *son, *brother;
};

#endif /* not H_tree_tEDOUBLE */
