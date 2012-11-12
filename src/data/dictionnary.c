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
#include <math.h>

#include "data/dictionnary.h"

#define BUFFER_SIZE 1000

// internal functions
// insert a word (stub)
int _dict_insert_word (struct dict_node_t **node, char *word, int sz_word);
// get word with highest occurence (stub)
struct dict_node_t *_dict_search_highest_occurrences (struct dict_node_t *node, struct dict_node_t **accu);
// count number of offsets (stub)
int _dict_offsets_count (struct dict_node_t *node, int total);

struct dict_t *dict_load (char *filename)
{
    return NULL;
}

// default dict constructor
struct dict_t *dict_new (struct dict_t **dict)
{
    struct dict_t *a_dic;

    a_dic = calloc(1, sizeof(**dict));
    if (dict)
        *dict = a_dic;
    
    return a_dic;
}

// destroy dictionnary recursively (stub)
void _dict_destroy (struct dict_node_t **node)
{
    if (node != NULL && *node != NULL) {
        // traverse nodes
        _dict_destroy ( &((*node)->left) );
        _dict_destroy ( &((*node)->right) );
        // free fields
        free ((*node)->description);
        free ((*node)->offsets);
        // free node
        free (*node), *node = NULL;
    }
}

// destroy dictionnary
void dict_destroy (struct dict_t **dict)
{
    if (!dict || !*dict)
        return;

    free((*dict)->str);
    _dict_destroy(&((*dict)->root));
    _dict_destroy(&((*dict)->nodes));
    free(*dict);
    *dict = NULL;
}

// insert a word (stub)
int _dict_insert_word (struct dict_node_t **node, char *word, int sz_word)
{
    int check;

    // check for wording validity
    if (!word || sz_word <= 0)
        return 0;
    // check for nodeionnary double pointer validity
    if (!node)
        return 0;

    // if we are at a leaf node
    // then we can insert the data
    if (!*node) {
        // we allocate a node
        *node = calloc(1, sizeof(**node));
        (*node)->hash = fnv_hash (word, sz_word);
        (*node)->str = word;
        // we initialize all variable to ensure correct behavior
        (*node)->sz_str = sz_word;
        (*node)->count = 1;
        (*node)->right = NULL;
        (*node)->left = NULL;
        //
        (*node)->sz_offsets = POINTERS_NB;
        (*node)->offsets = calloc(POINTERS_NB, sizeof(*(*node)->offsets));
        (*node)->offsets[0] = (unsigned long) word;

        return 1;
    }

    // compare words
    if ( (*node)->sz_str != sz_word )
        check = (*node)->sz_str - sz_word;
    else
        check = memcmp((*node)->str, word, sz_word);

    // insertion
    if ( check > 0 )
        return _dict_insert_word ( &((*node)->right), word, sz_word);
    else if ( check < 0 )
        return _dict_insert_word ( &((*node)->left), word, sz_word);
    else {
        // if same ptr or size not equal
        // then do not count it
        if ((word == (*node)->str) && (sz_word == (*node)->sz_str))
            return 0;

        // count number of occurrences of the word
        (*node)->count++;

        // keep track of pointers
        if ((*node)->count >= (*node)->sz_offsets) {
            (*node)->sz_offsets *= 2;
            (*node)->offsets = realloc ( (*node)->offsets, (*node)->sz_offsets * sizeof(*(*node)->offsets));
        }
        (*node)->offsets[(*node)->count-1] = (unsigned long) word;

        return 1;
    }

    return 0;
}

// insert a word
int dict_insert_word (struct dict_t *dict, char *word, int sz_word)
{
    return _dict_insert_word(&(dict->root), word, sz_word);
}

// search a word in the dictionnary
struct dict_node_t *_dict_search_word (struct dict_node_t *node, uint64_t hash)
{
    int check;

    if (!node)
        return NULL;

    check = node->hash - hash;
    // found
    if (check == 0)
        return node;
    else if (check < 0)
        return _dict_search_word (node->left, hash);
    else
        return _dict_search_word (node->right, hash);
}

// search a word in the dictionnary
struct dict_node_t *dict_search_word (struct dict_t *dict, char *word, int sz_word)
{
    uint64_t hash;

    if (!dict || !word || sz_word <= 0)
        return NULL;
    hash = fnv_hash (word, sz_word);

    return _dict_search_word (dict->root, hash);
}

