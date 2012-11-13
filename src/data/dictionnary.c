#include <stdio.h>
#include <stdlib.h>

#include "string_ext.h"
#include "data/tree_avl.h"

int dict_comparator (void *data1, void *data2)
{
    struct dict_node_t *node1 = data1, *node2 = data2;

    if (!data1 || !data2) {
        fprintf (stderr, "error: dict_comparator(): Bad parameter(s)\n");
        return 0;
    }

    return node1->hash_key - node2->hash_key;
}

void dict_destroy_data (void **data)
{
    struct dict_node_t **node;

    if (!node || !*node) {
        fprintf (stderr, "error: dict_destroy_data(): Bad parameter(s)\n");
        return 0;
    }

    free ((*node)->key);
    free ((*node)->value);
    free (*node);
    *node = NULL;
}

size_t dict_get_data_size (void *data)
{
    return sizeof(struct dict_node_t);
}

struct dict_t *dict_set (struct dict_t **dict, char *key, char *value)
{
    struct dict_node_t *node;

    if (!dict) {
        fprintf (stderr, "error: dict_add(): Bad parameters\n");
        return NULL;
    }

    // alloc tree
    if (!*dict) {
        *dict = calloc (1, sizeof(*dict));
        if (!*dict) {
            fprintf (stderr, "error: dict_add(): Couldn't allocate dict\n");
            return NULL;
        }

        (*dict)->bst = calloc (1, sizeof(*(*dict)->bst));
        if (!(*dict)->bst) {
            fprintf (stderr, "error: dict_add(): Failed allocating bst tree\n");
            return NULL;
        }

        (*dict)->bst->comparator = dict_comparator;
        (*dict)->bst->destroy_data = dict_destroy_data;
        (*dict)->bst->get_data_size = dict_get_data_size;
    }

    node = calloc (1, sizeof(*node));
    if (!node) {
        fprintf (stderr, "error: dict_add(): Couldn't allocate node\n");
        return NULL;
    }

    // key
    node->key = strdup(key);
    node->sz_key = strlen(node->key);
    node->hash_key = fnv_hash (key, node->sz_key);
    // value
    node->value = strdup(value);
    node->sz_value = strlen(node->value);

    // add in tree
    avl_add (&((*dict)->bst), node);

    return *dict;
}

struct dict_t *dict_unset (struct dict_t **dict, char *key)
{
}

