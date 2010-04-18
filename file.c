#include <stdio.h>
#include <stdlib.h>

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
            realloc(pLine, length * sizeof(*pLine));
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
