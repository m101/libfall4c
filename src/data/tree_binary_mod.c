/*
    This file is part of fall4c.

    fall4c is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fall4c is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with fall4c.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "data/tree_binary.h"


/* @brief   Add data to tree
*/
struct tree_t* bst_add (struct tree_t *bst, void *data)
{
    // pointers check
    if (!bst || !data)
        return NULL;
    return bst_add_stub (bst, &(bst->root), data);
}

/* @brief   Add node to tree
*/
struct tree_node_t* bst_add_stub (struct tree_t *bst, struct tree_node_t **node, void *data)
{
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
    else {
        // we don't check equality since we don't want dupes
        // if smaller
        // then we go left
        else if (bst->comparator(data, (*node)->data) < 0)
            return bst_add_stub (bst, &((*node)->left), data);
        // if bigger
        // then we go right
        else if (bst->comparator(data, (*node)->data) > 0)
            return bst_add_stub (bst, &((*node)->right), data);
        else
            (*node)->weight++;
    }
}

/* @brief   Display whole tree
*/
void bst_display (struct tree_t *root)
{
    if (root != NULL) {
        binary_tree_display (root->next);
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display (root->prev);
    }
}

/* @brief   Display right children
*/
void bst_display_right (struct tree_t *root)
{
    if (root != NULL) {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_right (root->prev);
    }
}

/* @brief   Display right children
*/
void bst_display_left (struct tree_t *root)
{
    if (root != NULL) {
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_left (root->prev);
    }
}

// AVL
void bst_sort (struct tree_t *bst)
{
    if (bst)
        binary_search_sort_stub (bst, bst->root);
}

void bst_sort_stub (struct tree_t *bst, struct tree_node_t *node)
{
    struct tree_t *leftOld = NULL, *rightOld = NULL;

    // pointer check
    if (!bst || !node)
        return;

    bst_sort_stub (node->prev);

    // 
    if ( node->left && node->right )
    {
        if ( node->comparator (node->left->data, node->right->data) < 0 )
        {
            rightOld = node->right;
            node->right = node;
        }
    }

    bst_sort_stub (node->right);
}

/*! @brief Recursive stub for binary tree searching
*/
struct tree_node_t* bst_search_stub (struct tree_t *bst, struct tree_node_t *node, void *data)
{
    // key not found
    if (!bst || !node || !data)
        return NULL;
    // below
    if (bst->comparator (data, node->data) < 0)
        return bst_search_stub (bst, node->left, data);
    // if upper
    else if(bst->comparator (data, node->data) > 0)
        return bst_search_stub (bst, node->right, data);
    // if equal
    // then we found it
    else 
        return node;
}

/*! @brief Search tree for specified data
*/
struct tree_node_t* bst_search (struct tree_t *bst, void *data)
{
    if (!bst || !data)
        return NULL;

    return bst_search_stub (bst, bst->root, data);
}

struct tree_node_t* tree_delete_node (struct tree_t *bst, struct tree_node_t **node)
{
    struct tree_node_t *pNode;

    if (!bst || !node)
        return NULL;
    if (!*node)
        return NULL;
    // no children
    if ((*node)->left == NULL && (*node)->right == NULL)
        tree_node_free (*node);
    // one child
    else if ((*node)->left || (*node)->right) {
        if ((*node)->left)
            pNode = (*node)->left;
        else if ((*node)->right)
            pNode = (*node)->right;
        bst->destroy_data((*node)->data);
        free(*node);
        *node = pNode;
    }
    // two children
    else if ((*node)->left && (*node)->right) {
    }
}

