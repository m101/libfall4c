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
#include <unac.h>

#include "string_ext.h"
#include "ctype_extended.h"

// init string
struct string_t *string_set (struct string_t **dst, char *str)
{
    if (!dst) {
        fprintf (stderr, "error: string_cat(): Bad parameter\n");
        return NULL;
    }

    *dst = calloc(1, sizeof(**dst));
    if (!*dst)
        return NULL;

    (*dst)->size = strlen(str);
    (*dst)->capacity = (*dst)->size + 1;
    if ((*dst)->bytes)
        free((*dst)->bytes);
    (*dst)->bytes = calloc((*dst)->capacity, sizeof(*(*dst)->bytes));
    if (!(*dst)->bytes)
        return NULL;

    strncpy((*dst)->bytes, str, (*dst)->size);

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
        fprintf (stderr, "error: string_cat(): Bad parameter(s)\n");
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
    // pointer check
    if (!dst || !src) {
        fprintf (stderr, "error: string_cat(): Bad parameter(s)\n");
        return NULL;
    }

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity < dst->size + src->size) {
        dst->capacity = dst->size + src->size + 1;
        dst->bytes = realloc (dst->bytes, dst->capacity);
    }

    // we concatenate strings
    strncat (dst->bytes, src->bytes, src->size);
    dst->bytes[dst->size - 1] = '\0';

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

    // allocate the ciphertext space
    cstr = calloc(n_columns, sizeof(*cstr));
    if (!cstr)
        return NULL;

    // calculate
    r_len = len % n_columns;
    m_len = len - r_len;
    m_len = m_len / n_columns;

    // construct the different strings
    for (idx_alpha = 0; idx_alpha < n_columns; idx_alpha++) {
        cstr[idx_alpha] = calloc(m_len + 2, sizeof(**cstr));
        for (idx_str = 0; idx_str < m_len; idx_str++) {
            // cstr[idx_alpha][idx_str] = str[idx_str * n_columns + idx_alpha];
            cstr[idx_alpha][idx_str] = str[idx_alpha * n_columns + idx_str];
        }
    }

    // end the different strings
    for (idx_alpha = 0; idx_alpha < r_len; idx_alpha++) {
        for (idx_str = m_len; idx_str < m_len + 1; idx_str++) {
            // cstr[idx_alpha][idx_str] = str[idx_str * n_columns + idx_alpha];
            cstr[idx_alpha][idx_str] = str[idx_alpha * n_columns + idx_str];
        }
        // printf("cstr: '%s'\n", cstr[idx_alpha]);
    }

    return cstr;
}

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

/*
char *
_DEFUN (strtok_r, (s, delim, lasts),
	register char *s _AND
	register const char *delim _AND
	char **lasts)
{
	register char *spanp;
	register int c, sc;
	char *tok;


	if (s == NULL && (s = *lasts) == NULL)
		return (NULL);

	 // Skip (span) leading delimiters (s += strspn(s, delim), sort of).
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

    // no non-delimiter characters
	if (c == 0) {		
		*lasts = NULL;
		return (NULL);
	}
	tok = s - 1;

	 // Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 // Note that delim must have one NUL; we stop if we see that, too.
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*lasts = s;
				return (tok);
			}
		} while (sc != 0);
	}
	// NOTREACHED
}
//*/

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

int binstr_count_digits (char *binstr, int len_binstr)
{
    int idx_binstr, max_bin;

    if (!binstr || len_binstr <= 0) {
        fprintf (stderr, "error: binstr_count_digits(): Bad parameter(s)\n");
        return -1;
    }

    for (idx_binstr = 0, max_bin = 0; idx_binstr < len_binstr; idx_binstr++) {
        if (isxdigit(binstr[idx_binstr]))
            max_bin++;
    }

    return max_bin;
}

/* @desc    convert binstr to binary
 */
uint8_t *hexstr_to_bin (char *hexstr, int len_hexstr)
{
    int idx_hexstr, idx_digit, idx_bin, max_bin;
    uint8_t hexnum, hexdigit;
    uint8_t *bin;

    max_bin = binstr_count_digits (hexstr, len_hexstr);
    if (max_bin <= 0) {
        fprintf(stderr, "error: binstr_to_bin(): count is 0\n");
        return NULL;
    }

    bin = calloc(max_bin, sizeof(*bin));
    if (!bin) {
        fprintf(stderr, "error: binstr_to_bin(): failed to allocated memory for binary\n");
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

uint8_t *bin_to_hexstr (char *bin, int len_bin)
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

    printf ("info : bin_to_hexstr(): hexstr (before): '%s'\n", hexstr);
    p_hexstr = hexstr;
    for (idx_bin = 0; idx_bin < len_bin; idx_bin++) {
        hexdigit = bin[idx_bin];
        snprintf(p_hexstr, 3, "%02x", hexdigit & 0xff);
        p_hexstr += 2;
    }
    printf ("info : bin_to_hexstr(): hexstr (after) : '%s'\n", hexstr);

    return hexstr;
}

