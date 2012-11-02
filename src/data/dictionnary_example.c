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

#include "data/dictionnary.h"

#define DICTIONNARY_NAME    "dictionnaire.txt"

int main(int argc, char *argv[])
{
    struct dict_t *dict = NULL;

    dict = dict_load (DICTIONNARY_NAME);
    if (!dict) {
        fprintf(stderr, "error: Failed to load dictionnary '%s'\n", DICTIONNARY_NAME);
    }

    dict_show (dict);

    return 0;
}

