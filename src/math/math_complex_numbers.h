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
