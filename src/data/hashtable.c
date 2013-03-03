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

int hashtable_comparator (void *data1, void *data2);
size_t hashtable_elt_size (void *elt);

static const struct data_ops hashtable_data_ops = {
    .comparator = hashtable_comparator,
    .destroy = hashtable_destroy,
    .get_size = hashtable_elt_size,
    .show = show_no_ops
};

/* @desc    Compute double hashing (FNV + 8 bits ADD)
*/
int _hnode_hash (struct hashtable_node *hnode, uint8_t *str, int len)
{
    int idx_str;
    uint16_t checksum;
    static uint16_t next_idx = 0;

    if (!hnode ||  !str ||  len <= 0) {
        fprintf (stderr, "error: _hnode_hash(): Bad parameter(s)\n");
        return -1;
    }

    checksum = 0;
    hnode->hash_key = 14695981039346656037UL;
    for (idx_str = 0; idx_str < len; idx_str++) {
        hnode->hash_key ^= str[idx_str];
        hnode->hash_key *= 1099511628211UL;

        checksum += str[idx_str];
    }
    checksum %= N_BUCKETS;
    hnode->idx_bucket = (hnode->hash_key + next_idx * checksum) % N_BUCKETS;
    next_idx = (next_idx + 1) % N_BUCKETS;
    // hnode->idx_bucket = checksum;

    return 0;
}

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

struct hashtable_t *hashtable_new (void)
{
    int idx_bucket;
    struct hashtable_t *htable;

    htable = calloc (1, sizeof(*htable));
    if (!htable)
        return NULL;

    //
    for (idx_bucket = 0; idx_bucket < N_BUCKETS; idx_bucket++) {
        htable->buckets[idx_bucket] = calloc (1, sizeof(*htable->buckets[idx_bucket]));
        htable->buckets[idx_bucket]->dops = &hashtable_data_ops;
    }

    // values and keys callbacks
    htable->keys = list_new();
    htable->values = list_new();

    return htable;
}

void hashtable_node_destroy_data (void **data)
{
    struct hashtable_node **node;

    node = data;
    if (!node || !*node) {
        fprintf (stderr, "error: hashtable_node_destroy_data(): Bad parameter(s)\n");
        return;
    }

    // string_destroy (&((*node)->key));
    free ((*node)->key);
    // free ((*node)->value);
    free (*node);
    *node = NULL;
}

void _hashtable_node_free (void *data)
{
    hashtable_node_destroy_data (&data);
}

void hashtable_destroy (struct hashtable_t **htable)
{
    int idx_bucket;

    if (!htable || !*htable)
        return;

    // free buckets
    for (idx_bucket = 0; idx_bucket < N_BUCKETS; idx_bucket++)
        tree_free ((*htable)->buckets[idx_bucket], _hashtable_node_free);

    // free key list
    list_set_callback ((*htable)->keys, destroy, string_destroy);
    list_destroy (&((*htable)->keys));

    // free values
    list_destroy (&((*htable)->values));

    // free htable
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
    _hnode_hash (elt, key, elt->sz_key);
    // value
    elt->value = value;
    
    // keep track of keys and values
    string_set (&s_key, key);
    if ((*htable)->keys == NULL)
        (*htable)->keys = list_new();
    list_append_data (&((*htable)->keys), s_key);
/*
    if ((*htable)->values == NULL)
        (*htable)->values = list_new();
    list_add (&((*htable)->values), value);
*/
    // add value in tree
    bst_add ((*htable)->buckets[elt->idx_bucket], elt);

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

    // search element in tree
    _hnode_hash (&elt, key, strlen(key));
    helt = bst_search (&(htable->buckets[elt.idx_bucket]), &elt);
    if (!helt)
        return NULL;

    return helt->value;
}

// get list of keys
struct list_simple *hashtable_get_keys (struct hashtable_t *htable)
{
    return htable->keys;
}

// get list of values
struct list_simple *hashtable_get_values (struct hashtable_t *htable)
{
    return htable->values;
}

