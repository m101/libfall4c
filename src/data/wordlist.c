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

#include "data/wordlist.h"

#define BUFFER_SIZE 1000

// internal functions
// insert a word (stub)
int _wlist_insert_word (struct wlist_node_t **node, char *word, int sz_word);
// get word with highest occurence (stub)
struct wlist_node_t *_wlist_search_highest_occurrences (struct wlist_node_t *node, struct wlist_node_t **accu);
// count number of offsets (stub)
int _wlist_offsets_count (struct wlist_node_t *node, int total);

struct wlist_t *wlist_load (char *filename)
{
    return NULL;
}

// default wlist constructor
struct wlist_t *wlist_new (struct wlist_t **wlist)
{
    struct wlist_t *a_dic;

    a_dic = calloc(1, sizeof(**wlist));
    if (wlist)
        *wlist = a_dic;
    
    return a_dic;
}

// destroy wordlist recursively (stub)
void _wlist_destroy (struct wlist_node_t **node)
{
    if (node != NULL && *node != NULL) {
        // traverse nodes
        _wlist_destroy ( &((*node)->left) );
        _wlist_destroy ( &((*node)->right) );
        // free fields
        free ((*node)->description);
        free ((*node)->offsets);
        // free node
        free (*node), *node = NULL;
    }
}

// destroy wordlist
void wlist_destroy (struct wlist_t **wlist)
{
    if (!wlist || !*wlist)
        return;

    free((*wlist)->str);
    _wlist_destroy(&((*wlist)->root));
    _wlist_destroy(&((*wlist)->nodes));
    free(*wlist);
    *wlist = NULL;
}

// insert a word (stub)
int _wlist_insert_word (struct wlist_node_t **node, char *word, int sz_word)
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
        return _wlist_insert_word ( &((*node)->right), word, sz_word);
    else if ( check < 0 )
        return _wlist_insert_word ( &((*node)->left), word, sz_word);
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
int wlist_insert_word (struct wlist_t *wlist, char *word, int sz_word)
{
    return _wlist_insert_word(&(wlist->root), word, sz_word);
}

// search a word in the wordlist
struct wlist_node_t *_wlist_search_word (struct wlist_node_t *node, uint64_t hash)
{
    int check;

    if (!node)
        return NULL;

    check = node->hash - hash;
    // found
    if (check == 0)
        return node;
    else if (check < 0)
        return _wlist_search_word (node->left, hash);
    else
        return _wlist_search_word (node->right, hash);
}

// search a word in the wordlist
struct wlist_node_t *wlist_search_word (struct wlist_t *wlist, char *word, int sz_word)
{
    uint64_t hash;

    if (!wlist || !word || sz_word <= 0)
        return NULL;
    hash = fnv_hash (word, sz_word);

    return _wlist_search_word (wlist->root, hash);
}

// search if there is at least one dupe
struct wlist_node_t *wlist_find_dupe (struct wlist_node_t **node1, struct wlist_node_t **wlist, struct wlist_node_t **dupes)
{
    int check;
    struct wlist_node_t *ret;

    //
    if (node1 && wlist && dupes) {
        if (!*wlist || !*node1)
            return NULL;
        // check
        if ((*node1)->sz_str == (*wlist)->sz_str) {
            // small optimisation
            check = *((*node1)->str) - *((*wlist)->str);
            // full check
            if (!check)
                check = memcmp ((*node1)->str, (*wlist)->str, (*node1)->sz_str);
            // found dupe
            if (!check) {
                /*
                   if (!*dupes)
                 *dupes = wlist_new(dupes);
                 (*dupes)->count++;
                 (*dupes)->next = *wlist;
                 (*dupes) = *wlist;
                 return *wlist;
                //*/
            }
        }

        ret = wlist_find_dupe (&((*wlist)->left), node1, dupes);
        if (ret)
            return ret;
        ret = wlist_find_dupe (&((*wlist)->right), node1, dupes);
        if (ret)
            return ret;
    }

    return NULL;
}

// destroy dupes by agregation
struct wlist_t *_wlist_destroy_dupes (struct wlist_t **wlist)
{
    return NULL;
}

// destroy dupes by agregation
struct wlist_t *wlist_destroy_dupes (struct wlist_t *wlist)
{
    return NULL;
}

// build a wordlist from a sequence of characters
// usefull to study frequency analysis
struct wlist_t *wlist_build_from_str_static_size (struct wlist_t *wlist, char *str, int sz_str, int sz_token)
{
    char *p_str;

