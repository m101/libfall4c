#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "array_associative.h"

// set a value
struct aarray_t* set_value (struct aarray_t **array, char *key, void *value) {
    struct aarray_elt_t *elt;

    // pointer check
    if (!array)
        return;

    // create array if it doesn't exist
    if (!*array) {
        *array = calloc (1, sizeof(**array));
        array->tree = tree_new (aarray_comparator, aarray_elt_size);
    }

    // create array element
    elt = calloc (1, sizeof(*elt));
    elt->key = key;
    elt->value = value;

    // add value in tree
    binary_search_tree_add ((*array)->tree, elt);

    return array;
}

// get a value
void *get_value (struct aarray_t *array, char *key) {
    struct tree_t *node;
    struct aarray_elt_t elt = { key, NULL };

    // pointer check
    if (!array)
        return NULL;

    // search element in tree
    node = binary_search_tree_search (array->tree, &elt);

    // if we didn't find the key
    if (!node) 
        return NULL;
    // else
    // we found it
    else {
        if (node->data)
            return ((struct array_elt_t *)(node->data))->value;
    }
}

// compare 2 elements
int aarray_comparator (void *elt1, void *elt2) {
    return strcmp ( ((struct aarray_elt_t *)elt1)->key, ((struct aarray_elt_t *)elt2)->key );
}

// size of an associative array element
size_t aarray_elt_size (void *elt) {
    return sizeof(struct aarray_elt_t);
}

