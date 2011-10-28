#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "dictionnary.h"
#include "tree_common.h"
#include "tree_binary.h"

#define BUFFER_SIZE 1000

// default dict constructor
struct dict_elt* dict_new (struct dict_t **dict) {
    struct dict_t *pDict;

    pDict = calloc(1, sizeof(**dict));
    if (dict)
        *dict = pDict;
    
    return pDict;
}

// insert a word
int dict_insert_word (struct dict_t **dict, char *str, size_t szStr) {
    int check;
    struct dict_elt_t *word, *pWord;

    // check for string validity
    if (!str || !szStr)
        return 0;
    // check for dictionnary double pointer validity
    if (!dict)
        return 0;

    if (!*dict) {
        *dict = tree_new ();
        tree_set_comparator (dict_compare_str);
    }

    word = calloc(1, sizeof(*word));
    word->str = calloc(1, (szStr + 1) * sizeof(*str));
    memcpy (word->str, str, szStr * sizeof(*str));
    word->szStr = szStr + 1;
    word->count = 1;
    pWord = tree_binary_search_tree_add (*dict, word);

    if (!pWord)
        return -1;
    else {
        if (pWord != word)
            free(word);
        pWord->count++;

        // keep track of pointers
        if pWord->count >= (*pWord->szOffsets) {
            if ( pWord->szOffsets == 0 )
                pWord->szOffsets = POINTERS_NB;
            else
                pWord->szOffsets *= 2;
            pWord->offsets = realloc (pWord->offsets, pWord->szOffsets * sizeof(**pWord));
        }
        pWord->offsets[(*pWord)->count] = (unsigned long) str;

        return 0;
    }
}

// search a word in the dictionnary
struct dict_elt_t* dict_search_word (struct dict_t *dict, char *word, size_t szWord) {
    int check;
    struct dict_elt_t *word;
    struct dict_node_t *pWord;

    if (!anchor || !word)
        return NULL;    

    // word
    word = calloc(1, sizeof(*word));
    word->str = calloc(1, (szStr + 1) * sizeof(*str));
    memcpy (word->str, str, szStr * sizeof(*str));
    word->szStr = szStr + 1;
    word->count = 1;

    // search word
    pWord = binary_search_tree_search (dict, word);

    if (pWord)
        return pWord->data;
    else
        return NULL;
}

// build a dictionnary from a sequence of characters
// usefull to study frequency analysis
struct dict_elt* dict_build_static_size (struct dict_t **dict, char *str, size_t szStr, size_t szToken) {
    char *pStr;

    // check string validity
    if (!dict || !str || !szStr || !szToken)
        return NULL;

    // we construct dictionary
    pStr = str;
    while (pStr < str + szStr - 1) {
        dict_insert_word(dict, pStr, szToken);
        pStr++;
    }

    return *dict;
}

// build a dictionnary from a sequence of characters
struct dict_elt* dict_build (struct dict_elt **dict, char *str, size_t szStr, size_t szTokenMax) {
    size_t i;

    // check string validity
    if (!dict || !str || !szStr || !szTokenMax)
        return NULL;

    for (i = 1; i <= szTokenMax; i++)
        dict_build_static_size (dict, str, szStr, i);

    return *dict;
}

// compute distance between equal words
struct dict_elt_t *dict_distance_stub (struct dict_t *dict, struct dict_node_t *word) {
    size_t i;

    if (dict && word) {
        dict_distance_stub (dict, word->left);
        // if there
        if (word->count <= 1) {
            for (i = 1; i < word->count; i++) {
                if (word->offsets[i] > word->offsets[i-1])
                    word->offsets[i] -= word->offsets[i-1];
                else
                    word->offsets[i] = word->offsets[i-1] - word->offsets[i];
            }
        }
        dict_distance_stub (dict, word->right);
    }
}

// compute distance between equal words
struct dict_t *dict_distance (struct dict_t *dict) {
    if (!dict)
        return NULL;
    
    dict_distance_stub (dict, dict->left);
    dict_distance_stub (dict, dict->right);

    return dict;
}

//
struct dict_elt *dict_search_highest_occurrences (struct dict_elt *dict, struct dict_elt_t **node) {
    int check;
    int (*dict_compare_count) (void *dict1, void *dict2);

    // if invalid node pointer given
    // then we exit
    if (!node || !dict)
        return NULL;

    if (dict)
        *node = binary_search_tree_search_node (dict, node);

    return *node;
}



// callbacks

int dict_compare_str (void *dict1, void *dict2) {
    int check = 1;
    struct dict_elt *pDict1, *pDict2;

    if (!dict1 || !dict2)
        return -1;

    pDict1 = dict1;
    pDict2 = dict2;

    if (pDict1->szStr != pDict2->szStr)
        return pDict1->szStr - pDict2->szStr;

    check = memcmp (pDict1->str, pDict2->str, pDict1->szStr);
    return check;
}

int dict_compare_count (void *dict1, void *dict2) {
    struct dict_elt *pDict1, *pDict2;
    int check;

    if (!dict1 || !dict2)
        return -1;

    pDict1 = dict1;
    pDict2 = dict2;


    if (pDict1->count == pDict2->count)
        check = dict_compare_str (dict1, dict2);
    else
        check = pDict1->count - pDict2->count;

    return check;
}

void dict_destroy (void *dict) {
    struct dict_elt *pDict;

    if (!dict)
        return;

    free(pDict->str);
    free(pDict->offsets);
    free(pDict->description);
}

size_t dict_get_size (void *dict) {
    return sizeof(struct dict_elt);
}

void dict_show_str (void *dict) {
    if (dict) {
        if (((struct dict_elt *)dict)->str) {
            //printf("dict->str : %s\n", dict->str);
            //printf("    count : %u\n", dict->count);
            printf("%s\n", ((struct dict_elt *)dict)->str);
        }
    }
}

