#include <stdio.h>
#include <stdlib.h>

#include "data/dictionnary.h"

#define DICTIONNARY_NAME    "dictionnaire.txt"

int main(int argc, char *argv[])
{
    struct dict_t *dict = NULL;

    dict = dict_load (DICTIONNARY_NAME);
    if (!dict) {
        fprintf(stderr, "error: Failed to load dictionnary '%s'\n", DICTIONNARY_NAME);
    }

    dict_show (dict);

    return 0;
}

