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
    int byte;
    size_t idx_line;

    line = calloc(length, sizeof(*line));
    if (!line)
        return NULL;

    byte = 0;
    idx_line = 0;
    while (!feof(stream)) {
        byte = fgetc(stream);

        if (byte == '\r' || byte == '\n' || byte == EOF)
            break;

        if (idx_line >= length) {
            length = length * 2;
            line = realloc(line, length * sizeof(*line));
        }

        line[idx_line] = byte;
        idx_line++;
    }

    if (feof(stream)) {
        free (line);
        return NULL;
    }

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

    if (idx_line < 0)
        return -1;

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

/*! @brief Read a line from file
 *  @param  fd       File descriptor where to read from
 *  @param  buffer   Pointer of buffer where to store data
 *  @param  bufsize  Pointer of buffer size
 *  @ret Pointer to buffer
 */
//char *file_fgetl ( char **buffer, size_t *bufsize, int fd)
char *file_fgetl ( char **buffer, size_t *bufsize, FILE *stream) {
    char *buf, *realbuf;
    int character;
    //  FILE *stream;

    // If pointer passed is invalid
    // Then we do nothing
    if (!buffer || !bufsize ) {
        fprintf(stderr, "fgetl: Failed fetching data\n");
        return NULL;
    }

    // If pointer is valid but no buffer allocated
    // Then we allocate it correctly
    if ( !*buffer || !*bufsize ) {
        *bufsize = 1024;
        *buffer = calloc( *bufsize, sizeof(char) );
    }

    // We open a stream corresponding to the file descriptor passed
    // stream = fdopen(fd, "r");
    if (!stream) {
        fprintf(stderr, "fgetl: Invalid stream\n");
        return NULL;
    }

    realbuf = *buffer;
    buf = realbuf;

    // We check for data availability
    /*
       if (data_read_time_out (fd, 2, 0) == -1)
       {
       fprintf(stderr, "file_fgetl: Read timeout\n");
       return NULL;
       }
       */

    // We read data until we reach a linefeed or the end of file
    while ( (character = fgetc(stream)) != '\n' && character != EOF ) {     
        if (  (size_t) (buf - realbuf) >= *bufsize ) {
            *bufsize *= 2;
            realbuf = realloc (realbuf, *bufsize);
            buf = realbuf + (buf - (char *)*buffer);
            *buffer = realbuf;
        }
        *buf = character;
        buf++;
        printf("file_fgetl: c : %d | %x\n", character, character);
    }
    printf("file_fgetl: c : %d | %x\n", character, character);
    *buf = '\0';

    if (strlen(realbuf) == 0)
        return NULL;

    return *buffer;
}



