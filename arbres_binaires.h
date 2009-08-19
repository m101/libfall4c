#ifndef ARBRES_BINAIRES_H
#define ARBRES_BINAIRES_H

#include <stddef.h>             /* pour size_t */

#include "listes_doubles.h"
#include "arbres_binaires.h"
#include "pathfinding.h"

typedef struct t_branche t_branche;
struct t_branche
{
    struct t_branche *parent;
    struct t_double_linked_list feuille;
};

struct t_double_linked_list* binary_search_tree_add (struct t_double_linked_list *node,
                    long integer);
struct t_double_linked_list* binary_search_tree_add_path (struct t_double_linked_list *node,
                    struct t_path_node *pathNode);
void binary_tree_display (struct t_double_linked_list *racine);
void binary_tree_display_right (struct t_double_linked_list *racine);
void binary_tree_display_path (struct t_double_linked_list *racine);
struct t_double_linked_list* binary_search_tree_search_lowestCostNode (struct t_double_linked_list *Root);

// Ouvert ou ferme?
void binary_search_tree_search_isOpen (struct t_double_linked_list *Root, t_path_node *Node);
void binary_search_tree_search_isClose (struct t_double_linked_list *Root, t_path_node *Node);

// AVL

typedef struct t_tree t_tree;

struct t_tree
{
    void *data;
    int balance;
    int h;
    int elt;
    t_double_linked_list *node;
    t_tree *left, *right;
};

#endif /* not H_LISTEDOUBLE */
