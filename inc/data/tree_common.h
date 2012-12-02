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

#ifndef _TREE_COMMON_H_
#define _TREE_COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

// tree types to use
#define TREE_BINARY
#define TREE_AVL    
#define TREE_RADBLACK
#define TREE_B      
#define TREE_BPLUS
#define TREE_SPLAY
#define TREE_AA
#define TREE_HEAP // TREAP

#define tree_set_callback(bst, name, callback)  bst->name = callback

// generic tree structure
struct tree_t
{
    // root of the tree
    struct tree_node_t *root;
    // number of nodes
    size_t n;

    // methods
    int (*comparator)(void *data1, void *data2);
    void (*destroy_data)(void **data);
    size_t (*get_data_size)(void *data);
    void (*show)(void *data);
};

// node structure
struct tree_node_t
{
    void *data;
    int weight;
    // balance of the subtree
    int balance;
    // depth at which the node is located
    int depth;
    //
    union
    {
        struct
        {
            struct tree_node_t *left, *right;
        };
        struct
        {
            struct tree_node_t *prev, *next;
        };
        struct 
        {
            struct tree_node_t *son, *brother;
        };
    };
};

// Create new tree
struct tree_t *tree_new (void);
// Destroy tree
struct tree_t *tree_free (struct tree_t *tree, void (*fct_free)(void *data));
// recursively compute height
int bst_depth (struct tree_t *bst);

#ifdef __cplusplus
}
#endif

#endif /* _TREE_COMMON_H_ */

