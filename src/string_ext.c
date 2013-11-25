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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

// depedencies
#ifdef __linux__
#include <unac.h>
#endif

#include "string_ext.h"
#include "ctype_extended.h"

// new string
struct string_t *string_new (void)
{
    struct string_t *string;

    return string_set (&string, "", 1);
}

// new string from str
struct string_t *string_new_from_str (char *str)
{
    struct string_t *string;

    return string_set (&string, str, strlen (str));
}

// init string
struct string_t *string_set (struct string_t **dst, char *str, int len)
{
    if (!dst || !str || (len <= 0)) {
        fprintf (stderr, "error: string_set(): Bad parameter\n");
        return NULL;
    }

    *dst = calloc(1, sizeof(**dst));
    if (!*dst)
        return NULL;

    (*dst)->size = len;
    (*dst)->capacity = (*dst)->size + 1;
    (*dst)->bytes = calloc((*dst)->capacity, sizeof(*(*dst)->bytes));
    if (!(*dst)->bytes) {
        fprintf (stderr, "error: string_set(): Failed allocation\n");
        return NULL;
    }

    memcpy ((*dst)->bytes, str, (*dst)->size);

    (*dst)->hash = fnv_hash ((*dst)->bytes, (*dst)->size);

    return *dst;
}

// destroy string
void string_destroy (struct string_t **str)
{
    if (!str || !*str) {
        fprintf (stderr, "error: string_destroy(): Bad parameter\n");
        return;
    }

    free ((*str)->bytes);
    free (*str);
    *str = NULL;
}

// get char *
char *string_to_cstr (struct string_t *str)
{
    if (!str)
        return NULL;
    return str->bytes;
}

// secure string length
size_t string_len (struct string_t *str)
{
    if (str)
        return str->size;
    else {
        fprintf (stderr, "error: string_len(): Bad parameter\n");
        return -1;
    }
}

// secure string copy
struct string_t *string_cpy (struct string_t *dst, struct string_t *src)
{
    // pointer check
    if (!dst || !src) {
        fprintf (stderr, "error: string_cpy(): Bad parameter(s)\n");
        return NULL;
    }

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity <= src->size) {
        dst->capacity = src->size + 1;
        dst->bytes = realloc (dst->bytes, dst->capacity);
    }

    // we copy string
    strncpy (dst->bytes, src->bytes, src->size);
    dst->bytes[dst->size - 1] = '\0';

    dst->hash = src->hash;

    return dst;
}

// secure string concatenation
struct string_t *string_cat (struct string_t *dst, struct string_t *src)
{
    if (!src) {
        fprintf (stderr, "error: string_cat(): Bad parameter(s)\n");
        return NULL;
    }

    return string_cat_cstr (dst, src->bytes, src->size);
}

struct string_t *string_cat_cstr (struct string_t *dst, char *src, int len)
{
    // pointer check
    if (!dst || !src || len <= 0) {
        fprintf (stderr, "error: string_cat_cstr(): Bad parameter(s)\n");
        return NULL;
    }

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity < dst->size + len) {
        dst->capacity = dst->size + len + 1;
        dst->bytes = realloc (dst->bytes, dst->capacity);
    }

    // we concatenate strings
    strncat (dst->bytes, src, len);
    dst->bytes[dst->capacity - 1] = '\0';
    dst->size += len;

    dst->hash = fnv_hash (dst->bytes, dst->size);

    return dst;
}

// secure string comparison
int string_cmp (struct string_t *str1, struct string_t *str2)
{
    if (!str1 || !str2) {
        fprintf (stderr, "error: string_cmp(): Bad parameter\n");
        return str1 - str2;
    }

    return str1->hash - str2->hash;
}

// puts
int string_puts (struct string_t *str)
{
    int idx_str;

    if (!str) {
        fprintf (stderr, "error: string_puts(): Bad parameter\n");
        return EOF;
    }

    if (string_check (str) == 0) {
        fprintf (stderr, "error: string_puts(): str not initialized correctly\n");
        return EOF;
    }

    for (idx_str = 0; idx_str < str->size; idx_str++) {
        if (isprint (str->bytes[idx_str]))
            putchar (str->bytes[idx_str]);
        else
            putchar ('.');
    }

    return 0;
}

