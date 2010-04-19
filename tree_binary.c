#include <stdio.h>
#include <stdlib.h>

#include "tree_tes_doubles.h"
#include "arbres_binaires.h"
#include "pathfinding.h"
#include "math_basic.h"

struct tree_t* binary_search_tree_add (struct tree_t *node, void *data)
{
    if (node == NULL)
    {
        node = calloc (1, sizeof(*node));
        node->data = data;
    }
    // if smaller
    // then we go left
    else if (node->comparator(node->data, data) <= 0)
        node->prev = binary_search_tree_add (node->left, data);
    // if bigger
    // then we go right
    else if (node->comparator(node->data, data) > 0)
        node->next = binary_search_tree_add (node->right, data);

    return node;
}


void binary_tree_display (struct tree_t *root)
{
    if (root != NULL)
    {
        binary_tree_display (root->next);
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display (root->prev);
    }
}

void binary_tree_display_right (struct tree_t *root)
{
    if (root != NULL)
    {
        // binary_tree_display_right (root->prev);
        printf("%4ld\n", *(long *)root->data);
        binary_tree_display_right (root->prev);
    }
}


// AVL

void binary_search_tree_sort (struct tree_t *root, struct t_path_node *Treeroot)
{
    t_double_linked_tree_t *tree_tTemp = NULL;

    if ( ((struct t_path_node *)(root->data))->cost < Treeroot->cost )
    {
        tree_tTemp = root->prev;
        root->prev = root;
    }

    binary_search_tree_sort (root->prev, Treeroot);
    binary_search_tree_sort (root->prev, Treeroot);
}

t_tree* binary_tree_rotate_left (t_tree *A)
{
    t_tree *B = NULL;
    int a = 0, b = 0;

    if ( A != NULL )
    {
        // Rotate left
        // B = A->right branch
        B = A->right;
        // A->left branch = A->right->left branch
        A->right = B->left;
        // A->right->left branch = A branch
        B->left = A;
        // Balance
        a = A->balance;
        b = B->balance;
        A->balance = a - max ("%ld%ld", b, 0) - 1;
        B->balance = min ("%ld%ld%ld", a - 2, a + b - 2, b - 1);
    }
    else
        fprintf(stderr, "Error: Tree branch is empty\n");

    return B;
}

t_tree* binary_tree_rotate_right (t_tree *A)
{
    t_tree *B = NULL;
    int a = 0, b = 0;

    if ( B != NULL )
    {
        // Rotate right
        // B = A->left branch
        B = A->left;
        // A->left branch = B->left->right branch
        A->left = B->right;
        // B->left->right branch = A branch
        B->right = A;
        // Balance
        a = A->balance;
        b = B->balance;
        A->balance = a - min ("%ld%ld", b, 0) + 1;
        B->balance = max ("%ld%ld%ld", a + 2, a + b + 2, b + 1);
    }
    else
        fprintf(stderr, "Error: Tree branch is empty\n");

    return B;
}

t_tree* binary_tree_rotate_left_double (t_tree *A)
{
    if ( A != NULL )
        A->right = binary_tree_rotate_right (A->right);
    else
        fprintf(stderr, "Error: Tree branch is empty\n");

    return binary_tree_rotate_left (A);
}

t_tree* binary_tree_equilibrate(t_tree* A)
{
    if (A->balance == 2)
    {
        if (A->right->balance >= 0)
            return binary_tree_rotate_left(A);
        else
        {
            A->right = binary_tree_rotate_right(A->right);
            return binary_tree_rotate_left(A);
        }
    }
    else if (A->balance == -2)
    {
        if (A->left->balance <= 0)
            return binary_tree_rotate_right(A);
        else
        {
            A->left = binary_tree_rotate_left(A->left);
            return binary_tree_rotate_right(A);
        }
    }
    else
        return A;
}

t_tree* binary_tree_add (t_tree* root, t_tree* Node, int h, int (*f)(void *) )
{
    int x = f(root), y = f(Node);

    if (root == NULL)
    {
        //creer un nœud root;
        root = malloc(sizeof(t_tree));
        root->left = NULL;
        root->right = NULL;
        root->elt = x;
        root->balance = 0;
        root->h = 1;
        return root;
    }
    else if ( x == y )
    {
        root->h = 0;
        return root;
    }
    else if ( x > y )
    {
        root->right = binary_tree_add(Node, root->right, h, f);
    }
    else
    {
        root->left = binary_tree_add(Node, root->left, h, f);
        h = -h;
    }

    if (h == 0)
    {
        root->h = 0;
        return root;
    }
    else
    {
        root->balance = root->balance + h;
        root = binary_tree_equilibrate(root);
    }
    if (root->balance == 0)
    {
        root->h = 0;
        return root;
    }
    else
    {
        root->h = 1;
        return root;
    }

    return root;
}

void tree_zero (t_tree *Tree)
{
    if (Tree != NULL)
    {
        Tree->balance = 0;
        Tree->node = NULL;
    }
}

void binary_tree_sort (t_double_linked_tree_t *Node)
{
    t_tree Tree;

    tree_zero(&Tree);

    Tree.node = Node;

    if (Tree.node != NULL)
    {
        if (Tree.node->next->data > Tree.node->prev->data)
            binary_tree_rotate_right (&Tree);
        else
            binary_tree_rotate_left (&Tree);
    }
}


