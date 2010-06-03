#ifndef _ARBRES_H
#define _ARBRES_H

/*! @brief Fonctions pour un dictionnaire dans un arbre */

/*! @brief Structure dictionnaire en utilisant les arbres n-aires
*/
struct dict_t
{
    /*! Caractere */
    char c;
    /*! Fils frere */
    struct dict_t *frere;
    /*! Fils */
    struct dict_ *fils;
};

// dictionnary : insert a word
struct dict_t* dict_insert_word (struct dict_t **anchor, char *word);
// search a word in the dictionnary
char *dict_search_word (struct dict_t *anchor, char *word,
                     char *recherche, size_t i);
// search a word in the dictionnary
char *dict_search_word (struct dict_t *anchor, char *word,
                     char *recherche, size_t i);
// load a dictionnary file
struct dict_t *dict_load (char *dict_filename);
// dictionnary : save to a file
int dict_save (char *dict_file, struct dict_t *dict);

#endif
