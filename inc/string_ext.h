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

#include <stdint.h>

    struct string_t {
        uint64_t hash;
        // string
        char *bytes;
        // size of string
        int size;
        // size of allocated space
        int capacity;
    };
    
    // init string
    struct string_t *string_set (struct string_t **dst, char *str);
    // destroy string
    void string_destroy (struct string_t **str);
    // secure string copy
    struct string_t *string_cpy (struct string_t *dst, struct string_t *src);
    // secure string concatenation
    struct string_t *string_cat (struct string_t *dst, struct string_t *src);
    // secure string comparison
    int string_cmp (struct string_t *str1, struct string_t *str2);
    // puts
    int string_puts (struct string_t *str);
    // putsln
    int string_putsln (struct string_t *str);

    // str functions
    // delete a word in a string
    int str_word_delete (char *str, char *word);
    // separate a string in its column components
    char **str_get_columns (char *str, int len, int n_columns);
    // normalize string to ascii (no accent, etc)
    char *str_normalize (char *str, int sz_str);
    
    // hashing functions
#define str_hash(str, len)    fnv_hash(str, len)
    // djb2 hashing algorithm
    unsigned long djb2_hash (unsigned char *str, int len);
    // FNV-1a hashing algorithm
    uint64_t fnv_hash (uint8_t *str, int len);

    /*
    char *_DEFUN (strtok_r, (s, delim, lasts),
                	register char *s _AND
                	register const char *delim _AND
                	char **lasts);
    */
    int binstr_count_digits (char *binstr, int len_binstr);
    // uint8_t *binstr_to_bin (char *binstr, int len_binstr);
    uint8_t *hexstr_to_bin (char *hexstr, int len_hexstr);
    uint8_t *bin_to_hexstr (char *bin, int len_bin);
#ifdef __cplusplus
}
#endif

#endif /* _STRINGMANIPULATION_H */