// search if there is at least one dupe
struct dict_node_t *dict_find_dupe (struct dict_node_t **node1, struct dict_node_t **dict, struct dict_node_t **dupes)
{
    int check;
    struct dict_node_t *ret;

    //
    if (node1 && dict && dupes) {
        if (!*dict || !*node1)
            return NULL;
        // check
        if ((*node1)->sz_str == (*dict)->sz_str) {
            // small optimisation
            check = *((*node1)->str) - *((*dict)->str);
            // full check
            if (!check)
                check = memcmp ((*node1)->str, (*dict)->str, (*node1)->sz_str);
            // found dupe
            if (!check) {
                /*
                   if (!*dupes)
                 *dupes = dict_new(dupes);
                 (*dupes)->count++;
                 (*dupes)->next = *dict;
                 (*dupes) = *dict;
                 return *dict;
                //*/
            }
        }

        ret = dict_find_dupe (&((*dict)->left), node1, dupes);
        if (ret)
            return ret;
        ret = dict_find_dupe (&((*dict)->right), node1, dupes);
        if (ret)
            return ret;
    }

    return NULL;
}

// destroy dupes by agregation
struct dict_t *_dict_destroy_dupes (struct dict_t **dict)
{
    return NULL;
}

// destroy dupes by agregation
struct dict_t *dict_destroy_dupes (struct dict_t *dict)
{
    return NULL;
}

// build a dictionnary from a sequence of characters
// usefull to study frequency analysis
struct dict_t *dict_build_from_str_static_size (struct dict_t *dict, char *str, int sz_str, int sz_token)
{
    char *p_str;

    // check string validity
    if (!dict || !str || (sz_str <= 0) || sz_token <= 0)
        return NULL;

    // we construct dictionary
    p_str = str;
    while (p_str + sz_token < str + sz_str) {
        dict_insert_word(dict, p_str, sz_token);
        p_str++;
    }

    return dict;
}

// build a dictionnary from a sequence of characters
struct dict_t *dict_build_from_str (struct dict_t *dict, char *str, int sz_str, int sz_token_max)
{
    int sz_token;

    // check string validity
    if (!dict || !str || (sz_str <= 0) || !sz_token_max)
        return NULL;

    for (sz_token = 1; sz_token <= sz_token_max; sz_token++)
        dict_build_from_str_static_size (dict, str, sz_str, sz_token);

    return dict;
}

// build a dictionnary from a sequence of characters
// usefull to study frequency analysis
struct dict_t *dict_build_from_str_static_size_kasiski (struct dict_t *dict, char *str, int sz_str, int sz_token)
{
    char *p_str1, *p_str2;
    int check;
    int dupe;

    // check string validity
    if (!dict || !str || (sz_str <= 0) || !sz_token)
        return NULL;

    // we construct dictionary
    p_str1 = str;
    while (p_str1 + sz_token < str + sz_str) {
        // check if token appear more than once
        dupe = 0;
        p_str2 = str;
        while (p_str2 < str + sz_str) {
            check = memcmp(p_str1, p_str2, sz_token);
            if (check == 0) {
                dupe++;
                if (dupe > 1)
                    break;
            }
            p_str2++;
        }

        // if it appear more than once
        // then we are interested in it
        if (dupe > 1)
            dict_insert_word(dict, p_str1, sz_token);
        p_str1++;
    }

    return dict;
}

// build a dictionnary from a sequence of characters
struct dict_t *dict_build_from_str_kasiski (struct dict_t *dict, char *str, int sz_str, int sz_token_max) 
{
    int sz_token;

    // check string validity
    if (!dict || !str || (sz_str <= 0) || !sz_token_max)
        return NULL;

    for (sz_token = 1; sz_token <= sz_token_max; sz_token++) {
        dict_build_from_str_static_size_kasiski (dict, str, sz_str, sz_token);
    }

    return dict;
}

int compare_ulong (const void *a, const void *b)
{
    return *(unsigned long *)a - *(unsigned long *)b;
}

