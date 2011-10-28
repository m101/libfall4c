#ifndef _MATHS_COMPLEX_NUMBERS_
#define _MATHS_COMPLEX_NUMBERS_

#ifdef __cplusplus
extern "C"
{
#endif

struct t_complex {
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
struct t_complex* complex_multiply (struct t_complex **result,
                                    struct t_complex *complex1,
                                    struct t_complex *complex2);

// complex number addition
struct t_complex* complex_add (struct t_complex **result,
                               struct t_complex *complex1,
                               struct t_complex *complex2);

// complex number norm
double complex_norm (struct t_complex *complexNumber);

// complex number argument in radian
double complex_arg (struct t_complex *complexNumber);

#ifdef __cplusplus
}
#endif

#endif /* _MATHS_COMPLEX_NUMBERS_ */
