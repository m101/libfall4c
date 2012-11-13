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

#ifndef _DICTIONNARY_H
#define _DICTIONNARY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdint.h>

// wordlist structure
struct dict_t {
    // binary search tree that contains the key=value
    struct tree_t *bst;
};

struct dict_node_t {
    // key
    uint64_t hash_key;
    int sz_key;
    char *key;
    // value
    int sz_value;
    char *value;
};

// wordlist : insert a word
int dict_set (struct dict_t **dict, char *key, char *value);

#ifdef __cplusplus
}
#endif

#endif /* _DICTIONNARY_H */
