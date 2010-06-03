#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "arbres.h"

#define BUFFER_SIZE 1000

// insert a word
int dict_insert_word (struct dict_t **dict, char *str, size_t szStr) {
    int check;

    // check for string validity
    if (!str || !szStr)
        return 0;
    // check for dictionnary double pointer validity
    if (!dict)
        return 0;

    // if we are at a leaf node
    // then we can insert the data
    if (!(*dict)) {
        // we allocate a node
        *dict = calloc(1, sizeof(*dict));
        // we allocate enough space for string
        (*dict)->str = calloc(1, szStr * sizeof(*str) + 1);
        // we make sure the string is zeroed out
//        bzero((*dict)->str, szStr * sizeof(*str) + 1);
        // we insert the string
        memcpy ( (*dict)->str, str, szStr * sizeof(*str) );
        // we initialize all variable to ensure correct behavior
        (*dict)->szStr = szStr;
        (*dict)->count = 1;
        (*dict)->right = NULL;
        (*dict)->left = NULL;

        return 1;
    }

    // compare strings
    check = memcmp((*dict)->str, str, szStr);

    // insertion
    if ( check > 0 )
        return dictionnary_insert ( &((*dict)->right), str, szStr);
    else if ( check < 0 )
        return dictionnary_insert ( &((*dict)->left), str, szStr);
    else {
        (*dict)->count++;
        return 1;
    }

    return 0;
}

// search a word in the dictionnary
struct dict_t* dict_search_word (struct dict_t *anchor, char *word) {
    int check;

    if (!anchor || !word)
        return NULL;

    check = strcmp (anchor->str, word);
    // found
    if (check == 0)
        return anchor;
    else if (check < 0)
        return dict_search_word (anchor->left, word);
    else
        return dict_search_word (anchor->right, word);
}

// build a dictionnary from a sequence of characters
// usefull to study frequency analysis
struct dict_t* dictionnary_build (char *str, size_t szStr, size_t szToken) {
    struct dict_t *dict;
    char *pStr;

    // check string validity
    if (!str || !szStr || !szToken)
        return NULL;

    // we construct dictionary
    pStr = str, dict = NULL;
    while (pStr < str + szStr - 1) {
        dictionnary_insert(&dict, pStr, szToken);
        pStr++;
    }

    return dict;
}

//
struct dict_t *dictionnary_search_highest_occurrences (struct dict_t *dict, struct dict_t **node) {
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
            dictionnary_search_highest_occurrences(dict->right, node);
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
            dictionnary_search_highest_occurrences(dict->left, node);
        }
    }

    return *node;
}

