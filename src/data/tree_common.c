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

#include <assert.h>

#include "data/tree_common.h"

// Create a tree node
struct tree_node_t* _tree_node_new (void);

int _tree_default_comparator (void *data1, void *data2)
{
    return 0;
}

int _tree_default_destroy_data (void **data)
{
    return 0;
}

int _tree_default_get_data_size (void *data)
{
    return 0;
}

struct tree_t *_tree_init_callbacks (struct tree_t *tree)
{
    tree_set_callback (tree, comparator, _tree_default_comparator);
    tree_set_callback (tree, destroy_data, _tree_default_destroy_data);
    tree_set_callback (tree, get_data_size, _tree_default_get_data_size);

    return 0;
}

/*  @brief  Create new tree
*/
struct tree_t* tree_new (void)
{
    struct tree_t *tree_table;

    tree_table = calloc (1, sizeof(*tree_table));
    assert (tree_table != NULL);
    _tree_init_callbacks (tree_table);

    return tree_table;
}

/*!  @brief Add new callback using an id
 */
struct tree_t* tree_add_callback_from_id (int id, void (*callback)(void *, void *))
{
}


/*!  @brief Add new callback using a callback name
 */
struct tree_t* tree_add_callback_from_name (char *name, void (*callback)(void *, void *))
{
}

// recursively traverse nodes to free them
struct tree_t *_tree_free (struct tree_node_t *node, void (*fct_free)(void *data))
{
    if (!node)
        return NULL;

    _tree_free (node->left, fct_free);
    _tree_free (node->right, fct_free);
    free (node);
    if (fct_free)
        fct_free (node->data);
}

/*!  @brief  Destroy tree
*/
struct tree_t *tree_free (struct tree_t *tree, void (*fct_free)(void *data))
{
    if (!tree)
        return NULL;

    _tree_free (tree->root, fct_free);
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

