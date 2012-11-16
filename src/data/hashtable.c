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

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "data/hashtable.h"
#include "data/tree_binary.h"

int hashtable_comparator (void *data1, void *data2)
{
    struct hashtable_node *node1 = data1, *node2 = data2;

    if (!data1 || !data2) {
        fprintf (stderr, "error: hashtable_comparator(): Bad parameter(s)\n");
        return data1 - data2;
    }

    return node1->hash_key - node2->hash_key;
}

// size of an associative array element
size_t hashtable_elt_size (void *elt)
{
    return sizeof(struct hashtable_node);
}

int _hashtable_init_callbacks (struct hashtable_t *htable)
{
    if (!htable || !htable->bst)
        return -1;

    tree_set_callback (htable->bst, TREE_CALLBACK_COMPARATOR, hashtable_comparator);
    tree_set_callback (htable->bst, TREE_CALLBACK_GET_DATA_SIZE, hashtable_elt_size);
    tree_set_callback (htable->bst, TREE_CALLBACK_DESTROY_DATA, hashtable_destroy);

    return 0;
}

struct hashtable_t *hashtable_new (void)
{
    int rc;
    struct hashtable_t *htable;

    htable = calloc (1, sizeof(*htable));
    if (!htable)
        return NULL;
    // htable->bst = tree_new (hashtable_comparator, hashtable_elt_size);
    htable->bst = tree_new ();

    rc = _hashtable_init_callbacks (htable);
    if (rc < 0) {
        hashtable_destroy(&htable);
        return NULL;
    }

    return htable;
}

void hashtable_node_destroy_data (void **data)
{
    struct hashtable_node **node;

    if (!node || !*node) {
        fprintf (stderr, "error: dict_destroy_data(): Bad parameter(s)\n");
        return;
    }

    free ((*node)->key);
    free ((*node)->value);
    free (*node);
    *node = NULL;
}

void _hashtable_node_free (void *data)
{
    hashtable_node_destroy_data (&data);
}

void hashtable_destroy (struct hashtable_t **htable)
{
    if (!htable || !*htable)
        return;

    tree_free((*htable)->bst, _hashtable_node_free);
    free(*htable);
    *htable = NULL;
}

// set a value
struct hashtable_t* hashtable_set_value (struct hashtable_t **htable, char *key, void *value)
{
    int rc;
    struct hashtable_node *elt;

    // pointer check
    if (!htable || !key || !value)
        return NULL;

    // create array if it doesn't exist
    if (!*htable) {
        *htable = hashtable_new();
        if (!*htable) {
            fprintf (stderr, "error: hashtable_set_value(): Couldn't allocate hashtable\n");
            return NULL;
        }
    }

    // create array element
    elt = calloc (1, sizeof(*elt));
    if (!elt)
        return NULL;
    // key
    elt->key = key;
    elt->sz_key = strlen (elt->key);
    elt->hash_key = fnv_hash (key, elt->sz_key);
    // value
    elt->value = value;
    elt->sz_value = strlen(elt->value);

    // add value in tree
    bst_add ((*htable)->bst, elt);

    return *htable;
}

// get a value
void *hashtable_get_value (struct hashtable_t *htable, char *key)
{
    int rc;
    struct tree_node_t *node;
    struct hashtable_node elt = { key, NULL }, *helt;

    // pointer check
    if (!htable || !key)
        return NULL;

    rc = _hashtable_init_callbacks (htable);
    if (rc < 0)
        return NULL;

    // search element in tree
    node = bst_search (htable->bst, &elt);
    if (!node)
        return NULL;

    // return found data
    helt = node->data;
    if (helt)
        return helt->value;
    else {
        // _tree_destroy_node(&node); // data is NULL so useless node
        return NULL;
    }
}

