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
long check_file_emptiness (char *fileName);#endif

#endif
