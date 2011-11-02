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

#include "array_associative.h"
#include "tree_binary.h"

// compare 2 elements in a hashtable
int hashtable_comparator (void *elt1, void *elt2) {
    return strcmp ( ((struct aarray_elt_t *)elt1)->key, ((struct aarray_elt_t *)elt2)->key );
}

// size of an associative array element
size_t hashtable_elt_size (void *elt) {
    return sizeof(struct aarray_elt_t);
}

// set a value
struct hashtable_t* set_value (struct hashtable_t **hashtable, char *key, void *value) {
    struct aarray_elt_t *elt;

    // pointer check
    if (!hashtable)
        return NULL;

    // create array if it doesn't exist
    if (!*hashtable) {
        *hashtable = calloc (1, sizeof(**hashtable));
        (*hashtable)->array = tree_new (hashtable_comparator, hashtable_elt_size);
    }

    // create array element
    elt = calloc (1, sizeof(*elt));
    elt->key = key;
    elt->value = value;

    // add value in tree
    binary_search_tree_add ((*hashtable)->array, elt);

    return *hashtable;
}

// get a value
void *get_value (struct hashtable_t *hashtable, char *key) {
    struct tree_t *node;
    struct aarray_elt_t elt = { key, NULL };

    // pointer check
    if (!hashtable)
        return NULL;

    // search element in tree
    node = binary_search_tree_search (hashtable->array, &elt);

    // if we didn't find the key
    if (!node)
        return NULL;
    // else
    // we found it
    else {
        /*
        if (node->data)
            return ((struct array_elt_t *)(node->data))->value;
        //*/
    }

    // return node->data;
    return NULL;
}

