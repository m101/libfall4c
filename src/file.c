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
    FILE *file_src = fopen(src, "r");
    FILE *file_dst = fopen(dest, "w");
    int character;

    if (!file_src || !file_dst)
        return;

    while ((character = fgetc(file_src)) != EOF)
        fputc(character, file_dst);
    fclose(file_dst);
    fclose(file_src);
}

/*! @brief                    Fonction récupérant une ligne de texte à partir d'un flux
 *   @param   stream           Flux ou récupérer la ligne de texte
 *   @return                   Adresse de la chaîne récupéré
 */
char *fgetl (FILE *stream)
{
    unsigned int length = 128;
    char *line;
    size_t idx_line = 0;

    line = malloc(sizeof(*line) * length);
    if (!line)
        return NULL;

    while (line[idx_line] != '\n') {
        if (idx_line >= length) {
            length = length * 2;
            line = realloc(line, length * sizeof(*line));
        }

        line[idx_line] = fgetc(stream);
        idx_line++;
    }
    line[--idx_line] = '\0';

    return line;
}

/*! @brief                    Fonction pour se déplacer de lignes en lignes
 *   @param   stream           Flux à parcourir
 *   @param   lineNumber       Ligne à atteindre
 *   @return                   Position du curseur dans le flux
 */
long fgotol (FILE *stream, long idx_line)
{
    int c;

    fseek(stream, 0, SEEK_SET);

    while (idx_line > 0 && c != EOF) {
        c = fgetc(stream);
        if (c == '\n')
            idx_line--;
    }

    return ftell(stream);
}

long fgotoc (FILE *stream, long offset)
{
    fseek(stream, offset, SEEK_SET);

    return ftell(stream);
}

// get filesize
int file_get_size (FILE *fp)
{
    int offset, sz;

    if (!fp)
        return -1;

    offset = ftell(fp);
    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, offset, SEEK_SET);

    return sz;
}

int file_count_line (char *filename)
{
    unsigned long count_line;
    int c;
    FILE *fp;

    fp = fopen(filename, "r");
    if (!fp)
        return -1;

    count_line = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n')
            count_line++;
    }

    fclose(fp);

    return count_line;
}

