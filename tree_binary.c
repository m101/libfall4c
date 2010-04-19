#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "struct tree_tes_doubles.h"
#include "arbres_binaires.h"
#include "pathfinding.h"
#include "math_basic.h"

/*  @brief  Create new tree
*/
struct tree_t* tree_new (int (*comparator)(void *, void *), size_t (*get_data_size)(void *))
{
    struct tree_t *struct tree_table;

    struct tree_table = calloc (1, sizeof(*struct tree_table));
    assert (struct tree_table != NULL);
    struct tree_table->root = calloc (1, sizeof(*(struct tree_table->root)));
    struct tree_table->comparator = comparator;
    struct tree_table->get_data_size = get_data_size;
}

/*  @brief  Destroy tree
*/
void tree_free (struct tree_t *root)
{
    if (root)
    {
        tree_free_stub (root->root);
        free (root);
    }
}

// recursively traverse nodes to free them
void tree_free_stub (struct tree_node_t *node)
{
    if (node)
    {
        tree_free_stub (node->left);
        tree_free_stub (node->right);
        free (node);
    }
}

/* @brief   add data to tree
 */
struct tree_t* binary_search_tree_add (struct tree_t *root, void *data)
{
    if (!root || !data)
        return NULL;
    binary_search_tree_add_node (root->root, data);
}

/* @brief   add node to tree
 */
struct tree_node_t* binary_search_tree_add_node (struct tree_node_t *node, void *data)
{
    if (!data)
        return NULL;
    if (!node)
    {
        node = calloc (1, sizeof(*node));
        node->data = data;
    }
    // if smaller
    // then we go left
    else if (node->comparator(node->data, data) <= 0)
        node->left = binary_search_tree_add (node->left, data);
    // if bigger
    // then we go right
    else if (node->comparator(node->data, data) > 0)
        node->right = binary_search_tree_add (node->right, data);

    return node;
}

/* @brief   Display whole tree
 */
void binary_search_tree_display (struct tree_t *root)
{
    if (root != NULL)
    {
        binary_tree_display (root->next);
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display (root->prev);
    }
}

void binary_search_tree_display_right (struct tree_t *root)
{
    if (root != NULL)
    {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_right (root->prev);
    }
}

void binary_search_tree_display_left (struct tree_t *root)
{
    if (root != NULL)
    {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_left (root->prev);
    }
}



// AVL

void binary_search_tree_sort (struct tree_t *root, struct t_path_node *Treeroot)
{
    t_double_linked_struct tree_t *struct tree_tTemp = NULL;

    if ( ((struct t_path_node *)(root->data))->cost < Treeroot->cost )
    {
        struct tree_tTemp = root->prev;
        root->prev = root;
    }

    binary_search_tree_sort (root->prev, Treeroot);
    binary_search_tree_sort (root->prev, Treeroot);
}

void tree_zero (struct tree_t *Tree)
{
    if (Tree != NULL)
    {
        Tree->balance = 0;
        Tree->node = NULL;
    }
}