int compare_int (const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// compute distance between equal words
struct dict_node_t *_dist_distance (struct dict_node_t *node)
{
    int i;

    // check pointer
    if (!node)
        return NULL;

    // compute each offset
    if (node->count >= 1 && node->offsets) {
        if (node->base == 0) {
            qsort (node->offsets, node->count, sizeof(int), compare_int);
            node->base = node->offsets[0];
        }
        for (i = 0; i < node->count; i++) {
            // check that offset is bigger than base
            // in order to avoid integer wrapping
            if (node->offsets[i] >= node->base)
                node->offsets[i] = abs (node->offsets[i] - node->base);
        }
    }
    _dist_distance (node->left);
    _dist_distance (node->right);

    return node;
}

// get distance between 2 same word in a file
struct dict_t *dict_distance (struct dict_t *dict)
{
    if (!dict)
        return NULL;

    _dist_distance (dict->root);

    return dict;
}

// count number of nodes (stub)
int _dict_nodes_count (struct dict_node_t *node, int total)
{
    if (!node)
        return total;
    else {
        total++;
        total = _dict_nodes_count(node->left, total);
        total = _dict_nodes_count(node->right, total);
    }

    return total;
}

// count number of nodes
int dict_nodes_count (struct dict_t *dict)
{
    if (!dict)
        return -1;

    return _dict_nodes_count (dict->root, 0);
}

// count number of offsets (stub)
int _dict_offsets_count (struct dict_node_t *node, int total)
{
    if (!node)
        return total;
    else {
        // printf("[%p] node->count: %lu - word: %s\n", node, node->count, node->str);
        total += node->count;
        total = _dict_offsets_count(node->left, total);
        total = _dict_offsets_count(node->right, total);
    }

    return total;
}

// count number of offsets
int dict_offsets_count (struct dict_t *dict)
{
    if (!dict)
        return -1;

    return _dict_offsets_count (dict->root, 0);
}

// get word with highest occurence (stub)
struct dict_node_t *_dict_search_highest_occurrences (struct dict_node_t *node, struct dict_node_t **accu)
{
    int check;

    // if invalid accu pointer given
    // then we exit
    if (!accu || !node)
        return NULL;

    // if accu is null
    // then it is equal to first the anchor
    if (!*accu)
        *accu = node;

    // traverse tree
    // right side
    if (node->right) {
        // if right accu count is higher than actual accu
        // then we update the actual accu
        if (node->right->count > (*accu)->count)
            *accu = node->right;
        // if we have the same count
        // then we update the actual accu according to alphabetical order
        else if (node->right->count == (*accu)->count) {
            // get order
            check = memcmp(node->right->str, (*accu)->str, (*accu)->sz_str);

            // if right accu is before actual accu
            // then we update actual accu
            if (check < 0)
                *accu = node->right;
        }

        // we go right
        return _dict_search_highest_occurrences(node->right, accu);
    }

    // left side
    if (node->left) {
        // if right accu count is higher than actual accu
        // then we update the actual accu
        if (node->left->count > (*accu)->count)
            *accu = node->left;
        // if we have the same count
        // then we update the actual accu according to alphabetical order
        else if (node->left->count == (*accu)->count) {
            // get order
            check = memcmp(node->left->str, (*accu)->str, (*accu)->sz_str);

            // if left accu is before actual accu
            // then we update actual accu
            if (check < 0)
                *accu = node->left;
        }

        // we go left
        return _dict_search_highest_occurrences(node->left, accu);
    }

    return *accu;
}

// get word with highest occurence (wrapper)
struct dict_node_t *dict_search_highest_occurrences (struct dict_t *dict)
{
    struct dict_node_t *node;

    if (!dict)
        return NULL;

    _dict_search_highest_occurrences (dict->root, &node);

    return node;
}

// show dictionnary (stub)
void _dict_show (struct dict_node_t *node) 
{
    int idx_str;

    // check ptr
    if (!node)
        return;

    if (node->str) {
        for (idx_str = 0; idx_str < node->sz_str; idx_str++)
            putchar(node->str[idx_str]);
        putchar('\n');
    }

    _dict_show (node->right);
    _dict_show (node->left);
}

// show dictionnary
void dict_show (struct dict_t *dict) 
{
    if (!dict)
        return;

    dict_distance (dict);
    _dict_show (dict->root);
}

// compare count
int dict_compare_count (void *data1, void *data2)
{
    struct dict_node_t *dict1, *dict2;
    int check;

    if (!data1 || !data2)
        return -1;

    dict1 = data1;
    dict2 = data2;

    if (dict1->count == dict2->count)
        // check = dict_compare_str (data1, data2);
        check = strcmp (data1, data2);
    else
        check = dict1->count - dict2->count;

    return check;
}

