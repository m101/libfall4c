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

#ifndef _TREE_BINARY_H_
#define _TREE_BINARY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>             /* pour size_t */

#include "tree_common.h"

// Add data to tree
struct tree_t* binary_search_tree_add (struct tree_t *bst, void *data);
// Search tree for specified data
struct tree_node_t* binary_search_tree_search (struct tree_t *bst, void *data);

// View component
// Display whole tree
void binary_tree_display (struct tree_t *bst);
void binary_tree_display_right (struct tree_t *bst);
void binary_tree_display_left (struct tree_t *bst);

#ifdef __cplusplus
}
#endif

#endif /* _TREE_BINARY_H_ */

