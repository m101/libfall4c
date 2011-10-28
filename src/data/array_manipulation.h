#ifndef ARRAY_MANIPULATION_H
#define ARRAY_MANIPULATION_H

#ifdef __cplusplus
extern "C"
{
#endif

struct array_t {
    // data
    void *data;
    // size of each data dimensions
    size_t *szData;
    // size of sizes array
    size_t size;
    // type of array
    int type;
};

void printArray (long array[], size_t i);
long numCount (long number);
long* num2array (long number, long array[], size_t *i);
long* numString2array (char *number, long *array, size_t *i);
long countDigitsInNumber (long digits);
void initialisationTableau (long tableau[]);
long sommeTableau(long tableau[], long tailleTableau);
double moyenneTableau(long tableau[], long tailleTableau);
void copie(long tableauOriginal[], long tableauCopie[], long tailleTableau);
void maximumTableau(long tableau[], long tailleTableau, long valeurMax);
void ordonnerTableau(long tableau[], long tailleTableau);

#ifdef __cplusplus
}
#endif

#endif

