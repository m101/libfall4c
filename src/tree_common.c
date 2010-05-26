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

#include "tree_common.h"

/*  @brief  Create new tree
*/
struct tree_t* tree_new (int (*comparator)(void *, void *), size_t (*get_data_size)(void *))
{
    struct tree_t *tree_table;

    tree_table = calloc (1, sizeof(*tree_table));
    assert (tree_table != NULL);
    tree_table->root = calloc (1, sizeof(*(tree_table->root)));
    tree_table->comparator = comparator;
    tree_table->get_data_size = get_data_size;
}

/*!  @brief  Destroy tree
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

/*! @brief Create a tree node
 *
 */
struct tree_node_t* tree_node_new (void) {
    struct tree_node_t *node;

    node = calloc (1, sizeof(*node));

    return node;
}
