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

#ifndef _TREE_AVL_H
#define _TREE_AVL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tree_common.h"

#define LEFT_HEAVY  1
#define RIGHT_HEAVY -1

struct tree_t *avl_add (struct tree_t **bst, void *data);
struct tree_t *avl_del (struct tree_t **bst, void *data);
void avl_show (struct tree_t *bst);

#ifdef __cplusplus
}
#endif

#endif /* _TREE_AVL_H */
