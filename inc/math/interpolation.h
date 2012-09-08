/***************************************************************************
 *            interpolation.h
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

#ifndef _INTERPOLATION_H
#define _INTERPOLATION_H

#define MAX_NUMBER_OF_DOT 100

#define PAS 0.01

#define X_AXIS  0
#define Y_AXIS  1

#define INTERPOLATION_LINEAR    0
#define INTERPOLATION_BEZIER    1
#define INTERPOLATION_LAGRANGE  2

//#include <glib.h>

#include "math_matrix.h"
#include "vector_space.h"

//G_BEGIN_DECLS

/*! @brief  Linear Interpolation */
double interpolation_linear (struct t_dot dot1, struct t_dot dot2, const double x);
/*! @brief  Cubic Interpolation */
double interpolation_cubic (struct t_dot dot1, struct t_dot dot2, double x);
/*! @brief  Lagrange polynoms */
struct Matrix* polynoms_lagrange (struct Matrix* vectors, const double x);
/*! @brief  Lagrange interpolation */
double interpolation_lagrange (struct Matrix* vectors, const double x);
/*! @brief  Bezier interpolation */
struct Matrix* interpolation_bezier (struct t_dot *dots, size_t size);

//G_END_DECLS

#endif /* INTERPOLATION_H */
