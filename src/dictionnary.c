#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "arbres.h"

#define BUFFER_SIZE 1000

// dictionnary : insert a word
struct dict_t* dict_insert_word (struct dict_t **anchor, char *word) {
    // pointers check
    if (!word)
        return NULL;
    if (!anchor)
        return NULL;
    if (!*anchor)
        *anchor = calloc( 1, sizeof(struct dict_t) );

    // insert caracter as long as it's not NULL
    if (*word != '\0') {
        (*anchor)->c = *word;
        if ((*anchor)->c > *word)
            dict_insert_word(&((*anchor)->fils), word + 1);
        else if ((*anchor)->c < *word)
            dict_insert_word(&((*anchor)->frere), word + 1);
    }
    // stop insertion
    else {
        (*anchor)->c = '\0';
        return *anchor;
    }
}

// search a word in the dictionnary
char *dict_search_word (struct dict_t *anchor, char *word,
                     char *recherche, size_t i) {
    // pointer check
    if (anchor == NULL)
        return 0;
    // Si la lettre du noeud courant est apres la lettre courante du word
    // Alors on a un echec
    if (anchor->c > word[i])
        return 0;
    // Si le caractere du noeud courant correspond a la lettre courante du word
    // Alors on stocke dans recherche et on appel recursivement la fonction
    else if (anchor->c == word[i])
    {
        recherche[i] = word[i];
        dict_search_word (anchor->fils, word, recherche, i + 1);
    }
    // Sinon on continue a parcourir le word
    else if (anchor->c > word[i])
    {
        dict_search_word (anchor->frere, word, recherche, i + 1);
    }
    // if word is in dictionnary
    if (strcmp(word, recherche))
        return recherche;
    // we arrived at the end of the word
    if (anchor->c == '\0')
        return 0;
}

// load a dictionnary file
struct dict_t *dict_load (char *dict_filename)
{
    struct dict_t *dict = NULL;
    FILE *dict_file = NULL;
    char *buffer = malloc(sizeof(*buffer) * BUFFER_SIZE);
    int nbword = 0;

    // pointers check
    if (!dict_filename)
        return NULL;

    dict_file = fopen(dict_filename, "r");

    // we get number of words
    fgets(buffer, BUFFER_SIZE * sizeof(*buffer), dict_file);
    nbword = atoi(buffer);

    // dict load
    // we construct the tree
    while (fgets(buffer, BUFFER_SIZE * sizeof(*buffer), dict_file))
        inserer_word(&dict, buffer);

    // cleaning up
    fclose(dict_file);
    free(buffer);

    return dict;
}

// dictionnary : save to a file
int dict_save (char *dict_file, struct dict_t *dict)
{
    FILE *file = NULL;

    // pointers check
    if ( (dict_file == NULL) || (dict == NULL) )
        return 0;
    else
    {
        // Parcours de l'arbre recursivement
        // Sauvegarde du word
    }
}

// show dictionnary
void dict_show (struct dict_t *dict)
{
    if (!dict)
    {
        fprintf (stderr, "Error: %s", "Dict not initialised");
        return;
    }
    else
    {
        printf("%c", dict->c);
        afficher_arbre(dict->fils);
        afficher_arbre(dict->frere);
    }
}
