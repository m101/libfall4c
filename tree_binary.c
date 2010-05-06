#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "tree_binary.h"


/* @brief   Add data to tree
 */
struct tree_t* binary_search_tree_add (struct tree_t *root, void *data)
{
    // pointers check
    if (!root || !data)
        return NULL;
    binary_search_tree_add_node (&(root->root), data);
}

/* @brief   Add node to tree
 */
struct tree_node_t* binary_search_tree_add_node (struct tree_node_t **node, void *data)
{
    // pointers check
    if (!data || !node)
        return NULL;
    if (!*node)
    {
        *node = calloc (1, sizeof(*node));
        (*node)->data = data;
        return *node;
    }
    // we don't check equality since we don't want dupes
    // if smaller
    // then we go left
    else if ((*node)->comparator((*node)->data, data) < 0)
        return binary_search_tree_add (&((*node)->left), data);
    // if bigger
    // then we go right
    else if ((*node)->comparator((*node)->data, data) > 0)
        return (*node)->right = binary_search_tree_add (&((*node)->right), data);
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

/* @brief   Display right children
 */
void binary_search_tree_display_right (struct tree_t *root)
{
    if (root != NULL)
    {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_right (root->prev);
    }
}

/* @brief   Display right children
 */
void binary_search_tree_display_left (struct tree_t *root)
{
    if (root != NULL)
    {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_left (root->prev);
    }
}



// AVL
void binary_search_tree_sort (struct tree_t *root)
{
    if (root)
        binary_search_sort_stub (root->root);
}

void binary_search_tree_sort_stub (struct tree_node_t *node)
{
    struct tree_t *leftOld = NULL, *rightOld = NULL;

    // pointer check
    if (!node)
        return;

    binary_search_tree_sort (node->prev);

    // 
    if ( node->left && node->right )
    {
        if ( node->comparator (node->left->data, node->right->data) < 0 )
        {
            rightOld = node->right;
            node->right = node;
        }
    }

    binary_search_tree_sort (node->right);
}

void tree_zero (struct tree_t *root)
{
    if (root != NULL)
        memset (root, sizeof(*root), 0);
}

