/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include "dictionnary.h"

#define BUFFER_SIZE 1000

// internal functions
// insert a word (stub)
int dict_insert_word_stub (struct dict_elt_t **node, char *word, int szWord);
// get word with highest occurence (stub)
struct dict_elt_t *dict_search_highest_occurrences_stub (struct dict_elt_t *node, struct dict_elt_t **accu);
// count number of offsets (stub)
int dict_offsets_count_stub (struct dict_elt_t *node, int total);

// default dict constructor
struct dict_t* dict_new (struct dict_t **dict) {
    struct dict_t *pDict;

    pDict = calloc(1, sizeof(**dict));
    if (dict)
        *dict = pDict;
    
    return pDict;
}

// destroy dictionnary recursively (stub)
void dict_destroy_stub (struct dict_elt_t **node) {
    if (node != NULL && *node != NULL) {
        // traverse nodes
        dict_destroy_stub ( &((*node)->left) );
        dict_destroy_stub ( &((*node)->right) );
        // free fields
        free ((*node)->description);
        free ((*node)->offsets);
        // free node
        free (*node), *node = NULL;
    }
}

// destroy dictionnary
void dict_destroy (struct dict_t **dict) {
    free((*dict)->str);
    dict_destroy_stub(&((*dict)->root));
    dict_destroy_stub(&((*dict)->nodes));
    free(*dict);
    *dict = NULL;
}

// insert a word (stub)
int dict_insert_word_stub (struct dict_elt_t **node, char *word, int szWord) {
    int check;

    // check for wording validity
    if (!word || szWord <= 0)
        return 0;
    // check for nodeionnary double pointer validity
    if (!node)
        return 0;

    // if we are at a leaf node
    // then we can insert the data
    if (!*node) {
        // we allocate a node
        *node = calloc(1, sizeof(**node));
        (*node)->str = word;
        // we allocate enough space for word
        // (*node)->str = calloc(szWord + 1, sizeof(*word));
        // we make sure the wording is zeroed out
        // memset((*node)->str, 0, szWord * sizeof(*word) + 1);
        // we insert the wording
        // memcpy ( (*node)->str, word, szWord * sizeof(*word));
        // we initialize all variable to ensure correct behavior
        (*node)->szStr = szWord;
        (*node)->count = 1;
        (*node)->right = NULL;
        (*node)->left = NULL;
        //
        (*node)->szOffsets = POINTERS_NB;
        (*node)->offsets = calloc(POINTERS_NB, sizeof(*(*node)->offsets));
        (*node)->offsets[0] = (unsigned long) word;

        return 1;
    }

    // compare words
    if ( (*node)->szStr != szWord )
        check = (*node)->szStr - szWord;
    else
        check = memcmp((*node)->str, word, szWord);

    // insertion
    if ( check > 0 )
        return dict_insert_word_stub ( &((*node)->right), word, szWord);
    else if ( check < 0 )
        return dict_insert_word_stub ( &((*node)->left), word, szWord);
    else {
        // if same ptr or size not equal
        // then do not count it
        if ((word == (*node)->str) && (szWord == (*node)->szStr))
            return 0;

        // count number of occurrences of the word
        (*node)->count++;

        // keep track of pointers
        if ((*node)->count >= (*node)->szOffsets) {
            (*node)->szOffsets *= 2;
            (*node)->offsets = realloc ( (*node)->offsets, (*node)->szOffsets * sizeof(*(*node)->offsets));
        }
        (*node)->offsets[(*node)->count-1] = (unsigned long) word;

        return 1;
    }

    return 0;
}

// insert a word
int dict_insert_word (struct dict_t *dict, char *word, int szWord) {
    return dict_insert_word_stub(&(dict->root), word, szWord);
}

// search a word in the dictionnary
struct dict_elt_t* dict_search_word_stub (struct dict_elt_t *node, char *word, int szWord) {
    int check;

    if (!node)
        return NULL;

    check = memcmp (node->str, word, szWord);
    // found
    if (check == 0)
        return node;
    else if (check < 0)
        return dict_search_word_stub (node->left, word, szWord);
    else
        return dict_search_word_stub (node->right, word, szWord);
}

// search a word in the dictionnary
struct dict_elt_t* dict_search_word (struct dict_t *dict, char *word, int szWord) {
    if (!dict || !word || szWord < 0)
        return NULL;
    return dict_search_word_stub(dict->root, word, szWord);
}

// search if there is at least one dupe
struct dict_elt_t* dict_find_dupe (struct dict_elt_t **node1, struct dict_elt_t **dict, struct dict_elt_t **dupes) {
    int check;
    struct dict_elt_t *ret;

