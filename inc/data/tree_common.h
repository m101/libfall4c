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

// callbacks ids
#define TREE_CALLBACK_MAX_NUM           16
#define TREE_CALLBACK_COMPARATOR        0
#define TREE_CALLBACK_DESTROY_DATA      1
#define TREE_CALLBACK_GET_DATA_SIZE     2

// generic tree structure
struct tree_t
{
    // root of the tree
    struct tree_node_t *root;
    // balance of the tree
    int balance;
    // height of the tree
    int height;
    // number of nodes
    size_t n;

    // callbacks
    uint64_t (*callbacks[TREE_CALLBACK_MAX_NUM]) (void *data1, void *data2);

    // functions
    int (*comparator)(void *data1, void *data2);
    void (*destroy_data)(void **data);
    size_t (*get_data_size)(void *data);
    // view functions
    void (*show)(void *data);
};

// node structure
struct tree_node_t
{
    void *data;
    int weight;
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
struct tree_t *tree_free (struct tree_t *tree);

// setters
struct tree_t *tree_set_callback (struct tree_t *tree, int id_callback, void (*callback)());
// comparator
void tree_set_comparator (int (*comparator)(void *, void *));
//
void tree_set_get_data_size (size_t (*get_data_size)(void *));
//
void tree_set_destroy (void (*destroy_data)(void *data));
//
void tree_set_show (void (*show)(void *data));

#ifdef __cplusplus
}
#endif

#endif /* _TREE_COMMON_H_ */

