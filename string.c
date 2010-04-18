#include <stdio.h>
#include <stdlib.h>

#include "string.h"

long strlen(char *string)
{
    char *pChaine = string;

    while (*pChaine != '\0')
    {
        pChaine++;
    }

    return pChaine - string;
}

char* strcpy(char* copieDeLaChaine, const char* chaineACopier)
{
    while (*chaineACopier)
    {
        *copieDeLaChaine = *chaineACopier;
        chaineACopier++;
        copieDeLaChaine++;
    }
    *copieDeLaChaine = '\0';

    return copieDeLaChaine;
}

char* strcat(char* chaine1, const char* chaine2)
{
    long i = 0;

    if (strlen(chaine1) > strlen(chaine2))
    {
        for (i = (strlen(chaine1) - strlen(chaine2)); i < strlen(chaine1); i++)
        {
            chaine1[i] = chaine2[i];
        }
    }
    else
    {
        exit(0);
    }

    return chaine1;
}

char *strchr (const char *str, int c)
{
    if(!str)
        return NULL;

    while (*str)
    {
        if (*str == c)
            return str;
        str++;
    }

    return NULL;
}

int strcmp (char *str1, char *str2)
{
    /* working code
    while ( *str1 && *str2 )
    {
        if ( *str1 != *str2 )
            return *str1 - *str2;
        str1++, str2++;
    }
    //*/

    while ( (*str1 == *str2) && *str1 )
        str1++, str2++;

    return *str1 - *str2;
}

//( int value, char * str, int base );
void inttostring(int entier, char *str, int i)
{
    char *strTemp = str;

    if (entier/10)
    {
        strTemp = str + sizeof(*str);
        inttostring(entier/10, strTemp--, ++i);

        *str = entier % 10 + '0';

        printf("Appel recursif %d, str : %p, c : %c\n", i, str, *str);
    }
    else
    {
        ++i;
        *str = entier + '0';
        *(str+1) = '\0';

        printf("Appel recursif %d, str : %p, c : %c\n", i, str, *str);
    }
}

unsigned long string_length (char *str)
{
    return string_length_r (str, 0);
}

unsigned long string_length_r (char *str, int i)
{
    if (*str != '\0')
    {
        i = string_length_r(++str, ++i);
    }

    return i;
}

void reverse_count (int number)
{
    if (number >= 0)
    {
        printf("%d ", number);
        reverse_count(--number);
    }
}

void reverse_string (char *string)
{
    char c = 0;

    if (*string != '\0')
    {
        reverse_string(++string);
    }
}

// To use with fgets
void clean(char *chaine)
{
    char *retourCharriot = strchr(chaine, '\n' );
    char *retourArriere = strchr(chaine, '\r' );

    if (retourCharriot)
    {
        *retourCharriot = 0;
    }
    else
    {
        purger();
    }
    if (retourArriere)
    {
        *retourArriere = 0;
    }
}

void purger(void)
{
    while ( (getchar() != '\n') && (getchar() != EOF));
}

// Reading
void read (size_t bufferLength)
{
    char input = 0;
    size_t size = bufferLength;
    size_t i = 0;

    char *string = malloc(sizeof(*string) * bufferLength);
    if (string != NULL)
    {
        while ((input = getchar()) != '\n')
        {
            if ((input != '\n') && (input != '\r'))
            {
                string[i] = input;
            }
            else if (i >= size)
            {
                string = realloc(string, sizeof(*string) + 10);
                if (string == NULL)
                {
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void initialisationChaine (char chaine[])
{
    while (*chaine)
    {
        *chaine = 0;
        chaine++;
    }
}

long* readNumber (size_t bufferLength)
{
    char input = 0;
    size_t size = bufferLength;
    size_t i = 0;

    long *string = malloc(sizeof(*string) * bufferLength);
    if (string != NULL)
    {
        while ((input = getchar()) != '\n')
        {
            if (i >= size)
            {
                string = realloc(string, sizeof(*string) + 10);
                if (string == NULL)
                {
                    exit(EXIT_FAILURE);
                }
            }
            else if ((input >= '0') && (input <= '9'))
            {
                string[i] = input - '0';
                i++;
            }
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return string;
}

long stringLength (char string[])
{
    char *p = string;

    while (*string)
    {
        string++;
    }

    return string - p;
}

int string_word_delete (char *str, char *word)
{
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