    //
    if (node1 && dict && dupes) {
        if (!*dict || !*node1)
            return NULL;
        // check
        if ((*node1)->szStr == (*dict)->szStr) {
            // small optimisation
            check = *((*node1)->str) - *((*dict)->str);
            // full check
            if (!check)
                check = memcmp ((*node1)->str, (*dict)->str, (*node1)->szStr);
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
struct dict_t* dict_destroy_dupes_stub (struct dict_t **dict) {
    return NULL;
}

// destroy dupes by agregation
struct dict_t* dict_destroy_dupes (struct dict_t *dict) {
    return NULL;
}

// build a dictionnary from a sequence of characters
// usefull to study frequency analysis
struct dict_t* dict_build_from_str_static_size (struct dict_t *dict, char *str, int szStr, int szToken) {
    char *pStr;

    // check string validity
    if (!dict || !str || (szStr <= 0) || !szToken)
        return NULL;

    // we construct dictionary
    pStr = str;
    while (pStr + szToken < str + szStr) {
        dict_insert_word(dict, pStr, szToken);
        pStr++;
    }

    return dict;
}

// build a dictionnary from a sequence of characters
struct dict_t* dict_build_from_str (struct dict_t *dict, char *str, int szStr, int szTokenMax) {
    int szToken;

    // check string validity
    if (!dict || !str || (szStr <= 0) || !szTokenMax)
        return NULL;

    for (szToken = 1; szToken <= szTokenMax; szToken++)
        dict_build_from_str_static_size (dict, str, szStr, szToken);

    return dict;
}

int compare_ulong (const void *a, const void *b) {
    return *(unsigned long *)a - *(unsigned long *)b;
}

// compute distance between equal words
struct dict_elt_t *dict_distance_stub (struct dict_elt_t *node) {
    int i;

    // check pointer
    if (!node)
        return NULL;

    // compute each offset
    if (node->count >= 1 && node->offsets) {
        for (i = 0; i < node->count; i++) {
            // check that offset is bigger than base
            // in order to avoid integer wrapping
            if (node->offsets[i] > node->base)
                node->offsets[i] = abs (node->offsets[i] - node->base);
        }
    }
    dict_distance_stub (node->left);
    dict_distance_stub (node->right);

    return node;
}

// get distance between 2 same word in a file
struct dict_t *dict_distance (struct dict_t *dict) {
    struct dict_elt_t *root;

    if (!dict)
        return NULL;

    root = dict->root;
    if (!root)
        return NULL;

    if (root->offsets) {
        qsort (root->offsets, root->count, sizeof(unsigned long), compare_ulong);

        root->base = root->offsets[0];

        dict_distance_stub (root);
    }

    return dict;
}

// count number of offsets (stub)
int dict_offsets_count_stub (struct dict_elt_t *node, int total) {
    if (!node)
        return total;
    else {
        // printf("[%p] node->count: %lu - word: %s\n", node, node->count, node->str);
        // printf("node->count: %lu - word: %s\n", node->count, node->str);
        // printf("%s\n", node->str);
        dict_offsets_count_stub(node->left, total + node->count);
        dict_offsets_count_stub(node->right, total + node->count);
    }
}

// count number of offsets
int dict_offsets_count (struct dict_t *dict) {
    struct dict_elt_t *root;

    if (!dict)
        return -1;

    root = dict->root;
    return dict_offsets_count_stub (root, 0);
}

// get word with highest occurence (stub)
struct dict_elt_t *dict_search_highest_occurrences_stub (struct dict_elt_t *node, struct dict_elt_t **accu) {
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
            check = memcmp(node->right->str, (*accu)->str, (*accu)->szStr);

            // if right accu is before actual accu
            // then we update actual accu
            if (check < 0)
                *accu = node->right;
        }

        // we go right
        return dict_search_highest_occurrences_stub(node->right, accu);
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
            check = memcmp(node->left->str, (*accu)->str, (*accu)->szStr);

            // if left accu is before actual accu
            // then we update actual accu
            if (check < 0)
                *accu = node->left;
        }

        // we go left
        return dict_search_highest_occurrences_stub(node->left, accu);
    }

    return *accu;
}

// get word with highest occurence (wrapper)
struct dict_elt_t *dict_search_highest_occurrences (struct dict_t *dict) {
    struct dict_elt_t *node;

    if (!dict)
        return NULL;

    dict_search_highest_occurrences_stub (dict->root, &node);

    return node;
}

// show dictionnary (stub)
void dict_show_stub (struct dict_elt_t *node) {
    int idxStr;

    // check ptr
    if (!node)
        return;

    if (node->str) {
        printf("str(%d) = %d occurrences : ", node->szStr, node->count);
        for (idxStr = 0; idxStr < node->szStr; idxStr++)
            putchar(node->str[idxStr]);
        putchar('\n');
    }

    /*
    if (node->offsets) {
        for (idxStr = 0; idxStr < node->count; idxStr++)
            printf("offset[%d] = %ld\n", idxStr, node->offsets[idxStr]);
    }
    */
    dict_show_stub (node->right);
    dict_show_stub (node->left);
}

// show dictionnary
void dict_show (struct dict_t *dict) {
    if (!dict)
        return;

    dict_distance(dict);
    dict_show_stub(dict->root);
}
