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

#include "data/tree_binary.h"

/* @brief   Add node to tree
*/
struct tree_node_t *_bst_add (struct tree_t *bst, struct tree_node_t **node, void *data)
{
    int result;

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
    result = bst->comparator((*node)->data, data);
    if (result < 0)
        return _bst_add (bst, &((*node)->left), data);
    // if bigger
    // then we go right
    else if (result > 0)
        return _bst_add (bst, &((*node)->right), data);
    else
        (*node)->weight++;
}

/* @brief   Add data to tree
*/
struct tree_t *bst_add (struct tree_t *bst, void *data)
{
    // pointers check
    if (!bst || !data)
        return NULL;

    if (_bst_add (bst, &(bst->root), data))
       return bst;
    else
        return NULL;
}

/* @brief   Display whole tree
*/
struct tree_t *_bst_show (struct tree_t *bst, struct tree_node_t *node)
{
    if (!bst || !node)
        return NULL;

    _bst_show (bst, node->next);
    bst->show (node->data);
    _bst_show (bst, node->prev);

    return bst;
}

struct tree_t *bst_show (struct tree_t *bst)
{
    return _bst_show (bst, bst->root);
}

struct tree_t *_bst_sort (struct tree_t *bst, struct tree_node_t *node)
{
    /*
    struct tree_t *left_old = NULL, *right_old = NULL;

    // pointer check
    if (!bst || !node)
        return;

    _bst_sort (bst, node->prev);

    // 
    if ( node->left && node->right )
    {
        if ( node->comparator (node->left->data, node->right->data) < 0 )
        {
            right_old = node->right;
            node->right = node;
        }
    }

    _bst_sort (node->right);
    //*/
}

// AVL
struct tree_t *bst_sort (struct tree_t *bst)
{
    if (!bst)
        return NULL;
    return _bst_sort (bst, bst->root);
}

/*! @brief Recursive stub for binary tree searching
*/
struct tree_node_t *_bst_search (struct tree_t *bst, struct tree_node_t *node, void *data)
{
    int result;

    // key not found
    if (!bst || !node || !data)
        return NULL;

    result = bst->comparator (node->data, data);

    // if equal
    // then we found it
    if (result == 0)
        return node;
    // below
    else if (result < 0)
        return _bst_search (bst, node->left, data);
    // if upper
    else if (result > 0)
        return _bst_search (bst, node->right, data);
}

/*! @brief Search tree for specified data
*/
struct tree_t *bst_search (struct tree_t *bst, void *data)
{
    if (!bst || !data)
        return NULL;

    if (_bst_search (bst, bst->root, data))
        return bst;
    else
        return NULL;

    return 0;
}

struct tree_t *_tree_destroy_node (struct tree_t *bst, struct tree_node_t **node, void *data)
{
    int result;

    if (!bst ||  !node || !*node || !data)
        return NULL;

    result = bst->comparator((*node)->data, data);
    if (result == 0) {
        bst->destroy_data(&((*node)->data));
        free(*node);
        *node = NULL;
        /* TODO: Fix rotation and such (losing childrens)
        */
        return bst;
    }
    else if (result < 0)
        _tree_destroy_node (bst, &((*node)->left), data);
    else if (result > 0)
        _tree_destroy_node (bst, &((*node)->right), data);
}

struct tree_t *bst_del (struct tree_t *bst, void *data)
{
    if (!bst ||  !data)
        return -1;
    return _tree_destroy_node (bst, &(bst->root), data);
}

