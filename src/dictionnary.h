#ifndef _ARBRES_H
#define _ARBRES_H

// dictionnary structure
struct dict_t
{
    //
    char *str;
    size_t szStr;
    //
    char *description;
    //
    size_t count;
    struct dict_t *left, *right;
};

// dictionnary : insert a word
int dict_insert_word (struct dict_t **dict, char *str, size_t szStr);
// search a word in the dictionnary
struct dict_t* dict_search_word (struct dict_t *anchor, char *word);
// load a dictionnary file
// struct dict_t *dict_load (char *dict_filename);
// dictionnary : save to a file
// int dict_save (char *dict_file, struct dict_t *dict);

#endif
