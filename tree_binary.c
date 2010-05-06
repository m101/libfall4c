#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "tree_binary.h"


/* @brief   Add data to tree
 */
struct tree_t* binary_search_tree_add (struct tree_t *bst, void *data) {
    // pointers check
    if (!bst || !data)
        return NULL;
    binary_search_tree_add_node (bst, &(bst->root), data);
}

/* @brief   Add node to tree
 */
struct tree_node_t* binary_search_tree_add_stub (struct tree_t *bst, struct tree_node_t **node, void *data) {
    // pointers check
    if (!bst || !data || !node)
        return NULL;
    // if we found a leaf
    // then we insert data
    if (!(*node)) {
        *node = calloc (1, sizeof(**node));
        (*node)->data = data;
        return *node;
    }
    // we don't check equality since we don't want dupes
    // if smaller
    // then we go left
    else if (bst->comparator(data, (*node)->data) < 0)
        return binary_search_tree_add_stub (bst, &((*node)->left), data);
    // if bigger
    // then we go right
    else if (bst->comparator(data, (*node)->data) > 0)
        return binary_search_tree_add_stub (bst, &((*node)->right), data);
}

/* @brief   Display whole tree
 */
void binary_search_tree_display (struct tree_t *root) {
    if (root != NULL)
    {
        binary_tree_display (root->next);
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display (root->prev);
    }
}

/* @brief   Display right children
 */
void binary_search_tree_display_right (struct tree_t *root) {
    if (root != NULL)
    {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_right (root->prev);
    }
}

/* @brief   Display right children
 */
void binary_search_tree_display_left (struct tree_t *root) {
    if (root != NULL)
    {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_left (root->prev);
    }
}



// AVL
void binary_search_tree_sort (struct tree_t *bst) {
    if (bst)
        binary_search_sort_stub (bst, bst->root);
}

void binary_search_tree_sort_stub (struct tree_t *bst, struct tree_node_t *node) {
    struct tree_t *leftOld = NULL, *rightOld = NULL;

    // pointer check
    if (!bst || !node)
        return;

    binary_search_tree_sort_stub (node->prev);

    // 
    if ( node->left && node->right )
    {
        if ( node->comparator (node->left->data, node->right->data) < 0 )
        {
            rightOld = node->right;
            node->right = node;
        }
    }

    binary_search_tree_sort_stub (node->right);
}

/*! @brief Recursive stub for binary tree searching
 */
struct tree_node_t* binary_search_tree_search_stub (struct tree_t *bst, struct tree_node_t *node,
                                                    void *data) {
    // key not found
    if (!bst || !node || !data)
        return NULL;
    // below
    if (bst->comparator (data, node->data) < 0)
        return binary_search_tree_search (bst, node->left, data);
    // if upper
    else if(bst->comparator (data, node->data) > 0)
        return binary_search_tree_search (bst, node->right, data);
    // if equal
    // then we found it
    else 
        return node;
}

/*! @brief Search tree for specified data
 */
struct tree_node_t* binary_search_tree_search (struct tree_t *bst, void *data) {
    if (!bst || !data)
        return NULL;

    return binary_search_tree_search_stub (bst, bst->root, data);
}


void tree_zero (struct tree_t *root)
{
    if (root != NULL)
        memset (root, sizeof(*root), 0);
}

