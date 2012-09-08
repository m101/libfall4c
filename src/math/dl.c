#include <stdlib.h>

#include <math.h>

#include "math/math_probability.h"

double dl_exponential (double x, long ordre) {
    size_t i = 0;
    double value = 0;

    // exp(x) = sum(x^i/i!, 0, n)
    // i in [0 ... n]
    for (i = 0; i <= ordre;  i++)
        value += pow(x, i) / (double) factorielle(i, 1);

    return value;
}

double dl_cosinus (double x, long ordre) {
    size_t i = 0;
    double value = 0;
    short int coef = 1;

    // cos(x) = 1 - x^2/2 + x^4/4 + x^6/6 + ... + (-1)^n *(x^2n)/(2n!) + O(x^(n+1))
    for (i = 1; i <= ordre;  i++) {
        coef *= -1;
        value += coef * (pow(x, 2*i) / (double) factorielle(2*i, 1));
    }

    value += 1;

    return value;
}
