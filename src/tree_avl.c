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

#include <tree_avl.h>

void avl_tree_balance (struct tree_t *root)
{
    struct tree_t *balanced;
    
    // pointer check
    if (!root)
        return;

    balanced = root;

    if (balanced != NULL)
    {
        if (balanced->root)
        {
            if (root->comparator(balanced->root->next->data) > root->comparator(sorted->root->prev->data))
                avl_tree_rotate_right (balanced);
            else
                avl_tree_rotate_left (balanced);
        }
    }
}

struct tree_t* avl_tree_rotate_left (struct tree_t *A)
{
    struct tree_t *B = NULL;
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

struct tree_t* avl_tree_rotate_right (struct tree_t *A)
{
    struct tree_t *B = NULL;
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

struct tree_t* avl_tree_rotate_left_double (struct tree_t *A)
{
    if ( A != NULL )
        A->right = avl_tree_rotate_right (A->right);
    else
        fprintf(stderr, "Error: Tree branch is empty\n");

    return avl_tree_rotate_left (A);
}

struct tree_t* avl_tree_equilibrate(struct tree_t* A)
{
    if (A->balance == 2)
    {
        if (A->right->balance >= 0)
            return avl_tree_rotate_left(A);
        else
        {
            A->right = avl_tree_rotate_right(A->right);
            return avl_tree_rotate_left(A);
        }
    }
    else if (A->balance == -2)
    {
        if (A->left->balance <= 0)
            return avl_tree_rotate_right(A);
        else
        {
            A->left = avl_tree_rotate_left(A->left);
            return avl_tree_rotate_right(A);
        }
    }
    else
        return A;
}

struct tree_t* avl_tree_add (struct tree_t* root, struct tree_t* Node, int h, int (*f)(void *) )
{
    int x = f(root), y = f(Node);

    if (root == NULL)
    {
        //creer un nœud root;
        root = malloc(sizeof(struct tree_t));
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
        root->right = avl_tree_add(Node, root->right, h, f);
    }
    else
    {
        root->left = avl_tree_add(Node, root->left, h, f);
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
        root = avl_tree_equilibrate(root);
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

