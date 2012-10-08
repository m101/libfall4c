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
#include <math.h>
#include <ctype.h>

#include "ctype_extended.h"

long l_round (double value)
{
    long rounded = 0;

    if (abs(value - (long)value) >= 0.5)
        rounded = ceil(value);
    else if (abs(value - (long)value) < 0.5)
        rounded = floor(value);

    return rounded;
}

/*! @brief               Convertit une chaine en majuscule
*
*   @param   string      Chaine à convertir
*   @return              Renvoi l'adresse de la chaine convertie
*/
char *str_toupper (char *string)
{
    char *str = strdup(string);
    char *ptr = str;

    if (!str)
        return NULL;

    while (*ptr) {
        *ptr = toupper(*ptr);
        ptr++;
    }

    return str;
}

/*! @brief               Convertit une chaine en minuscule
*
*   @param   string      Chaine à convertir
*   @return              Renvoi l'adresse de la chaine convertie
*/
char *str_tolower (char *string)
{
    char *str = strdup(string);
    char *ptr = str;

    if (!str)
        return NULL;

    while (*ptr) {
        *ptr = tolower(*ptr);
        ptr++;
    }

    return str;
}

