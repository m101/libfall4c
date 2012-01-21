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
#include <ctype.h>

// depedencies
#include <unac.h>

#include "string_ext.h"

// secure string length
size_t string_len (struct string_t *str) {
    if (str)
        return str->size;
    else
        return -1;
}

// secure string copy
struct string_t* string_cpy (struct string_t *dst, struct string_t *src) {
    // pointer check
    if (!dst || !src)
        return NULL;

    // size check
    if (src->size < 1)
        return NULL;

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity < src->size) {
        dst->capacity = src->size;
        dst->bytes = realloc (dst->bytes, dst->capacity);
    }

    // we copy string
    strncpy (dst->bytes, src->bytes, src->size);
    dst->bytes[dst->size - 1] = '\0';

    return dst;
}

// secure string concatenation
struct string_t* string_cat (struct string_t *dst, struct string_t *src) {
    // pointer check
    if (!dst || !src)
        return NULL;

    // size check
    if (src->size < 1)
        return NULL;

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity < dst->size + src->size) {
        dst->capacity = dst->size + src->size;
        dst->bytes = realloc (dst->bytes, dst->capacity);
    }

    // we copy string
    strncat (dst->bytes, src->bytes, src->size);
    dst->bytes[dst->size - 1] = '\0';

    return dst;
}

// secure string comparison
int string_cmp (struct string_t *str1, struct string_t *str2) {
    int sz;

    // get the smaller size
    if (str1->size > str2->size)
        sz = str2->size;
    else 
        sz = str1->size;

    return strncmp (str1->bytes, str2->bytes, sz);
}

int string_word_delete (char *str, char *word) {
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

// separate a string in its column components
char** string_get_columns (char *str, int len, int nColumns) {
    // multiple len and rest len
    int mLen, rLen;
    // indexes
    int idxStr, idxAlpha;
    // string table
    char **cstr;

    // allocate the ciphertext space
    cstr = calloc(nColumns, sizeof(*cstr));
    if (!cstr)
        return NULL;

    // calculate
    rLen = len % nColumns;
    mLen = len - rLen;
    mLen = mLen / nColumns;

    // construct the different strings
    for (idxAlpha = 0; idxAlpha < nColumns; idxAlpha++) {
        cstr[idxAlpha] = calloc(mLen + 2, sizeof(**cstr));
        for (idxStr = 0; idxStr < mLen; idxStr++) {
            // cstr[idxAlpha][idxStr] = str[idxStr * nColumns + idxAlpha];
            cstr[idxAlpha][idxStr] = str[idxAlpha * nColumns + idxStr];
        }
    }

    // end the different strings
    for (idxAlpha = 0; idxAlpha < rLen; idxAlpha++) {
        for (idxStr = mLen; idxStr < mLen + 1; idxStr++) {
            // cstr[idxAlpha][idxStr] = str[idxStr * nColumns + idxAlpha];
            cstr[idxAlpha][idxStr] = str[idxAlpha * nColumns + idxStr];
        }
        // printf("cstr: '%s'\n", cstr[idxAlpha]);
    }

    return cstr;
}

// normalize string to ascii (no accent, etc)
char *normalize_str (char *str, int szStr) {
    int idxStr, idxNew;
    // normalized string
    char *normalized = NULL;
    size_t sznormalized = 0;
    // return code
    int rc;

    // check ptrs
    if (!str || szStr <= 0)
        return NULL;

    // remove all accents and diacritics
    // ISO646-US === ASCII
    rc = unac_string("ISO646-US", str, szStr, &normalized, &sznormalized);
    if (rc < 0)
        fatal("normalize_str():Error: Failed removing accents\n");
    // printf("normalize_str():normalized: '%s'\n", normalized);

    // toupper string
    for (idxStr = 0, idxNew = 0; idxStr < sznormalized; idxStr++) {
        if (isalpha(normalized[idxStr])) {
            normalized[idxNew++] = toupper(normalized[idxStr]);
        }
    }
    normalized[idxNew] = '\0';

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

  while (head < tail)
  {
    *head = *tail;
    head++;
    tail--;
  }

  return str;
}
