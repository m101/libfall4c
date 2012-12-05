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
        bst->size++;
        return *node;
    }

    // we don't check equality since we don't want dupes
    // if smaller
    // then we go left
    result = bst->dops->comparator((*node)->data, data);
    if (result < 0)
        return _bst_add (bst, &((*node)->left), data);
    // if bigger
    // then we go right
    else if (result > 0)
        return _bst_add (bst, &((*node)->right), data);
    else {
        (*node)->weight++;
        return *node;
    }
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
    bst->dops->show (node->data);
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

    result = bst->dops->comparator (node->data, data);

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
void *bst_search (struct tree_t *bst, void *data)
{
    struct tree_node_t *node;

    if (!bst || !data)
        return NULL;

    node = _bst_search (bst, bst->root, data);
    if (node)
        return node->data;

    return NULL;
}

struct tree_t *_bst_destroy_node (struct tree_t *bst, struct tree_node_t **node)
{
    int result;

    if (!bst || !node || !*node)
        return NULL;

    bst->dops->destroy (&((*node)->data));
    free(*node);
    *node = NULL;

    return bst;
}

/*! @brief Recursive stub for binary tree deletion
*/
struct tree_node_t *_bst_del (struct tree_t *bst, struct tree_node_t **node, void *data)
{
    int result;
    struct tree_node_t *node_holder;
    void *data_holder;

    // key not found
    if (!bst || !node || !*node || !data)
        return NULL;

    result = bst->dops->comparator ((*node)->data, data);

    // if below
    if (result < 0)
        _bst_del (bst, &((*node)->left), data);
    // if upper
    else if (result > 0)
        _bst_del (bst, &((*node)->right), data);

    // if equal
    // then we found the node to delete

    // if leaf
    if ((*node)->left == NULL && (*node)->right == NULL) {
        _bst_destroy_node (bst, node);

        return bst;
    }
    // if only right node
    else if ((*node)->left == NULL && (*node)->right) {
        node_holder = (*node)->right;
        _bst_destroy_node (bst, node);
        *node = node_holder;

        return node_holder;
    }
    // if only left node
    else if ((*node)->left && (*node)->right == NULL) {
        node_holder = (*node)->left;
        _bst_destroy_node (bst, node);
        *node = node_holder;

        return node_holder;
    }
    // if both nodes
    else {
        // we search for the left most node in our right subtree
        node_holder = (*node)->right;
        while (node_holder->left)
            node_holder = node_holder->left;

        // swap data pointers
        data_holder = (*node)->data;
        (*node)->data = node_holder->data;
        node_holder->data = data_holder;
        // remove node
        _bst_del (bst, &node_holder, node_holder->data);
    }
}

struct tree_t *bst_del (struct tree_t *bst, void *data)
{
    if (!bst ||  !data)
        return -1;
    return _bst_del (bst, &(bst->root), data);
}

/*! @brief Recursive stub for binary tree walking
*/
struct tree_node_t *_bst_walk (struct tree_t *bst, struct tree_node_t *node, void *(*action) (void *data))
{
    int result;

    // key not found
    if (!bst || !node || !action)
        return NULL;

    _bst_walk (bst, node->left, action);
    action (node->data);
    _bst_walk (bst, node->right, action);

    return node;
}

struct tree_t *bst_walk (struct tree_t *bst, void *(*action) (void *data))
{
    struct tree_node_t *node;

    if (!bst || !action) {
        fprintf (stderr, "error: bst_walk(): Bad parameter(s)\n");
        return NULL;
    }

    node = _bst_walk (bst, bst->root, action);

    return (node ? bst : NULL);
}

