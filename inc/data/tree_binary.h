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
struct tree_t *bst_add (struct tree_t *bst, void *data);
// struct tree_t *bst_sort (struct tree_t *bst);
// Search tree for specified data
struct tree_t *bst_search (struct tree_t *bst, void *data);
struct tree_t *bst_del (struct tree_t *bst, void *data);

#ifdef __cplusplus
}
#endif

#endif /* _TREE_BINARY_H_ */

