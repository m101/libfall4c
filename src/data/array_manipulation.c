#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "arrayManipulation.h"

void printArray (long array[], size_t i)
{
    size_t j = 0;

    for (j = 0; j < i; j++)
    {
        printf("%ld\n", array[j]);
    }
}

long* num2array (long number, long *array, size_t *i)
{
    long i_temp = 0, j = 0, temp1 = 0;
    double temp2 = number;
    *i = numCount(number);
    i_temp = *i;
    printf("i_temp initial : %ld et *i : %d\n\n", i_temp, *i);
    array = malloc(sizeof(*array) * i_temp);
    if (array == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < *i; j++)
    {
        temp2 = temp2 / pow(10, i_temp - 1);
        printf("temp 2 div : %lf\n", temp2);
        temp1 = (long)temp2;
        printf("temp 1 : %ld\n", temp1);
        *(array+j) = temp1;
        printf("array : %ld, j : %ld", array[j], j);
        temp2 = (temp2 - (long)temp2) * pow(10, i_temp - 1);
        printf("temp 2 arith : %lf\n", temp2);
        printf("i_temp : %ld\n", i_temp);
        i_temp -= 1;
        printf("i_temp : %ld\n\n", i_temp);
    }

    return array;
}

long* numString2array (char *number, long *array, size_t *i)
{
    long numberLength = strlen(number);
    *i = numberLength;
    long *longArray = malloc (sizeof(*longArray) * numberLength + 1);
    long *pArray = longArray;
    //long j = numberLength - 1;

    while (*number != '\0')
    {
        //*(longArray + j) = *number - '0';
        *longArray = *number - '0';
        longArray++;
        number++;
        //j--;
    }

    return pArray;
}

long numCount (long number)
{
    long count = 0;

    do
    {
        number /= 10;
        count++;
    }
    while (number > 0);

    return count;
}

long countDigitsInNumber (long digits)
{
    long i = 0;

    do
    {
        digits /= 10;
        i++;
    } while (digits > 0);

    return i;
}

void ArrayInit (long tableau[])
{
    while (*tableau)
    {
        *tableau = 0;
        tableau++;
    }
}

//Somme de toutes les valeurs d'un tableau
long sommeTableau(long tableau[], long tailleTableau)
{
    long somme = 0, i;

    for (i = 0; i < tailleTableau; i++)
    {
        somme += tableau[i];
    }

    return somme;
}

//Moyenne de la somme des valeurs contenues dans un tableau.
double moyenneTableau(long tableau[], long tailleTableau)
{
    double moyenne = 0, somme;

    somme = sommeTableau(tableau[], tailleTableau);
    moyenne = somme/tailleTableau;

    return moyenne;
}

void copie(long tableauOriginal[], long tableauCopie[], long tailleTableau)
{
    int i;

    //Fait une copie conforme tu tableau original
    for (i=0; i < tailleTableau; i++)
    {
        tableauCopie[i] = tableauOriginal[i];
    }
}

void maximumTableau(long tableau[], long tailleTableau, long valeurMax)
{
    int i;

    for (i = 0; i < tailleTableau; i++)
    {
        //Si la valeur d'un element du tableau est superieur a valeur max alors
        //celui-ci est re-initialiser a 0
        if (tableau[i] > valeurMax)
        {
            tableau[i] = 0;
        }
    }
}

void ordonnerTableau(long tableau[], long tailleTableau)
{
    long temp = 0;
    int i, j;

    for (i = 0; i < (tailleTableau-1); i++)
    {
        for (j=i++; j < tailleTableau; j++)
        {
            if (tableau[i] > tableau[j])
            {
                temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
        }
    }
}
