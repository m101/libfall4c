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

#define TREE_BINARY
#define TREE_AVL    
#define TREE_RADBLACK
#define TREE_B      
#define TREE_BPLUS
#define TREE_SPLAY
#define TREE_AA
#define TREE_HEAP // TREAP

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

    // functions
    int (*comparator)(void *data1, void *data2);
    void (*destroy_data)(void *data);
    size_t (*get_data_size)(void *data);
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
            struct t_tree *left, *right;
        };
        struct 
        {
            struct t_tree *son, *brother;
        };
    };
};

// Create new tree
struct tree_t* tree_new (int (*comparator)(void *, void *), size_t (*get_data_size)(void *));
// Destroy tree
void tree_free (struct tree_t *root);
// Create a tree node
struct tree_node_t* tree_node_new (void);

#endif /* _TREE_COMMON_H_ */

