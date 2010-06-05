#ifndef _DICTIONNARY_H
#define _DICTIONNARY_H

#define POINTERS_NB     32

// dictionnary structure
struct dict_t {
    //
    char *str;
    size_t szStr;
    //
    char *description;
    //
    size_t count;
    //
    unsigned long *pointers;
    size_t szPointers;
    //
    struct dict_t *left, *right;
};

// destroy dictionnary recursively
void dict_destroy (struct dict_t **dict);
// dictionnary : insert a word
int dict_insert_word (struct dict_t **dict, char *str, size_t szStr);
// search a word in the dictionnary
struct dict_t* dict_search_word (struct dict_t *anchor, char *word, size_t szWord);
// search if there is at least one dupe
struct dict_t* dict_find_dupe (struct dict_t *dict, char *word, size_t szWord, size_t *count);
// find and destroy duplicates
struct dict_t* dict_destroy_dupes (struct dict_t **dict, char *word, size_t szWord);
// build a dictionnary from a sequence of characters
struct dict_t* dict_build_static_size (struct dict_t **dict, char *str, size_t szStr, size_t szToken);
// build a dictionnary from a sequence of characters
struct dict_t* dict_build (struct dict_t **dict, char *str, size_t szStr, size_t szTokenMax);
// compute distance between equal words
struct dict_t *dict_distance (struct dict_t *dict);
//
struct dict_t *dict_search_highest_occurrences (struct dict_t *dict, struct dict_t **node);
// load a dictionnary file
// struct dict_t *dict_load (char *dict_filename);
// dictionnary : save to a file
// int dict_save (char *dict_file, struct dict_t *dict);
void dict_show (struct dict_t *dict);

#endif
