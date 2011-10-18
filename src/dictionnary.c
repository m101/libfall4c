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

// default dict constructor
struct dict_elt_t* dict_new (struct dict_elt_t **dict) {
    struct dict_elt_t *pDict;

    pDict = calloc(1, sizeof(**dict));
    if (dict)
        *dict = pDict;
    
    return pDict;
}

// destroy dictionnary recursively
void dict_destroy (struct dict_elt_t **dict) {
    size_t i;

    if (dict != NULL && *dict != NULL) {
        // traverse nodes
        dict_destroy ( &((*dict)->left) );
        dict_destroy ( &((*dict)->right) );
        // free fields
        // free ((*dict)->str);
        free ((*dict)->description);
        free ((*dict)->offsets);
        // free node
        free (*dict), *dict = NULL;
    }
}

// insert a word
int dict_insert_word (struct dict_elt_t **dict, char *str, size_t szStr) {
    int check;

    // check for string validity
    if (!str || !szStr)
        return 0;
    // check for dictionnary double pointer validity
    if (!dict)
        return 0;

    // if we are at a leaf node
    // then we can insert the data
    if (!*dict) {
        // we allocate a node
        *dict = calloc(1, sizeof(**dict));
        (*dict)->str = str;
        // we allocate enough space for string
        // (*dict)->str = calloc(szStr + 1, sizeof(*str));
        // we make sure the string is zeroed out
        // memset((*dict)->str, 0, szStr * sizeof(*str) + 1);
        // we insert the string
        // memcpy ( (*dict)->str, str, szStr * sizeof(*str));
        // we initialize all variable to ensure correct behavior
        (*dict)->szStr = szStr + 1;
        (*dict)->count = 1;
        (*dict)->right = NULL;
        (*dict)->left = NULL;
        //
        (*dict)->szOffsets = POINTERS_NB;
        (*dict)->offsets = calloc(POINTERS_NB, sizeof(*(*dict)->offsets));
        (*dict)->offsets[0] = (unsigned long) str;

        return 1;
    }
    // compare strings
    check = memcmp((*dict)->str, str, szStr);

    // insertion
    if ( check > 0 )
        return dict_insert_word ( &((*dict)->right), str, szStr);
    else if ( check < 0 )
        return dict_insert_word ( &((*dict)->left), str, szStr);
    else {
        (*dict)->count++;

        // keep track of pointers
        if ((*dict)->count >= (*dict)->szOffsets) {
            (*dict)->szOffsets *= 2;
            (*dict)->offsets = realloc ( (*dict)->offsets, (*dict)->szOffsets * sizeof(*(*dict)->offsets));
        }
        (*dict)->offsets[(*dict)->count-1] = (unsigned long) str;

        return 1;
    }

    return 0;
}

// search a word in the dictionnary
struct dict_elt_t* dict_search_word (struct dict_elt_t *anchor, char *word, size_t szWord) {
    int check;

    if (!anchor || !word)
        return NULL;

    check = memcmp (anchor->str, word, szWord);
    // found
    if (check == 0)
        return anchor;
    else if (check < 0)
        return dict_search_word (anchor->left, word, szWord);
    else
        return dict_search_word (anchor->right, word, szWord);
}

// search if there is at least one dupe
struct dict_elt_t* dict_find_dupe (struct dict_elt_t **root, struct dict_elt_t **dict, struct dict_elt_t **dupes) {
    int check;
    struct dict_elt_t *ret;

    //
    if (root && dict && dupes) {
        if (!*dict || !*root)
            return NULL;
        // check
        if ((*root)->szStr == (*dict)->szStr) {
            // small optimisation
            check = *((*root)->str) - *((*dict)->str);
            // full check
            if (!check)
                check = memcmp ((*root)->str, (*dict)->str, (*root)->szStr);
            // found dupe
            if (!check) {
                if (!*dupes)
                    *dupes = dict_new(dupes);
                (*dupes)->count++;
                (*dupes)->next = *dict;
                (*dupes) = *dict;
                return *dict;
            }
        }

        ret = dict_find_dupe (&((*dict)->left), root, dupes);
        if (ret)
            return ret;
        ret = dict_find_dupe (&((*dict)->right), root, dupes);
        if (ret)
            return ret;
    }

    return NULL;
}

struct dict_elt_t* dict_find_dupes (struct dict_elt_t *root, struct dict_elt_t **dict) {
}

// destroy dupes by agregation
struct dict_elt_t* dict_destroy_dupe (struct dict_elt_t *root, struct dict_elt_t **dict) {
    if (root && dict) {
        if (*dict && (*dict != root)) {
            if (root->szStr == (*dict)->szStr
                    && memcmp(root->str, (*dict)->str, root->szStr)) {
                root->count += (*dict)->count;
            }
        }
    }
}

