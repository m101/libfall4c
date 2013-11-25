/*
    libbparse - Binary file parser library
    Copyright (C) 2010  m_101

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "escape.h"

// escape bytes
unsigned char* escape_hex (unsigned char *bytes, size_t nbytes)
{
        unsigned char *escaped;
        char *pEscaped;

        escaped = calloc(nbytes * 4 + 1, sizeof(*escaped));

        pEscaped = escaped;
        while (nbytes)
        {
                snprintf(pEscaped, 5, "\\x%02x", *bytes & 0xff);
                pEscaped += 4;
                bytes++;
                nbytes--;
        }

        return escaped;
}

// unescape escaped hex
unsigned char *unescape_hex (char *str, size_t sz_str)
{
    unsigned char *unescaped;
    unsigned short int *pUnescaped, n_separators, n_characters;

    if (!str || !sz_str || sz_str % 4 != 0)
        return NULL;

    unescaped = calloc (sz_str / 4, sizeof(*unescaped));
    pUnescaped = unescaped;

    n_separators = 0, n_characters = 0;
    while (*str) {
        // must be hex digit or '\' or 'x' char
        // else we stop parsing and there was an error
        if ( ((*str < 'A' || *str > 'F') && (*str < 'a' || *str > 'f'))
                || *str != '\\' || *str != 'x')
            break;
        //
        if (*str == '\\' || *str == 'x') {
            n_separators++;
            n_characters = 0;
            continue;
        }

        if (n_characters > 2)
            break;
        if (n_separators > 2)
            break;
        else if (n_separators == 2) {
            *pUnescaped = hexstr_to_num (str, 2);
            str += 2;
            pUnescaped++;
            n_characters += 2;
        }
        n_separators = 0;
    }

    if (n_separators > 2)
        free (unescaped), unescaped = NULL;

    return unescaped;
}

