#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "ctype_extended.h"

long l_round (double value)
{
    long roundedValue = 0;

    if (abs(value - (long)value) >= 0.5)
        roundedValue = ceil(value);
    else if (abs(value - (long)value) < 0.5)
        roundedValue = floor(value);

    return roundedValue;
}

/*! @brief               Convertit une chaine en majuscule
*
*   @param   string      Chaine à convertir
*   @return              Renvoi l'adresse de la chaine convertie
*/
char* stringtoupper (char *string)
{
    while (*string)
    {
        *string = toupper(*string);
        //toupper(*string);
        string++;
    }

    return string;
}

/*! @brief               Convertit une chaine en minuscule
*
*   @param   string      Chaine à convertir
*   @return              Renvoi l'adresse de la chaine convertie
*/
char* stringtolower (char string[])
{
    while (*string)
    {
        *string = tolower(*string);
        string++;
    }

    return string;
}
