#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "data/array_manipulation.h"

int num_count (int num)
{
    return 0;
}

long *num2array (long number, long *array, size_t *i)
{
    long i_temp = 0, j = 0, temp1 = 0;
    double temp2 = number;

    *i = num_count(number);
    i_temp = *i;
    printf("i_temp initial : %ld et *i : %d\n\n", i_temp, *i);

    array = malloc(sizeof(*array) * i_temp);
    if (!array)
        exit(EXIT_FAILURE);

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

// generic bubble sort
void sort_bubble (void *array, size_t nmemb, size_t size, int(*compar)(const void *, const void *))
{
    void *temp = NULL;
    int i, j;
    int check;

    // alloc temp
    temp = calloc(1, size);
    if (!temp)
        return;

    for (i = 0; i < (nmemb-1); i++) {
        for (j=i++; j < nmemb; j++) {
            check = compar(array+i, array+j);
            if (check > 0) {
                memcpy(temp, array+i, size);
                memcpy(array+i, array+j, size);
                memcpy(array+j, temp, size);
            }
        }
    }

    free(temp);
}

