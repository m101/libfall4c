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

#define string_get_size(str)    (str ? (str)->size : -1)
    
    // new string
    struct string_t *string_new (void);
    // new string from str
    struct string_t *string_new_from_str (char *str);
    // init string
    struct string_t *string_set (struct string_t **dst, char *str, int len);
    // destroy string
    void string_destroy (struct string_t **str);
    // get char *
    char *string_to_cstr (struct string_t *str);
    // secure string copy
    struct string_t *string_cpy (struct string_t *dst, struct string_t *src);
    // secure string concatenation
    struct string_t *string_cat (struct string_t *dst, struct string_t *src);
    // concatenation of cstr to string
    struct string_t *string_cat_cstr (struct string_t *dst, char *src, int len);
    // secure string comparison
    int string_cmp (struct string_t *str1, struct string_t *str2);
    // puts
    int string_puts (struct string_t *str);
    // putsln
    int string_putsln (struct string_t *str);
    // check string consistency
    int string_check (struct string_t *str);

    // hashing functions
#define str_hash(str, len)    fnv_hash(str, len)
    // djb2 hashing algorithm
    unsigned long djb2_hash (unsigned char *str, int len);
    // FNV-1a hashing algorithm
    uint64_t fnv_hash (uint8_t *str, int len);

    // str functions
    // remove starting and trailing spaces
    char *str_strip (char *str, int len);
    // delete a word in a string
    int str_word_delete (char *str, char *word);
    // separate a string in its column components
    char **str_get_columns (char *str, int len, int n_columns);
    // normalize string to ascii (no accent, etc)
    char *str_normalize (char *str, int sz_str);
    // replace char
    char *str_replace_chr (char *str, int len, int chr, int rep);
    // get a line from str
    char *str_get_line (char *str, int len, char **endptr);

    // return a repeated string of 'byte'
    char *str_repeat_byte (int byte, int n_repeat);
    // return a repeated string of 'str'
    char *str_repeat_str (char *str, int len, int n_repeat);
    
    int hexstr_count_digits (char *hexstr, int len_hexstr);
    uint8_t *hexstr_to_bin (char *hexstr, int len_hexstr);
    uint8_t *bin_to_hexstr (uint8_t *bin, int len_bin);

#ifdef _WIN32
#define strdup _strdup
#define snprintf _snprintf
#endif

#ifdef __cplusplus
}
#endif

#endif /* _STRINGMANIPULATION_H */

