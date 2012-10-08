#ifndef ARRAY_MANIPULATION_H
#define ARRAY_MANIPULATION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

long *num2array (long number, long *array, size_t *i);
// generic bubble sort
void sort_bubble (void *array, size_t nmemb, size_t size, int(*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif

