#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int string_word_delete (char *str, char *word)
{
    char *p, *space;
    
    p = strstr(str, word);
    if (!p)
        return -1;
    
    space = strchr(p, ' ');
    
    if (space)
        strcpy(p, space);
    else
        return -1;
    
    return 0;
}

