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

#include "data/tree_avl.h"
#include "math/math_basic.h"

struct tree_node_t *_tree_rotate_left (struct tree_node_t **node)
{
    struct tree_node_t *new_root;

    if (!node || !*node) {
        fprintf(stderr, "error: _tree_rotate_left(): Tree branch is empty\n");
        return NULL;
    }

    new_root = (*node)->right;
    printf ("left new_root: %p\n", new_root);

    // update depth
    new_root->depth--;
    (*node)->depth++;

    // rotate left
    (*node)->right = new_root->left;
    new_root->left = *node;
    *node = new_root;

    return new_root;
}

struct tree_node_t *_tree_rotate_right (struct tree_node_t **node)
{
    struct tree_node_t *new_root;

    if (!node || !*node) {
        fprintf(stderr, "error: _tree_rotate_right(): Tree branch is empty\n");
        return NULL;
    }

    new_root = (*node)->left;

    // update depth
    new_root->depth--;
    (*node)->depth++;

    // rotate right
    printf ("right new_root: %p\n", new_root);
    (*node)->left = new_root->right;
    new_root->right = *node;
    *node = new_root;

    return new_root;
}

struct tree_node_t *_tree_rotate_left_double (struct tree_node_t **node)
{
    if (!node || !*node) {
        fprintf(stderr, "error: _tree_rotate_left_double(): tree branch is empty\n");
        return NULL;
    }

    (*node)->right = _tree_rotate_right (&((*node)->right));

    return _tree_rotate_left (node);
}

struct tree_node_t *_tree_rotate_right_double (struct tree_node_t **node)
{
    if (!node || !*node) {
        fprintf(stderr, "error: _tree_rotate_right_double(): tree branch is empty\n");
        return NULL;
    }

    (*node)->right = _tree_rotate_left (&((*node)->left));

    return _tree_rotate_right (node);
}

struct tree_node_t *_avl_tree_balance (struct tree_node_t **node)
{
    if ((*node)->balance < RIGHT_HEAVY) {
        if ((*node)->right && ((*node)->right->balance > LEFT_HEAVY))
            return _tree_rotate_left_double (node);
        else
            return _tree_rotate_left (node);
    }
    else if ((*node)->balance > LEFT_HEAVY) {
        if ((*node)->left && ((*node)->left->balance < RIGHT_HEAVY))
            return _tree_rotate_right_double (node);
        else
            return _tree_rotate_right (node);
    }

    return *node;
}

struct tree_node_t *_avl_add (struct tree_t *bst, struct tree_node_t **parent, struct tree_node_t **node, void *data, int depth)
{
    int check;

    // pointers check
    if (!bst || !node || !data) {
        fprintf (stderr, "error: _avl_add(): Bad parameters\n");
        return NULL;
    }

    // if we found a leaf
    // then we insert data
    if (!(*node)) {
        int left_depth, right_depth;
        struct tree_node_t *left, *right;

        *node = calloc (1, sizeof(**node));
        if (!*node) {
            fprintf (stderr, "error: _avl_add(): Failed allocating new node\n");
            return NULL;
        }
        (*node)->data = data;
        (*node)->depth = depth;

        printf ("child          : %p\n", *node);
        printf ("   depth = %d\n\n", depth);

        if (!parent) {
            fprintf (stderr, "info : _avl_add(): Parent is NULL\n");
            return *node;
        }

        // for lisibility
        left = (*parent)->left;
        right = (*parent)->right;
        // compute balance
        left_depth = (left ? left->depth : 0);
        right_depth = (right ? right->depth : 0);
        (*parent)->balance = left_depth - right_depth;
        // update depth of parent
        (*parent)->depth = max("%ld%ld", left_depth, right_depth) + 1;

        // balance tree
        _avl_tree_balance (parent);

        return *node;
    }

    // we don't check equality since we don't want dupes
    // if smaller
    // then we go left
    // check = bst->comparator((*node)->data, data);
    check = -1;
    printf ("check          : %d\n", check);
    if (parent)
        printf ("parent         : %p\n", *parent);
    else
        printf ("parent         : %p\n", parent);
    printf ("(*node)->left  : %p\n", (*node)->left);
    printf ("(*node)->right : %p\n", (*node)->right);
    if (check < 0)
        return _avl_add (bst, node, &((*node)->left), data, depth + 1);
    // if bigger
    // then we go right
    else if (check > 0)
        return _avl_add (bst, node, &((*node)->right), data, depth + 1);
    else
        (*node)->weight++;
}

struct tree_t *avl_add (struct tree_t **bst, void *data)
{
    struct tree_node_t *node;

    if (!bst) {
        fprintf (stderr, "error: avl_add(): Bad parameter\n");
        return NULL;
    }

    if (!*bst) {
        *bst = calloc (1, sizeof(*bst));
        if (!*bst) {
            fprintf (stderr, "error: avl_add(): Couldn't allocate bst\n");
            return NULL;
        }
    }

    node = _avl_add (*bst, NULL, &((*bst)->root), data, 0);

    return (node ? *bst : NULL);
}

struct tree_node_t *_avl_del (struct tree_t *bst, struct tree_node_t **parent, struct tree_node_t **node, void *data, int depth)
{
}

struct tree_t *avl_del (struct tree_t **bst, void *data)
{
    struct tree_node_t *node;

    if (!bst) {
        fprintf (stderr, "error: avl_add(): Bad parameter\n");
        return NULL;
    }

    if (!*bst) {
        *bst = calloc (1, sizeof(*bst));
        if (!*bst) {
            fprintf (stderr, "error: avl_add(): Couldn't allocate bst\n");
            return NULL;
        }
    }

    node = _avl_del (*bst, NULL, &((*bst)->root), data, 0);

    return (node ? *bst : NULL);
}

void _avl_show (struct tree_node_t *node)
{
    static int recsop=0; /* no of recs printed */

    if (!node) {
        fprintf (stderr, "error: _avl_show(): Bad parameter\n");
        return;
    }

    /* print left subtree */
    if(node->left)
        _avl_show (node->left);
    /* print data for current node */
    if (node->left)
        printf ("%p ", node->left->data);
    else
        printf("null    ");
    printf ("%p ", node->data);
    printf ("%d ", node->depth);
    recsop++;
    if (node->right)
        printf ("%p ", node->right->data);
    else
        printf("null    ");
    if (recsop % 4 == 0)
        printf("\n");
    else
        printf("    ");
    /* print right subtree */
    if(node->right)
        _avl_show(node->right);
}

void avl_show (struct tree_t *bst)
{
    if (!bst) {
        fprintf (stderr, "error: avl_show(): bst is null\n");
        return;
    }
    _avl_show (bst->root);
}