// find and destroy duplicates
/*
   struct dict_elt_t* dict_destroy_dupes (struct dict_t *dict) {
   int check;
   size_t count = 0;
   struct dict_elt_t *ldict, *dupes;

   if (dict) {
   dupes = NULL;
   while ( (ldict = dict_find_dupe (&(dict->root), , &dupes)) ) {
   if (count > 1)
   dict_destroy(&ldict);
   }
   }
   }
//*/

// build a dictionnary from a sequence of characters
// usefull to study frequency analysis
struct dict_elt_t* dict_build_static_size (struct dict_elt_t **dict, char *str, size_t szStr, size_t szToken) {
    char *pStr;

    // check string validity
    if (!dict || !str || !szStr || !szToken)
        return NULL;

    // we construct dictionary
    pStr = str;
    while (pStr + szToken < str + szStr) {
        dict_insert_word(dict, pStr, szToken);
        pStr++;
    }

    return *dict;
}

// build a dictionnary from a sequence of characters
struct dict_elt_t* dict_build (struct dict_elt_t **dict, char *str, size_t szStr, size_t szTokenMax) {
    size_t i;

    // check string validity
    if (!dict || !str || !szStr || !szTokenMax)
        return NULL;

    for (i = 1; i <= szTokenMax; i++)
        dict_build_static_size (dict, str, szStr, i);

    return *dict;
}

int compare_ulong (const void *a, const void *b) {
    return *(unsigned long *)a - *(unsigned long *)b;
}

// compute distance between equal words
struct dict_elt_t *dict_distance_stub (struct dict_elt_t *dict) {
    size_t i;

    if (dict) {
        // if there
        if (dict->count >= 1 && dict->offsets) {
            for (i = 0; i < dict->count; i++)
                dict->offsets[i] = abs (dict->offsets[i] - dict->base);
        }
        dict_distance_stub (dict->left);
        dict_distance_stub (dict->right);
    }
}

struct dict_elt_t *dict_distance (struct dict_elt_t *dict) {
    size_t i;

    if (!dict)
        return NULL;

    if (dict->offsets) {
        qsort (dict->offsets, dict->count, sizeof(unsigned long), compare_ulong);

        dict->base = dict->offsets[0];

        dict_distance_stub (dict);
    }
}

//
struct dict_elt_t *dict_search_highest_occurrences (struct dict_elt_t *dict, struct dict_elt_t **node) {
    int check;

    // if invalid node pointer given
    // then we exit
    if (!node || !dict)
        return NULL;

    if (dict) {
        // if node is null
        // then it is equal to first the anchor
        if (!*node)
            *node = dict;

        // traverse tree
        // right side
        if (dict->right) {
            // if right node count is higher than actual node
            // then we update the actual node
            if (dict->right->count > (*node)->count)
                *node = dict->right;
            // if we have the same count
            // then we update the actual node according to alphabetical order
            else if (dict->right->count == (*node)->count) {
                // get order
                check = memcmp(dict->right->str, (*node)->str, (*node)->szStr);

                // if right node is before actual node
                // then we update actual node
                if (check < 0)
                    *node = dict->right;
            }

            // we go right
            return dict_search_highest_occurrences(dict->right, node);
        }

        // left side
        if (dict->left) {
            // if right node count is higher than actual node
            // then we update the actual node
            if (dict->left->count > (*node)->count)
                *node = dict->left;
            // if we have the same count
            // then we update the actual node according to alphabetical order
            else if (dict->left->count == (*node)->count) {
                // get order
                check = memcmp(dict->left->str, (*node)->str, (*node)->szStr);

                // if left node is before actual node
                // then we update actual node
                if (check < 0)
                    *node = dict->left;
            }

            // we go left
            return dict_search_highest_occurrences(dict->left, node);
        }
    }

    return *node;
}

void dict_show (struct dict_elt_t *dict) {
    size_t i;

    if (dict) {
        dict_distance(dict);

        //if (dict->count > 1) {

            if (dict->str) {
                printf("str   : %s\n", dict->str);
                printf("szStr : %lu\n", dict->szStr);
            }

            printf("count : %lu\n", dict->count);

            if (dict->offsets) {
                for (i = 0; i < dict->count; i++)
                    printf("offset[%lu] = %lu\n", i, dict->offsets[i]);
                printf("\n");
            }
        //}
        dict_show (dict->right);
        dict_show (dict->left);
    }
}