// putsln
int string_putsln (struct string_t *str)
{
    string_puts (str);
    putchar ('\n');
}

// check string consistency
int string_check (struct string_t *str)
{
    if (!str)
        return 0;

    if (str->bytes == NULL || str->size > str->capacity)
        return 0;

    return 1;
}

/* hash string to an integer value */
unsigned long djb2_hash (unsigned char *str, int len)/*{{{*/
{
    int idx_str;
    unsigned long hash = 5381;

    idx_str = 0;
    while (idx_str < len) {
        hash ^= (((hash << 5) + hash) + str[idx_str]); /* hash * 33 + c */
        idx_str++;
    }

    return hash;
}/*}}}*/

// alternative FNV hash has better avalanche characteritics
uint64_t fnv_hash (uint8_t *str, int len)
{
    uint64_t hash;
    int idx_str;

    // offset basis
    hash = 14695981039346656037UL;
    for (idx_str = 0; idx_str < len; idx_str++) {
        hash ^= str[idx_str];
        hash *= 1099511628211UL;
    }

    return hash;
}

// remove starting and trailing spaces
char *str_strip (char *str, int len)
{
    char *tmp;
    int idx_str;

    if (!str || len <= 0)
        return NULL;

    tmp = calloc (len, sizeof(*tmp));
    if (!tmp)
        return NULL;

    // search for first non space character
    for (idx_str = 0; idx_str < len; idx_str++) {
        if (isspace (str[idx_str]) == 0) {
            break;
        }
    }

    // suppress prefixed spaces
    idx_str = (idx_str > len ? len : idx_str);
    if (idx_str != len)
        memcpy (tmp, str + idx_str, len - idx_str);
    else
        memcpy (tmp, str, len);

    // remove trailing blanks
    for (idx_str = len - 1; idx_str >= 0; idx_str--) {
        if (isspace (tmp[idx_str]))
            tmp[idx_str] = 0;
        else
            break;
    }

    return tmp;
}

// delete a word in a string
int str_word_delete (char *str, char *word)
{
    char *p, *space;

    p = strstr(str, word);
    if (!p) {
        fprintf (stderr, "error: str_word_delete(): Couldn't find word\n");
        return -1;
    }

    space = strchr(p, ' ');

    if (space)
        strcpy(p, space);
    else
        return -1;

    return 0;
}

// separate a string in its column components
char **str_get_columns (char *str, int len, int n_columns)
{
    // multiple len and rest len
    int m_len, r_len;
    // indexes
    int idx_str, idx_alpha;
    // string table
    char **cstr;

    if (!str || (len <= 0) || (n_columns <= 0)) {
        fprintf (stderr, "error: str_get_columns(): Bad parameter(s)\n");
        fprintf (stderr, "  str       :%p\n", str);
        fprintf (stderr, "  len       :%d\n", len);
        fprintf (stderr, "  n_columns :%d\n", n_columns);
        return NULL;
    }

    printf ("str_get_columns params:\n");
    printf ("  str       :%p\n", str);
    printf ("  len       :%d\n", len);
    printf ("  n_columns :%d\n", n_columns);

    // allocate the ciphertext space
    cstr = calloc(n_columns, sizeof(*cstr));
    if (!cstr)
        return NULL;

    // calculate
    r_len = len % n_columns;
    m_len = (len - r_len) / n_columns;

    // printf ("the string: '%s' (%d/%d)\n", str, strlen(str), len);

    // construct the different strings
    for (idx_alpha = 1; idx_alpha < n_columns; idx_alpha++) {
        cstr[idx_alpha] = calloc(m_len + 2, sizeof(**cstr));
        for (idx_str = 0; idx_str < m_len; idx_str++) {
            // cstr[idx_alpha][idx_str] = str[idx_str * n_columns + idx_alpha];
            cstr[idx_alpha][idx_str] = str[idx_alpha * n_columns + idx_str];
        }
    }

    // end the different strings
    cstr[0] = calloc(m_len + r_len + 2, sizeof(**cstr));
    for (idx_str = len - r_len; idx_str < len; idx_str++) {
        // cstr[idx_alpha][idx_str] = str[idx_str * n_columns + idx_alpha];
        cstr[0][idx_str] = str[idx_str];
    }

    return cstr;
}

