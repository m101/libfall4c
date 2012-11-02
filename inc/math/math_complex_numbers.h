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

#ifndef _MATHS_COMPLEX_NUMBERS_
#define _MATHS_COMPLEX_NUMBERS_

#ifdef __cplusplus
extern "C"
{
#endif

struct complex_t {
    // real part
    double real;
    // imaginary part
    double im;
};

// get a new complex number
struct complex_t* complex_new (double im, double r);

// destroy complex struct
void complex_delete (struct complex_t **cnum);

// complex number multiplication
struct complex_t* complex_multiply (struct complex_t **result,
                                    struct complex_t *complex1,
                                    struct complex_t *complex2);

// complex number addition
struct complex_t* complex_add (struct complex_t **result,
                               struct complex_t *complex1,
                               struct complex_t *complex2);

// complex number norm
double complex_norm (struct complex_t *complexNumber);

// complex number argument in radian
double complex_arg (struct complex_t *complexNumber);

#ifdef __cplusplus
}
#endif

#endif /* _MATHS_COMPLEX_NUMBERS_ */
