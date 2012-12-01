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
#include "data/list.h"
#include "data/tree_binary.h"
#include "string_ext.h"

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

int _hashtable_init_callbacks (struct tree_t *bst)
{
    if (!bst)
        return -1;

    tree_set_callback (bst, comparator, hashtable_comparator);
    tree_set_callback (bst, get_data_size, hashtable_elt_size);
    tree_set_callback (bst, destroy_data, hashtable_destroy);

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

    // values and keys callbacks
    htable->keys = tree_new();
    tree_set_callback (htable->keys, comparator, string_cmp);
    htable->values = tree_new();
    tree_set_callback (htable->values, comparator, string_cmp);

    rc = _hashtable_init_callbacks (htable->bst);
    if (rc < 0) {
        hashtable_destroy(&htable);
        return NULL;
    }

    return htable;
}

void hashtable_node_destroy_data (void **data)
{
    struct hashtable_node **node;

    node = data;
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
    struct hashtable_node *elt;
    struct string_t *s_key;

    // pointer check
    if (!htable || !key || !value)
        return NULL;

    // create array if it doesn't exist
    if (!*htable)
        *htable = hashtable_new();

    // create array element
    elt = calloc (1, sizeof(*elt));
    if (!elt)
        return NULL;
    // key
    elt->key = strdup(key);
    elt->sz_key = strlen (key);
    elt->hash_key = fnv_hash (key, elt->sz_key);
    // value
    elt->value = value;
    
    // keep track of keys and values
    string_set (&s_key, key);
    (*htable)->keys = tree_new();
    bst_add ((*htable)->keys, s_key);
    // bst_add (&((*htable)->values), value);

    // add value in tree
    bst_add ((*htable)->bst, elt);

    return *htable;
}

// get a value
void *hashtable_get_value (struct hashtable_t *htable, char *key)
{
    int rc;
    struct hashtable_node elt, *helt;

    // pointer check
    if (!htable || !key)
        return NULL;

    rc = _hashtable_init_callbacks (htable->bst);
    if (rc < 0)
        return NULL;

    // search element in tree
    elt.hash_key = fnv_hash (key, strlen(key));
    helt = bst_search (htable->bst, &elt);
    if (!helt)
        return NULL;

    return helt->value;
}

void *_hashtable_get_keys (struct tree_t *bst, struct tree_node_t *node, struct list_simple **keys)
{
    struct hashtable_node *hnode;

    // key not found
    if (!bst || !node || !keys)
        return NULL;

    _hashtable_get_keys (bst, node->left, keys);
    hnode = node->data;
    if (hnode)
        list_append_data (keys, hnode->key);
    _hashtable_get_keys (bst, node->right, keys);
}

// get list of keys
struct list_simple *hashtable_get_keys (struct hashtable_t *htable)
{
    struct list_simple *keys;

    if (!htable)
        return NULL;

    keys = NULL;
    if (htable->bst)
        _hashtable_get_keys (htable->bst, htable->bst->root, &keys);

    return keys;
}

void *_hashtable_get_values (struct tree_t *bst, struct tree_node_t *node, struct list_simple **values)
{
    struct hashtable_node *hnode;

    // value not found
    if (!bst || !node || !values)
        return NULL;

    _hashtable_get_values (bst, node->left, values);
    hnode = node->data;
    if (hnode)
        list_append_data (values, hnode->value);
    _hashtable_get_values (bst, node->right, values);
}

// get list of values
struct list_simple *hashtable_get_values (struct hashtable_t *htable)
{
    struct list_simple *values;

    if (!htable)
        return NULL;

    values = NULL;
    if (htable->bst)
        _hashtable_get_values (htable->bst, htable->bst->root, &values);

    return values;
}

