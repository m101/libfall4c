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

#ifndef CTYPE_H
#define CTYPE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*! @file c_type_extended.h
*   @brief Fonctions supplémentaires de conversion de type
*/

typedef unsigned char u8;

long l_round (double value);
// Convertit une chaine en majuscule
char* stringtoupper (char string[]);
// Convertit une chaine en minuscule
char* stringtolower (char string[]);

#ifdef __cplusplus
}
#endif


#endif
