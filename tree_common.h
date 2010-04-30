#ifndef _TREE_COMMON_H_
#define _TREE_COMMON_H_

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
    size_t (*get_data_size)(void *data);
};

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

#endif /* _TREE_COMMON_H_ */

