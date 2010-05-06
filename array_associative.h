#ifndef _ARRAY_ASSOCIATIVE_
#define _ARRAY_ASSOCIATIVE_

#include "tree_binary.h"

// associative array element
struct aarray_elt_t {
    char *key;
    void *value;
};

// associative array
struct aarray_t {
    struct tree_t *array;
};

// set a value
void set_value (struct aarray_t **array, char *key, void *value);
// get a value
void *get_value (struct aarray_t **array, char *key);

// callbacks
// compare 2 elements
int aarray_comparator (void *elt1, void *elt2);
// size of an associative array element
size_t aarray_elt_size (void *elt);

#endif
