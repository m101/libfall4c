/***************************************************************************
 *            interpolation.c
 *
 *  Fri Dec 19 21:40:11 2008
 *  Copyright  2008  kurapix
 *  <kurapix@<host>>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

//#include <octave/oct.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <math.h>

#include "interpolation.h"
#include "math_matrix.h"
#include "vector_space.h"

/*! @brief  Linear Interpolation
    @param  dot1    Dot to start drawing from
    @param  dot1    Dot to finish drawing to
    @param  x       X for which we want our value
    @return Calculated value
*/
double interpolation_linear (struct t_dot dot1, struct t_dot dot2, double x)
{
    // y = a*x + b
    double y = (dot2.y - dot1.y)/(dot2.x - dot1.x)*(x - dot1.x) + dot1.y;
    return y;
}

/*! @brief  Cubic Interpolation
    @param  dot1    Dot to start drawing from
    @param  dot1    Dot to finish drawing to
    @param  x       X for which we want our value
    @return Calculated value
*/
double interpolation_cubic (struct t_dot dot1, struct t_dot dot2, double x)
{
    double valueInterpolated = 0;

    return valueInterpolated;
}

/*! @brief  Spline Interpolation
    @param  dot1    Dot to start drawing from
    @param  dot1    Dot to finish drawing to
    @param  x       X for which we want our value
    @return Calculated value
*/
double interpolation_spline (void)
{
    double valueInterpolated = 0;

    return valueInterpolated;
}

/*! @brief  Lagrange polynoms
*   @param  vectors     Matrix of dots
*   @param     x        Absciss
*   @return Computed values
*/
struct Matrix* polynoms_lagrange (struct Matrix* vectors, const double x)
{
    struct Matrix *p;
    size_t i, j;

    if (!vectors)
    {
        fprintf(stderr, "interpolation_lagrange: Vectors NULL\n");
        return NULL;
    }

    p = matrix_create(1, vectors->nc);

    printf("== debut polynomes lagrange ==\n");

    for (i=0; i < p->nc; i++)
    {
        p->data[0][i] = 1.0;
        for (j = 0; j < vectors->nc; j++)
        {
            if (i != j)
                p->data[0][i] *= ( (x-vectors->data[X_AXIS][j])
                                   / (vectors->data[X_AXIS][i]-vectors->data[X_AXIS][j]) );

            printf("    x-vectors->data[X_AXIS][%u] : %lf\n", i, x-vectors->data[X_AXIS][i]);
            printf("    x-vectors->data[X_AXIS][%u] : %lf\n", j, x-vectors->data[X_AXIS][j]);
        }
        printf("    p->data[0][%u] : %lf\n\n", i, p->data[0][i]);
    }

    printf("== fin polynomes lagrange ==\n\n");

    return p;
}

/*! @brief  Lagrange interpolation
*   @param      vectors     Matrix of vectors
*   @param         x        Absciss
*   @return Computed value
*/
double interpolation_lagrange (struct Matrix* vectors, const double x)
{
    double interp = 0.0;
    size_t i;
    struct Matrix* LagrangePolynoms;

    LagrangePolynoms = polynoms_lagrange (vectors, x);

    if (!LagrangePolynoms)
    {
        fprintf(stderr, "interpolation_lagrange: LagrangePolynoms NULL\n");
        return 0;
    }

    printf("== debut interpolation lagrange ==\n");

    // Interpolation polynom
    for (i = 0; i < LagrangePolynoms->nc; i++)
    {
        // Interpolation polynom
        interp += LagrangePolynoms->data[0][i] * vectors->data[Y_AXIS][i];
        printf("    interp[%u] = %lf\n", i, interp);
        printf("    vectors->data[Y_AXIS][%u] : %lf\n", i, vectors->data[Y_AXIS][i]);
        printf("    LagrangePolynoms->data[0][%u] : %lf\n", i, LagrangePolynoms->data[0][i]);
        printf("    LagrangePolynoms->data[0][%u] * vectors->data[Y_AXIS][%u] : %lf\n", i, i, LagrangePolynoms->data[0][i] * vectors->data[Y_AXIS][i]);
    }

    printf("    interp : %lf\n", interp);

    printf("== fin interpolation lagrange ==\n\n");

    matrix_destroy (&LagrangePolynoms);

    return interp;
}

/*! @brief  Bezier interpolation
*   @param      dots    Matrix of dots
*   @param        x     Size of matrix
*   @return Computed values
*/
struct Matrix* interpolation_bezier (struct t_dot *dots, size_t size)
{
    size_t l;
    double t;
    struct Matrix *interpolatedValues;

    interpolatedValues = matrix_create (2, size);

    for (t = 0, l = 0; l < size; t += PAS, l++)
    {
        // Bezier cubic
        interpolatedValues->data[X_AXIS][l] = dots[0].x * pow((1-t),3)
                                              + 3 * dots[1].x * t * pow(1-t,2)
                                              + 3 * dots[2].x * pow(t, 2) * (1-t)
                                              + dots[3].x * pow(t,3);
        interpolatedValues->data[Y_AXIS][l] = dots[0].y * pow((1-t),3)
                                              + 3 * dots[1].y * t * pow(1-t, 2)
                                              + 3 * dots[2].y * pow(t,2 ) * (1-t)
                                              + dots[3].y * pow(t,3);
    }

    return interpolatedValues;
}
