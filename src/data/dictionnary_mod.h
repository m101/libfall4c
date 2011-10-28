#ifndef _DICTIONNARY_H
#define _DICTIONNARY_H

#define POINTERS_NB     32

#include "tree_common.h"

// dictionnary structure
typedef struct tree_t struct dict_t;
// dictionnary node
typedef struct tree_node_t struct dict_node_t;

// dictionnary data structure
struct dict_elt_t {
    size_t count;
    //
    char *str;
    size_t szStr;
    //
    unsigned long base;
    unsigned long *offsets;
    size_t szOffsets;
    //
    char *description;
    size_t szDescription;
};

// dictionnary : insert a word
int dict_insert_word (struct dict_t **dict, char *str, size_t szStr);
// search a word in the dictionnary
struct dict_t* dict_search_word (struct dict_t *anchor, char *word, size_t szWord);
// build a dictionnary from a sequence of characters
struct dict_t* dict_build_static_size (struct dict_elt **dict, char *str, size_t szStr, size_t szToken);
// build a dictionnary from a sequence of characters
struct dict_t* dict_build (struct dict_t **dict, char *str, size_t szStr, size_t szTokenMax);
// compute distance between equal words
struct dict_t *dict_distance (struct dict_t *dict);
//
struct dict_elt *dict_search_highest_occurrences (struct dict_t *dict, struct dict_elt **node);
// load a dictionnary file
// struct dict_elt *dict_load (char *dict_filename);
// dictionnary : save to a file
// int dict_save (char *dict_file, struct dict_elt *dict);

// callbacks
// functions
int dict_compare_str (void *dict1, void *dict2);
void dict_destroy (void *dict);
inline size_t dict_get_size (void *dict);
// view functions
void dict_show_str (void *dict);

#endif
