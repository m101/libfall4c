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
