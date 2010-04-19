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
    void *data;
    int balance;
    int h;
    int elt;
    tree_t *node;
    t_tree *left, *right;
    t_tree *son, *brother;

    // functions
    int (*comparator)(void *data1, void *data2);
    size_t (*get_data_size)(void *data);
};

#endif /* not H_tree_tEDOUBLE */