#ifdef _unac_h
// normalize string to ascii (no accent, etc)
char *str_normalize (char *str, int szStr)
{
    size_t idx_str, idx_new;
    // normalized string
    char *normalized;
    size_t sz_normalized;
    // return code
    int rc;

    // check ptrs
    if (!str || szStr <= 0)
        return NULL;

    // remove all accents and diacritics
    // ISO646-US === ASCII
    normalized = NULL;
    sz_normalized = 0;
    rc = unac_string("ISO646-US", str, szStr, &normalized, &sz_normalized);
    if (rc < 0)
        fatal("error: str_normalize(): Failed removing accents\n");
    // printf("str_normalize():normalized: '%s'\n", normalized);

    // toupper string
    for (idx_str = 0, idx_new = 0; idx_str < sz_normalized; idx_str++) {
        if (isalpha(normalized[idx_str])) {
            normalized[idx_new++] = toupper(normalized[idx_str]);
        }
    }
    normalized[idx_new] = '\0';

    return normalized;
}
#endif

// replace char
char *str_replace_chr (char *str, int len, int chr, int rep)
{
    int idx_str;

    if (!str || len <= 0) {
        fprintf (stderr, "error: str_replace(): Bad parameter(s)\n");
        return NULL;
    }

    for (idx_str = 0; idx_str < len; idx_str++) {
        if (str[idx_str] == chr)
            str[idx_str] = rep;
    }

    return str;
}

char *str_reverse (char *str)
{
    char *head, *tail;

    head = str;
    tail = str + strlen(str) - 1;

    while (head < tail) {
        *head = *tail;
        head++;
        tail--;
    }

    return str;
}

// get a line from str
char *str_get_line (char *str, int len, char **endptr)
{
    int idx_str;
    char *src;
    char *line;
    int sz_line;

    if (!str || len <= 0) {
        fprintf (stderr, "error: str_get_line(): Bad parameter(s)\n");
        return NULL;
    }

    if (endptr && *endptr && *endptr <= str + len)
        src = *endptr;
    else
        src = str;

    // get line
    sz_line = 0;
    for (idx_str = 0; src + idx_str < str + len; idx_str++) {
        if ( src[idx_str] == '\r' && src[idx_str+1] == '\n' ) {
            idx_str += 2;
            break;
        }
        if (src[idx_str] == '\n') {
            idx_str++;
            break;
        }
        sz_line++;
    }

    if (sz_line == 0) {
        fprintf (stderr, "error: str_get_line(): sz_line is 0\n");
        return NULL;
    }

    // update endptr
    if (endptr)
        *endptr = src + idx_str;
    /*
       printf ("src        : '%s'\n", src);
       printf ("*endptr str: '%s'\n", *endptr);
       printf ("idx_str    : %d\n", idx_str);
    //*/

    // extract line
    line = calloc (sz_line, sizeof (*line));
    if (!line) {
        fprintf (stderr, "error: str_get_line(): Failed line allocation\n");
        return NULL;
    }
    memcpy (line, src, sz_line);

    return line;
}

// return a repeated string of 'byte'
char *str_repeat_byte (int byte, int n_repeat)
{
    char *bytes;

    if (n_repeat <= 0) {
        printf ("error: str_repeat_byte(): Bad parameter(s)\n");
        return NULL;
    }

    bytes = calloc (n_repeat, sizeof (*bytes));
    if (!byte || !bytes)
        return bytes;

    memset (bytes, byte, n_repeat);

    return bytes;
}

