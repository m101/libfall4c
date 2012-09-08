/*
    This file is part of fall4c.

    fall4c is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fall4c is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with fall4c.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _STRINGMANIPULATION_H
#define _STRINGMANIPULATION_H

#include "util/errors.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct string_t {
        // string
        char *bytes;
        // size of string
        int size;
        // size of allocated space
        int capacity;
    };
    
    // secure string copy
    struct string_t* string_cpy (struct string_t *dst, struct string_t *src);
    // secure string concatenation
    struct string_t* string_cat (struct string_t *dst, struct string_t *src);
    // secure string comparison
    int string_cmp (struct string_t *str1, struct string_t *str2);
    // separate a string in its column components
    char** string_get_columns (char *str, int len, int nColumns);
    // normalize string to ascii (no accent, etc)
    char *normalize_str (char *str, int szStr);

    void clean(char *chaine);
    void purger(void);
    /*
    char *_DEFUN (strtok_r, (s, delim, lasts),
                	register char *s _AND
                	register const char *delim _AND
                	char **lasts);
    */
#ifdef __cplusplus
}
#endif

#endif /* _STRINGMANIPULATION_H */

