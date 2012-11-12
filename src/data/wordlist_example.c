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

#include "data/wordlist.h"

#define WORDLIST_NAME    "wordlist.txt"

int main(int argc, char *argv[])
{
    struct wlist_t *wlist = NULL;

    wlist = wlist_load (WORDLIST_NAME);
    if (!wlist) {
        fprintf(stderr, "error: Failed to load wordlist '%s'\n", WORDLIST_NAME);
    }

    wlist_show (wlist);

    return 0;
}