// return a repeated string of 'str'
char *str_repeat_str (char *str, int len, int n_repeat)
{
    char *bytes;
    int idx_repeat;

    if (!str || len <= 0 || n_repeat <= 0) {
        printf ("error: str_repeat_str(): Bad parameter(s)\n");
        return NULL;
    }

    if ( (len * n_repeat + 1) < len
            || (len * n_repeat + 1) < n_repeat) {
        printf ("error: str_repeat_str(): Integer overflow detected\n");
        return NULL;
    }

    bytes = calloc (len * n_repeat + 1, sizeof (*bytes));
    if (!bytes) {
        printf ("error: str_repeat_str(): bytes failed allocation\n");
        return bytes;
    }

    for (idx_repeat = 0; idx_repeat < n_repeat; idx_repeat++)
        memcpy (bytes + idx_repeat * len, str, len);

    return bytes;
}

int hexstr_count_digits (char *hexstr, int len_hexstr)
{
    int idx_hexstr, max_bin;

    if (!hexstr || len_hexstr <= 0) {
        fprintf (stderr, "error: hexstr_count_digits(): Bad parameter(s)\n");
        return -1;
    }

    for (idx_hexstr = 0, max_bin = 0; idx_hexstr < len_hexstr; idx_hexstr++) {
        if (isxdigit(hexstr[idx_hexstr]))
            max_bin++;
    }

    return max_bin;
}

/* @desc    convert hexstr to binary
*/
uint8_t *hexstr_to_bin (char *hexstr, int len_hexstr)
{
    int idx_hexstr, idx_digit, idx_bin, max_bin;
    uint8_t hexnum, hexdigit;
    uint8_t *bin;

    max_bin = hexstr_count_digits (hexstr, len_hexstr);
    if (max_bin <= 0) {
        fprintf(stderr, "error: hexstr_to_bin(): count is 0\n");
        return NULL;
    }

    bin = calloc(max_bin, sizeof(*bin));
    if (!bin) {
        fprintf(stderr, "error: hexstr_to_bin(): failed to allocated memory for binary\n");
        return NULL;
    }

    /* convert hexstr to bin and ignore unwanted chars */
    hexnum = 0;
    hexdigit = 0;
    idx_digit = 0;
    for (idx_hexstr = 0, idx_bin = 0; idx_hexstr < len_hexstr; idx_hexstr++) {
        if (!isxdigit(hexstr[idx_hexstr]))
            continue;

        // get decimal digit
        hexdigit = toupper(hexstr[idx_hexstr]) - '0';
        // get hex digit
        if (hexdigit >= 0xa)
            hexdigit -= 7;
        hexnum |= hexdigit;

        // store hex byte
        if (((idx_digit+1) % 2) == 0 || (idx_digit == max_bin - 1)) {
            // if last hex digit and odd number of digits
            // then shift left
            if ((idx_bin % 2) == 0 && (idx_bin == max_bin - 1))
                hexnum <<= 4;
            bin[idx_bin] = hexnum;
            ++idx_bin;
            hexnum = 0;
        }

        hexnum <<= 4;

        idx_digit++;
    }

    return bin;
}

uint8_t *bin_to_hexstr (uint8_t *bin, int len_bin)
{
    uint8_t hexdigit;
    int idx_bin;
    uint8_t *hexstr, *p_hexstr;

    if (!bin || len_bin <= 0) {
        fprintf (stderr, "error: bin_to_hexstr(): Bad parameters\n");
        return NULL;
    }

    hexstr = calloc (2 * len_bin + 1, sizeof(*hexstr));
    if (!hexstr) {
        fprintf (stderr, "error: bin_to_hexstr(): Failed allocating hex string\n");
        return NULL;
    }

    p_hexstr = hexstr;
    for (idx_bin = 0; idx_bin < len_bin; idx_bin++) {
        hexdigit = bin[idx_bin];
        snprintf(p_hexstr, 3, "%02x", hexdigit & 0xff);
        p_hexstr += 2;
    }

    return hexstr;
}

