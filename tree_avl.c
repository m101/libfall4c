void binary_search_tree_balance (struct  tree_t *root)
{
    struct  tree_t *balanced;
    
    // pointer check
    if (!root)
        return;

    balanced = root;

    if (balanced != NULL)
    {
        if (balanced->root)
        {
            if (root->comparator(balanced->root->next->data) > root->comparator(sorted->root->prev->data))
                binary_tree_rotate_right (balanced);
            else
                binary_tree_rotate_left (balanced);
        }
    }
}

struct tree_t* binary_tree_rotate_left (t_tree *A)
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

struct tree_t* binary_tree_rotate_right (t_tree *A)
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

struct tree_t* binary_tree_rotate_left_double (t_tree *A)
{
    if ( A != NULL )
        A->right = binary_tree_rotate_right (A->right);
    else
        fprintf(stderr, "Error: Tree branch is empty\n");

    return binary_tree_rotate_left (A);
}

struct tree_t* binary_tree_equilibrate(t_tree* A)
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