    // check string validity
    if (!wlist || !str || (sz_str <= 0) || sz_token <= 0)
        return NULL;

    // we construct wordlist
    p_str = str;
    while (p_str + sz_token < str + sz_str) {
        wlist_insert_word(wlist, p_str, sz_token);
        p_str++;
    }

    return wlist;
}

// build a wordlist from a sequence of characters
struct wlist_t *wlist_build_from_str (struct wlist_t *wlist, char *str, int sz_str, int sz_token_max)
{
    int sz_token;

    // check string validity
    if (!wlist || !str || (sz_str <= 0) || !sz_token_max)
        return NULL;

    for (sz_token = 1; sz_token <= sz_token_max; sz_token++)
        wlist_build_from_str_static_size (wlist, str, sz_str, sz_token);

    return wlist;
}

// build a wordlist from a sequence of characters
// usefull to study frequency analysis
struct wlist_t *wlist_build_from_str_static_size_kasiski (struct wlist_t *wlist, char *str, int sz_str, int sz_token)
{
    char *p_str1, *p_str2;
    int check;
    int dupe;

    // check string validity
    if (!wlist || !str || (sz_str <= 0) || !sz_token)
        return NULL;

    // we construct wordlist
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
            wlist_insert_word(wlist, p_str1, sz_token);
        p_str1++;
    }

    return wlist;
}

// build a wordlist from a sequence of characters
struct wlist_t *wlist_build_from_str_kasiski (struct wlist_t *wlist, char *str, int sz_str, int sz_token_max) 
{
    int sz_token;

    // check string validity
    if (!wlist || !str || (sz_str <= 0) || !sz_token_max)
        return NULL;

    for (sz_token = 1; sz_token <= sz_token_max; sz_token++) {
        wlist_build_from_str_static_size_kasiski (wlist, str, sz_str, sz_token);
    }

    return wlist;
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
struct wlist_node_t *_dist_distance (struct wlist_node_t *node)
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
struct wlist_t *wlist_distance (struct wlist_t *wlist)
{
    if (!wlist)
        return NULL;

    _dist_distance (wlist->root);

    return wlist;
}

// count number of nodes (stub)
int _wlist_nodes_count (struct wlist_node_t *node, int total)
{
    if (!node)
        return total;
    else {
        total++;
        total = _wlist_nodes_count(node->left, total);
        total = _wlist_nodes_count(node->right, total);
    }

    return total;
}

// count number of nodes
int wlist_nodes_count (struct wlist_t *wlist)
{
    if (!wlist)
        return -1;

    return _wlist_nodes_count (wlist->root, 0);
}

// count number of offsets (stub)
int _wlist_offsets_count (struct wlist_node_t *node, int total)
{
    if (!node)
        return total;
    else {
        // printf("[%p] node->count: %lu - word: %s\n", node, node->count, node->str);
        total += node->count;
        total = _wlist_offsets_count(node->left, total);
        total = _wlist_offsets_count(node->right, total);
    }

    return total;
}

// count number of offsets
int wlist_offsets_count (struct wlist_t *wlist)
{
    if (!wlist)
        return -1;

    return _wlist_offsets_count (wlist->root, 0);
}

// get word with highest occurence (stub)
struct wlist_node_t *_wlist_search_highest_occurrences (struct wlist_node_t *node, struct wlist_node_t **accu)
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
        return _wlist_search_highest_occurrences(node->right, accu);
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
        return _wlist_search_highest_occurrences(node->left, accu);
    }

    return *accu;
}

// get word with highest occurence (wrapper)
struct wlist_node_t *wlist_search_highest_occurrences (struct wlist_t *wlist)
{
    struct wlist_node_t *node;

    if (!wlist)
        return NULL;

    _wlist_search_highest_occurrences (wlist->root, &node);

    return node;
}

// show wordlist (stub)
void _wlist_show (struct wlist_node_t *node) 
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

    _wlist_show (node->right);
    _wlist_show (node->left);
}

// show wordlist
void wlist_show (struct wlist_t *wlist) 
{
    if (!wlist)
        return;

    wlist_distance (wlist);
    _wlist_show (wlist->root);
}

// compare count
int wlist_compare_count (void *data1, void *data2)
{
    struct wlist_node_t *wlist1, *wlist2;
    int check;

    if (!data1 || !data2)
        return -1;

    wlist1 = data1;
    wlist2 = data2;

    if (wlist1->count == wlist2->count)
        // check = wlist_compare_str (data1, data2);
        check = strcmp (data1, data2);
    else
        check = wlist1->count - wlist2->count;

    return check;
}

