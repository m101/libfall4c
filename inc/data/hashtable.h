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

#ifndef _ARRAY_ASSOCIATIVE_
#define _ARRAY_ASSOCIATIVE_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include "tree_common.h"

#define N_BUCKETS 256

#define hashtable_for_each(htable, key, value)

// associative array element
struct hashtable_node {
    uint16_t idx_bucket;
    // key
    uint64_t hash_key;
    int sz_key;
    char *key;
    // value
    int sz_value;
    void *value;
};

// associative array
struct hashtable_t {
    struct list_simple *keys;
    struct list_simple *values;

    struct tree_t *buckets[N_BUCKETS];
};

struct hashtable_t *hashtable_new (void);
void hashtable_destroy (struct hashtable_t **htable);
// set a value
struct hashtable_t *hashtable_set_value (struct hashtable_t **htable, char *key, void *value);
// get a value
void *hashtable_get_value (struct hashtable_t *htable, char *key);
// get list of keys
struct list_simple *hashtable_get_keys (struct hashtable_t *htable);
// get list of values
struct list_simple *hashtable_get_values (struct hashtable_t *htable);

#ifdef __cplusplus
}
#endif

#endif
