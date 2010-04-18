#ifndef CTYPE_H
#define CTYPE_H

#include <stdio.h>
#include <stdlib.h>

/*! @file c_type_extended.h
*   @brief Fonctions supplémentaires de conversion de type
*/

typedef unsigned char u8;

long l_round (double value);
// Convertit une chaine en majuscule
char* stringtoupper (char string[]);
// Convertit une chaine en minuscule
char* stringtolower (char string[]);

#endif
