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

#ifndef FILE_H

#define FILE_H

// Fonction copiant un fichier en mode texte
void file_copy (char *dest, char *src);
// Fonction pour se déplacer de caractères en caractères
long fgotoc (FILE *stream, long characterNumber);
// Fonction pour se déplacer de lignes en lignes
long fgotol (FILE *stream, long lineNumber);
// Fonction récupérant une ligne de texte à partir d'un flux
char* fgetl(FILE *stream, char *pLine);
// Fonction récupérant une ligne de texte à partir d'un fichier
long getLine (char *line, long max);
// Vérifie si le fichier est vide ou non
long check_file_emptiness (char *fileName);

#endif
