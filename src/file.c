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

/*! @brief                    Fonction copiant un fichier en mode texte
*   @param   dest             Fichier de copie
*   @param   src              Fichier a copier
*/
void file_copy (char *dest, char *src)
{
    FILE *fileRead = fopen(src, "r");
    FILE *fileCopy = fopen(dest, "w");
    char character = 0;

    if (fileRead != NULL)
    {
        if (fileCopy != NULL)
        {
            while ((character = fgetc(fileRead)) != EOF)
                fputc(character, fileCopy);
            fclose(fileCopy);
        }
        else
            printf("La copie de fichier a echoue\n");
        fclose(fileRead);
    }
    else
        printf("La copie de fichier a echoue\n");
}

/*! @brief                    Fonction récupérant une ligne de texte à partir d'un fichier
*   @param   line             Ligne à récupérer
*   @param   max              Taille du buffer à récupérer
*   @return                   La longueur de la ligne
*/
long check_file_emptiness (char *fileName)
{
    FILE *file = fopen(fileName, "r");
    unsigned long counter = 0;

    if (!file)
        fprintf(stderr, "Erreur : Ouverture du fichier a echouer\n");
    else
    {
        while (fgetc(file) && (counter != (31 << 2)))
            counter++;

        if (counter != 0)
            return 0;
        else
        {
            return -1;
        }
    }
}

/*! @brief                    Fonction récupérant une ligne de texte à partir d'un flux
*   @param   stream           Flux ou récupérer la ligne de texte
*   @param   pLine            Ligne à récupérer
*   @return                   Adresse de la chaîne récupéré
*/
char* fgetl(FILE *stream, char *pLine)
{
    unsigned int length = 100;
    size_t i = 0;
    pLine = malloc(sizeof(*pLine) * length);
    if (pLine == NULL)
        return NULL;

    do {
        if (i >= length)
        {
            length = length * 2;
            pLine = realloc(pLine, length * sizeof(*pLine));
        }

        pLine[i] = fgetc(stream);
    } while (pLine[i++] != '\n');
    pLine[--i] = '\0';

    return pLine;
}

/*! @brief                    Fonction récupérant une ligne de texte à partir d'un fichier
*   @param   line             Ligne à récupérer
*   @param   max              Taille du buffer à récupérer
*   @return                   La longueur de la ligne
*/
long getLine (char *line, long max)
{
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}

/*! @brief                    Fonction pour se déplacer de lignes en lignes
*   @param   stream           Flux à parcourir
*   @param   lineNumber       Ligne à atteindre
*   @return                   Position du curseur dans le flux
*/
long fgotol (FILE *stream, long lineNumber)
{
    char *pLine = NULL;
    while (lineNumber != 0)
    {
        fgetl(stream, pLine);
        lineNumber--;
    }

    return ftell(stream);
}

long fgotoc (FILE *stream, long characterNumber)
{
    while (characterNumber != 0)
    {
        fgetc(stream);
        characterNumber--;
    }

    return ftell(stream);
}

// get filesize
int get_filesize(FILE *fp) {
    int offset, sz;

    if (!fp)
        return -1;

    offset = ftell(fp);
    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, offset, SEEK_SET);

    return sz;
}

