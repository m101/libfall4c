#include <stdio.h>
#include <stdlib.h>

#include "data/dictionnary.h"

int main(int argc, char *argv[])
{
    struct dict_t *dictionnaire_arbre = NULL;

    dictionnaire_arbre = dict_load ("dictionnaire.txt");

    dict_show (dictionnaire_arbre);

    return 0;
}
