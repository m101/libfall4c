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

#include "string.h"

// secure string length
size_t string_len (string_t *str) {
    if (str)
        return str->szString;
    else
        return -1;
}

// secure string copy
string_t* string_cpy (string_t *dst, string_t *src) {
    // new size
    size_t nsize;

    // pointer check
    if (!dst || !src)
        return NULL;

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity < src->szString) {
        dst->capacity = src->szString;
        dst->string = realloc (dst->string, dst->capacity);
    }

    // we copy string
    strncpy (dst->string, src->string, src->szString);
    dst->string[dst->szString - 1] = '\0';

    return dst;
}

// secure string concatenation
string_t *string_cat (string_t *dst, string_t *src) {
    // new size
    size_t nsize;

    // pointer check
    if (!dst || !src)
        return NULL;

    // if buffer isn't big enough
    // then allocate an adapted one
    if (dst->capacity < dst->szString + src->szString) {
        dst->capacity = dst->szString + src->szString;
        dst->szString = realloc (dst->string, dst->capacity);
    }

    // we copy string
    strncat (dst->string, src->string, src->szString);
    dst->string[dst->szString - 1] = '\0';

    return dst;
}

string_t string_cmp (string_t *str1, string_t str2) {
    if (str1->size != str2->size)
        return *(str1->bytes) - *(str2->bytes);

    return strncmp (str1->bytes, str2->bytes, str1->szString);
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

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		*lasts = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
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
	/* NOTREACHED */
}

