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

#ifndef _MATHS_MATRICES_H
#define _MATHS_MATRICES_H

//#include <glib.h>

//G_BEGIN_DECLS

#define X_AXIS 0
#define Y_AXIS 1

#include "vector_space.h"

#define ERROR_MATRIX_NOTSQUARE  -1
#define ERROR_MATRIX_NOT_FILLED -2

/*! @brief Matrix object : Contain matrix data
 */
typedef struct Matrix
{
	/*! bi-dimensionnal doubles array */
	double **data;
	/*! number of rows */
	size_t nr;
	/*! number of columns */
	size_t nc;
} Matrix;

/*! @brief Matrix max object
 */
typedef struct Matrix_max
{
	/*! Vector where there are the max values of each columns of a matrix */
	struct Matrix *matrix;
	/*! Index of the first maximum value in the vector */
	size_t index;
} Matrix_max;

// Destroy Matrix_max variable instance
void matrix_max_destroy(struct Matrix_max **matrix_max);
// Create a matrix
struct Matrix* matrix_create (size_t nr, size_t nc);
// Destroy a matrix
void matrix_destroy (struct Matrix **matrix);
// Create a copy of a matrix
struct Matrix* matrix_copy (struct Matrix *matrix);
// Row reduction echelon form
struct Matrix* matrix_rref (struct Matrix *matrix);
// Inverse matrix
struct Matrix* matrix_inverse (struct Matrix *matrix);
// Matrix augmentation
struct Matrix* matrix_augment (struct Matrix *A, struct Matrix *B);
// Gauss elimination
struct Matrix* matrix_rref_gauss (struct Matrix *matrix);
// Find max values of each column
struct Matrix_max* matrix_max (struct Matrix *matrix);
// Return infinite norm of a matrix
double matrix_norm_inf (struct Matrix *matrix);
// Determinant with Sarrus
// struct SRet matrix_det_sarrus (struct Matrix *matrix);
int matrix_det_sarrus (struct Matrix *matrix);
// Matrix filling row
int matrix_fill_row (struct Matrix *matrix, size_t rowNb, char *row);
// Matrix fill
int matrix_fill (struct Matrix *matrix, char *data);
// Matrix show
int matrix_show (struct Matrix *matrix);
// Matrice reduction
struct Matrix* matrix_reduction (struct Matrix *matrix);
// Return identity matrix
struct Matrix *matrix_identity (size_t nr, size_t nc);
// Matrix addition
struct Matrix *matrix_addition (struct Matrix *A, struct Matrix *B);
// Matrix multiplication with a scalar
struct Matrix *matrix_multiplication_scalar (struct Matrix *matrix,
												double scalar);
// Matrix multiplication
struct Matrix *matrix_multiplication (struct Matrix *A, struct Matrix *B);
// Transpose a matrix
struct Matrix *matrix_transpose (struct Matrix *matrix);
// Swap 2 rows
int matrix_row_swap (struct Matrix *matrix, size_t row1, size_t row2);

// Comatrix
struct Matrix *matrix_com (struct Matrix *matrix, size_t row);

/*! Sort vector of dots */
struct Matrix *matrix_sort_vector2d (struct Matrix *matrix);

/*! Convert an array of dots to a matrix */
struct Matrix *dotArray_to_vector2d (struct t_dot *dots, size_t size);

//G_END_DECLS

#endif /* MATHS_MATRICES_H */
