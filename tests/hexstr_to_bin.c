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
#include <stdint.h>
#include <string.h>

#include "util/debug.h"
#include "string_ext.h"

#define HEXSTR  "0x0xdeadbeefcafebabef"

int main (int argc, char *argv[])
{
    uint8_t *bin;
    char *hexstr;
    int len_hexstr;

    if (argc < 2) {
        printf (
                "hexstr_to_bin  Copyright (C) 2012  m_101\n"
                "This program comes with ABSOLUTELY NO WARRANTY.\n"
                "This is free software, and you are welcome to redistribute it\n"
                "under certain conditions.\n\n"
               );
        printf("Usage: %s hexstr\n", argv[0]);
        exit(1);
    }

    hexstr = strdup(argv[1]);
    len_hexstr = strlen(hexstr);
    bin = hexstr_to_bin(hexstr, len_hexstr);
    if (!bin) {
        fprintf(stderr, "error: Failed to convert\n");
        exit(1);
    }

    printf("original: '%s'\n", hexstr);
    dump(bin, hexstr_count_digits(hexstr, len_hexstr), 16);

    free(hexstr);

    return 0;
}

