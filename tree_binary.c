#include <stdio.h>
#include <stdlib.h>

#include "listes_doubles.h"
#include "arbres_binaires.h"
#include "pathfinding.h"
#include "math_basic.h"

struct List* binary_search_tree_add (struct List *node, long integer)
{
    if (node == NULL)
    {
        node = list_new();
        node->data = double_linked_list_data_new(sizeof(long));
        *(long *)node->data = integer;
    }
    // Si c'est plus petit
    // Alors ca va a gauche
    else if (*(long *)node->data < integer)
        node->prev = binary_search_tree_add (node->prev, integer);
    // Si c'est plus grand
    // Alors ca va a droite
    else if (*(long *)node->data > integer)
        node->next = binary_search_tree_add (node->next, integer);

    return node;
}

struct List* binary_search_tree_add_path (struct List *node,
                    struct t_path_node *pathNode)
{
    long costStored = 0;
    long costToStore = 0;
    t_position Position = {0, 0};

    if (pathNode != NULL)
    {
        Position.x = pathNode->Position.x;
        Position.y = pathNode->Position.y;
    }

    if ( (node == NULL) && (pathNode != NULL) )
    {
        node = list_new();
        node->data = double_linked_list_data_new(sizeof(struct t_path_node));
        path_node_zero(node->data);
        // Les coûts
        ((struct t_path_node *)(node->data))->cost = pathNode->cost;
        ((struct t_path_node *)(node->data))->costFromStart = pathNode->costFromStart;
        ((struct t_path_node *)(node->data))->costToGoal_heuristic = pathNode->costToGoal_heuristic;
        ((struct t_path_node *)(node->data))->costNode = pathNode->costNode;
        // Position
        ((struct t_path_node *)(node->data))->Position.x = Position.x;
        ((struct t_path_node *)(node->data))->Position.y = Position.y;

#ifdef DEBUG
        printf("Allocated arbre\n");
        printf("((struct t_path_node *)(node->data))->cost : %ld\n", ((struct t_path_node *)(node->data))->cost);
        printf("((struct t_path_node *)(node->data))->costFromStart : %ld\n", ((struct t_path_node *)(node->data))->costFromStart);
        printf("((struct t_path_node *)(node->data))->costToGoal_heuristic : %ld\n", ((struct t_path_node *)(node->data))->costToGoal_heuristic);
        printf("((struct t_path_node *)(node->data))->costNode : %ld\n", ((struct t_path_node *)(node->data))->costNode);
        printf("((struct t_path_node *)(node->data))->Position.x : %ld\n", ((struct t_path_node *)(node->data))->Position.x);
        printf("((struct t_path_node *)(node->data))->Position.y : %ld\n\n", ((struct t_path_node *)(node->data))->Position.y);
#endif

    }
    // Si on a déjà la point dans l'arbre
    // Alors on regarde si le coût est inférieur
    else if ( (Position.x == ((struct t_path_node *)(node->data))->Position.x)
              && (Position.y == ((struct t_path_node *)(node->data))->Position.y) )
    {
        if ( pathNode->cost < ((struct t_path_node *)(node->data))->cost )
        {
            // Les coûts
            ((struct t_path_node *)(node->data))->cost = pathNode->cost;
            ((struct t_path_node *)(node->data))->costFromStart = pathNode->costFromStart;
            ((struct t_path_node *)(node->data))->costToGoal_heuristic = pathNode->costToGoal_heuristic;
            ((struct t_path_node *)(node->data))->costNode = pathNode->costNode;
        }
    }
    // Si c'est plus petit
    // Alors ca va a droite
    else if ( (costStored = ((struct t_path_node *)(node->data))->cost)
              < (costToStore = pathNode->cost) )
        node->next = binary_search_tree_add_path (node->next, pathNode);
    // Si c'est plus grand
    // Alors ca va a gauche
    else if (costStored > costToStore)
        node->prev = binary_search_tree_add_path (node->prev, pathNode);

    return node;
}

struct List* binary_search_tree_search_lowestCostNode (struct List *Root)
{
    t_double_linked_list *lowestCostNode = NULL;

    while (Root != NULL)
    {
        lowestCostNode = Root;
        Root = Root->prev;
    }

    return lowestCostNode;
}

void binary_search_tree_search_isOpen (struct List *Root, struct t_path_node *Node)
{
    while (Root != NULL)
    {
        if ( ((struct t_path_node *)(Root->data))->Position.x == Node->Position.x
                && ((struct t_path_node *)(Root->data))->Position.y == Node->Position.y )
        {
            Node->isOpen = 1;
            break;
        }

        Root = Root->next;
    }
}

void binary_search_tree_search_isClose (struct List *Root, struct t_path_node *Node)
{
    while (Root != NULL)
    {
        if ( ((struct t_path_node *)(Root->data))->Position.x == Node->Position.x
                && ((struct t_path_node *)(Root->data))->Position.y == Node->Position.y )
        {
            Node->isOpen = 0;
            break;
        }

        Root = Root->prev;
    }
}

void binary_tree_display (struct List *racine)
{
    if (racine != NULL)
    {
        binary_tree_display (racine->next);
        printf("%4ld\n", *(long *)racine->data);
        binary_tree_display (racine->prev);
    }
}

void binary_tree_display_right (struct List *racine)
{
    if (racine != NULL)
    {
        // binary_tree_display_right (racine->prev);
        printf("%4ld\n", *(long *)racine->data);
        binary_tree_display_right (racine->prev);
    }
}

void binary_tree_display_path (struct List *racine)
{
    if (racine != NULL)
    {
        // binary_tree_display_right (racine->prev);
        printf("x : %3ld, y : %3ld\n", ((struct t_path_node *)(racine->data))->Position.x, ((struct t_path_node *)(racine->data))->Position.y);
        binary_tree_display_path (racine->prev);
    }
}

// AVL

void binary_search_tree_sort (struct List *Root, struct t_path_node *TreeRoot)
{
    t_double_linked_list *listTemp = NULL;

    if ( ((struct t_path_node *)(Root->data))->cost < TreeRoot->cost )
    {
        listTemp = Root->prev;
        Root->prev = Root;
    }

    binary_search_tree_sort (Root->prev, TreeRoot);
    binary_search_tree_sort (Root->prev, TreeRoot);
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

t_tree* binary_tree_add (t_tree* Root, t_tree* Node, int h, int (*f)(void *) )
{
    int x = f(Root), y = f(Node);

    if (Root == NULL)
    {
        //creer un nœud Root;
        Root = malloc(sizeof(t_tree));
        Root->left = NULL;
        Root->right = NULL;
        Root->elt = x;
        Root->balance = 0;
        Root->h = 1;
        return Root;
    }
    else if ( x == y )
    {
        Root->h = 0;
        return Root;
    }
    else if ( x > y )
    {
        Root->right = binary_tree_add(Node, Root->right, h, f);
    }
    else
    {
        Root->left = binary_tree_add(Node, Root->left, h, f);
        h = -h;
    }

    if (h == 0)
    {
        Root->h = 0;
        return Root;
    }
    else
    {
        Root->balance = Root->balance + h;
        Root = binary_tree_equilibrate(Root);
    }
    if (Root->balance == 0)
    {
        Root->h = 0;
        return Root;
    }
    else
    {
        Root->h = 1;
        return Root;
    }

    return Root;
}

void tree_zero (t_tree *Tree)
{
    if (Tree != NULL)
    {
        Tree->balance = 0;
        Tree->node = NULL;
    }
}

void binary_tree_sort (t_double_linked_list *Node)
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
