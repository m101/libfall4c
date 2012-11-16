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

#include "tree_common.h"

// associative array element
struct hashtable_node {
    char *key;
    void *value;
};

// associative array
struct hashtable_t {
    struct tree_t *array;
};

struct hashtable_t *hashtable_new (void);
void hashtable_destroy (struct hashtable_t **htable);
// set a value
struct hashtable_t* hashtable_set_value (struct hashtable_t **htable, char *key, void *value);
// get a value
void *hashtable_get_value (struct hashtable_t *htable, char *key);

#ifdef __cplusplus
}
#endif

#endif
