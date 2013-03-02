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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "data/data_ops.h"
#include "data/tree_common.h"

static const struct data_ops tree_data_ops = {
    .comparator = comparator_no_ops,
    .destroy = destroy_no_ops,
    .free = free_no_ops,
    .get_size = get_size_no_ops,
    .show = show_no_ops
};

// Create a tree node
struct tree_node_t* _tree_node_new (void);

/*  @brief  Create new tree
*/
struct tree_t *tree_new (void)
{
    struct tree_t *tree_table;

    tree_table = calloc (1, sizeof(*tree_table));
    assert (tree_table != NULL);
    tree_table->dops = calloc (1, sizeof(tree_data_ops));
    memcpy (tree_table->dops, &tree_data_ops, sizeof(tree_data_ops));

    return tree_table;
}

// recursively traverse nodes to free them
struct tree_t *_tree_free (struct tree_node_t **node, void (*fct_free)(void *data))
{
    if (!node || !*node)
        return NULL;

    _tree_free (&((*node)->left), fct_free);
    _tree_free (&((*node)->right), fct_free);
    if (fct_free)
        fct_free ((*node)->data);
    free (*node);
    *node = NULL;
}

/*!  @brief  Free tree
*/
struct tree_t *tree_free (struct tree_t *tree, void (*fct_free)(void *data))
{
    if (!tree)
        return NULL;
    if (!fct_free)
        return NULL;

    _tree_free (&(tree->root), fct_free);
    free (tree);
}

/*!  @brief  Destroy tree
*/
struct tree_t *_tree_destroy (struct tree_node_t **node, void (*fct_destroy)(void *data))
{
    if (!node || !*node)
        return NULL;

    _tree_destroy (&((*node)->left), fct_destroy);
    _tree_destroy (&((*node)->right), fct_destroy);
    if (fct_destroy)
        fct_destroy (&((*node)->data));
    free (*node);
    *node = NULL;
}

/*!  @brief  Destroy tree
*/
struct tree_t *tree_destroy (struct tree_t *tree, void (*fct_destroy)(void **data))
{
    if (!tree)
        return NULL;

    _tree_destroy (&(tree->root), fct_destroy);
    free (tree);
}

/*! @brief Create a tree node
 *
 */
struct tree_node_t* _tree_node_new (void)
{
    struct tree_node_t *node;

    node = calloc (1, sizeof(*node));

    return node;
}

int _bst_depth (struct tree_node_t *node, int depth)
{
    if (node == NULL)
        return depth;
    else
        return max ("%ld%ld", _bst_depth(node->left, depth + 1), _bst_depth(node->right, depth + 1));
}

int bst_depth (struct tree_t *bst)
{
    return _bst_depth (bst->root, 0);
}

