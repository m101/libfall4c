#ifndef ARBRES_BINAIRES_H
#define ARBRES_BINAIRES_H

#include <stddef.h>             /* pour size_t */

#include "list.h"
#include "arbres_binaires.h"
#include "pathfinding.h"

struct t_branche
{
    struct t_branche *parent;
    struct List feuille;
};

struct List* binary_search_tree_add (struct List *node,
                    long integer);
struct List* binary_search_tree_add_path (struct List *node,
                    struct t_path_node *pathNode);
void binary_tree_display (struct List *racine);
void binary_tree_display_right (struct List *racine);
void binary_tree_display_path (struct List *racine);
struct List* binary_search_tree_search_lowestCostNode (struct List *Root);

// Ouvert ou ferme?
void binary_search_tree_search_isOpen (struct List *Root, t_path_node *Node);
void binary_search_tree_search_isClose (struct List *Root, t_path_node *Node);

// AVL
struct t_tree
{
    void *data;
    int balance;
    int h;
    int elt;
    List *node;
    t_tree *left, *right;
    t_tree *son, *brother;

    // functions
    int (*comparator)(void *data1, void *data2);
};

#endif /* not H_LISTEDOUBLE */
