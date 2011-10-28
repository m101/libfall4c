#include <stdlib.h>

#include <math.h>

#include "math_complex_numbers.h"

// get a new complex number
struct complex_t* complex_new (double im, double r) {
    struct complex_t *cnum;

    // alloc complex struct
    cnum = calloc(1, sizeof(*cnum));
    if (!cnum)
        return NULL;

    cnum->real = r;
    cnum->im = im;

    return cnum;
}

// destroy complex struct
void complex_delete (struct complex_t **cnum) {
    if (!cnum)
        return;

    if (!*cnum)
        return;

    free(*cnum);
    *cnum = NULL;
}

// complex number multiplication
struct complex_t* complex_multiply (struct complex_t **result,
                                    struct complex_t *complex1,
                                    struct complex_t *complex2)
{
    // check pointer validity
    if (!result || !complex1 || !complex2)
        return NULL;

    // check pointer validity
    if (!*result)
        *result = malloc(sizeof(**result));

    // we calculate the real part
    (*result)->real = complex1->real * complex2->real - complex1->im * complex2->im;
    // we calculate the imaginary part
    (*result)->im = complex1->im * complex2->real + complex1->real * complex2->im;

    // result = (a+bi)*(c+di) = (a*c - b*d) + (b*c + a*d)i

    return *result;
}

// complex number addition
struct complex_t* complex_add (struct complex_t **result,
                               struct complex_t *complex1,
                               struct complex_t *complex2)
{
    // check pointer validity
    if (!result || !complex1 || !complex2)
        return NULL;

    // check pointer validity
    if (!*result)
        *result = malloc(sizeof(**result));

    // we calculate the real part
    (*result)->real = complex1->real + complex2->real;
    // we calculate the imaginary part
    (*result)->im = complex1->im + complex2->im;

    // result = (a+bi)+(c+di) = (a+c) + (b+d)i

    return *result;
}

// complex number norm
double complex_norm (struct complex_t *complexNumber) {
    // check pointer validity
    if (!complexNumber)
        return -1;

    // do calculation
    return sqrt(complexNumber->real * complexNumber->real + complexNumber->im * complexNumber->im);
}

// complex number argument in radian
double complex_arg (struct complex_t *complexNumber) {
    // check pointer validity
    if (!complexNumber)
        return -1;

    // do calculation
    return atan(complexNumber->im / complexNumber->real);
}
