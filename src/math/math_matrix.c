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

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <math.h>

//#include "interpolation.h"
#include "util/errors.h"
#include "math/math_matrix.h"
#include "math/vector_space.h"

#define matrix_rref_gauss_java(var) matrix_rref_gauss(var)

#ifdef WIN32
    #include "strtok_r.h"
#endif

/*! @brief				Function which destroy an object of type matrix_max
	@param matrix_maxi  matrix_max to destroy
 */
void matrix_max_destroy(struct Matrix_max **matrix_maxi)
{
    // Temporary pointer to ease reading
    struct Matrix_max *m_matrix_max = NULL;

    // We check if pointers are valid
    if (!matrix_maxi)
        return;
    if (!*matrix_maxi)
        return;

    // Ease reading
    m_matrix_max = *matrix_maxi;

    // Destroy vector
    matrix_destroy(&(m_matrix_max->matrix));
    // Destroy allocated instance of matrix_max
    free(m_matrix_max);
    // NULL it
    *matrix_maxi = NULL;
}

/*! @brief		Create a matrix object
	@param nr   Number of rows
	@param nc   Number of columns
	@return		Created matrix
 */
struct Matrix* matrix_create (size_t nr, size_t nc)
{
    struct Matrix *m_matrix = NULL;
    size_t i = 0;

    // Allocate
    m_matrix = malloc(sizeof(*m_matrix));

    if (!m_matrix)
        return NULL;

    // Set the number of rows and columns to values passed
    m_matrix->nr = nr;
    m_matrix->nc = nc;

    // Allocation of a bi-dimensionnal doubles array
    m_matrix->data = malloc(sizeof(*m_matrix->data) * nr);
    for (i = 0; i < nr; i++)
    {
        // Allocate and initialize to 0
        m_matrix->data[i] = calloc(nc, sizeof(*m_matrix->data[i]));
        // If matrix is square, we have an identity matrix by default
        if (nr == nc)
            m_matrix->data[i][i] = 1;
    }

    return m_matrix;
}

/*! @brief			Destroy a matrix object
	@param matrix   Matrix to destroy
 */
void matrix_destroy (struct Matrix **matrix)
{
    size_t i = 0;

    // Check pointers
    if (!matrix)
        return;
    if (!*matrix)
        return;

    // Free all rows and cols
    for (i = 0; i < (*matrix)->nr; i++)
        free((*matrix)->data[i]);
    // Free structure
    free(*matrix);
    // NULL it
    *matrix = NULL;
}

double matrix_get_elt (struct Matrix *matrix, int x, int y) {
    //
    if (!matrix || !(matrix->data))
        return -1;

    return matrix->data[x][y];
}

int matrix_get_nrow (struct Matrix *matrix) {
    if (!matrix)
        return -1;
    return matrix->nr;
}

int matrix_get_ncol (struct Matrix *matrix) {
    if (!matrix)
        return -1;
    return matrix->nc;
}

/*! @brief			Copy a matrix
	@param  matrix  Matrix to copy
	@return			A copy of matrix
 */
struct Matrix* matrix_copy (struct Matrix *matrix)
{
    size_t i = 0;
    struct Matrix *m_mcpy = NULL;

    // Check pointer
    if (!matrix)
    {
        printf("matrix_copy: matrix is null\n");
        return NULL;
    }

    // Allocate a matrix object
    m_mcpy = matrix_create(matrix->nr, matrix->nc);

    // Copy rows by rows
    for (i = 0; i < matrix->nr; i++)
        memcpy(m_mcpy->data[i], matrix->data[i],
               sizeof(*matrix->data[i]) * matrix->nc);

    return m_mcpy;
}

/*! @brief			Invert a matrix
	@param matrix   Matrix for which we want the inverse
	@return			Inverted Matrix
 */
struct Matrix* matrix_inverse (struct Matrix *matrix)
{
    // Index to browse augmented matrix rref
    size_t i = 0, j = 0;
    // Index to browse inverted matrix
    size_t k = 0;
    // struct SRet Ret = {0};
    // Matrix identity to append
    struct Matrix *m_identity = NULL;
    // augmented matrix
    struct Matrix *m_augmented = NULL;
    // rref of the augmented matrix
    struct Matrix *m_rref = NULL;
    // Inverted matrix
    struct Matrix *m_inverse = NULL;
    // determinant
    int det;

    // Ret = matrix_det_sarrus(matrix);
    det = matrix_det_sarrus(matrix);

    if (!matrix)
    {
        // // Ret.ret = ERROR_NULL_POINTER;
        printf("matrix_inverse: Matrix not allocated\n");
        return NULL;
    }

    if (matrix->nr != matrix->nc)
    {
        // Ret.ret = ERROR_MATRIX_NOTSQUARE;
        printf("matrix_inverse: Matrix not square\n");
        return NULL;
    }

    // if (!Ret.ret)
    if (!det)
    {
        printf("matrix_inverse: Matrix not inversible\n");
        return NULL;
    }

    // We create the working matrix
    m_identity = matrix_identity(matrix->nr, matrix->nc);
    m_augmented = matrix_augment(matrix, m_identity);
    m_rref = matrix_rref_gauss (m_augmented);
    // We allocate inverted matrix
    m_inverse = matrix_create(matrix->nr, matrix->nc);

    // We extract the inverted matrix
    for (i = 0; i < matrix->nr; i++)
    {
        for (j = matrix->nc; j < 2*matrix->nc; j++)
        {
            m_inverse->data[i][k] = m_rref->data[i][j];
            k++;
        }
        k = 0;
    }

    // We free all useless used memory
    matrix_destroy(&m_identity);
    matrix_destroy(&m_augmented);
    matrix_destroy(&m_rref);

    return m_inverse;
}

/*! @brief			Compute the augmented matrix of A and B : (A|B)
	@param A		First Matrix : Matrix to augment
	@param B		Second Matrix : Matrix to append
	@return			The augmented matrix of the form (A|B)
 */
struct Matrix* matrix_augment (struct Matrix *A, struct Matrix *B)
{
    // Index for A and m_augmented
    size_t i = 0, j = 0;
    // Index for B
    size_t k = 0;
    // Augmented matrix
    struct Matrix *m_augmented = NULL;

    // Check for valid matrix
    if (!A)
    {
        fprintf(stderr, "matrix_augment: Matrix A is null\n");
        return NULL;
    }

    if (!B)
    {
        fprintf(stderr, "matrix_augment: Matrix A is null\n");
        return NULL;
    }

    // The two matrix has to have the same number of rows
    if (A->nr != B->nr)
    {
        fprintf(stderr, "matrix_augment: Matrix A and B"
                "don't have the same number of rows\n");
        return NULL;
    }

    // Allocate the matrix
    m_augmented = matrix_create(A->nr, A->nc + B->nc);

    // Construct the augmented matrix
    for (i = 0; i < m_augmented->nr; i++)
    {
        for (j = 0; j < A->nc; j++)
            m_augmented->data[i][j] = A->data[i][j];
        for (j = A->nc; j < m_augmented->nc; j++)
        {
            m_augmented->data[i][j] = B->data[i][k];
            k++;
        }
        k = 0;
    }

    return m_augmented;
}

/*! @brief			Function which compute
					the reduce row echelon form of a matrix.
					This function works correctly
					(it will solve the linear equation only if
					 there are solutions)
	@param matrix   Matrix for which to compute the rref
	@return			The reduce row echelon form of the matrix

 */
struct Matrix* matrix_rref_gauss_java (struct Matrix *matrix)
{
    int x = 0, y = 0, t = 0;
    struct Matrix *m_rref = NULL;

    if (!matrix)
    {
        fprintf(stderr, "matrix_rref_gauss: matrix is null\n");
        return NULL;
    }

    m_rref = matrix_copy(matrix);

    // Pour chaque ligne de la matrice T
    for (x = 0; x < m_rref->nr; x++)
    {
        // Cherche la ligne avec le pivot max (en valeur fabsolue)
        int bestline = x;
        double pivot = m_rref->data[bestline][x];
        for (y = x + 1; y < m_rref->nr; y++)
        {
            if (fabs(m_rref->data[y][x]) > fabs(pivot))
            {
                bestline = y;
                pivot = m_rref->data[bestline][x];
            }
        }
        //*
        if (pivot == 0)
        {
            fprintf(stderr, "matrix_rref_gauss: Pivot is null,"
                    "impossible to rref\n");
            //return NULL;
            return NULL;
        }
        //*/

        // Echange des lignes (si necessaire)
        if (bestline != x)
        {
            double *m_swap = NULL;

            m_swap = m_rref->data[x];
            m_rref->data[x] = m_rref->data[bestline];
            m_rref->data[bestline] = m_swap;

            /*
            double tmp;
            for (t = 0; t < matrix->nc; t++)
            {
            	tmp = matrix->data[x][t];
            	matrix->data[x][t] = matrix->data[bestline][t];
            	matrix->data[bestline][t] = tmp;
            }
             */
        }

        // Normalisation de la ligne du pivot
        for (t = 0; t < m_rref->nc; t++)
            m_rref->data[x][t] /= pivot;

        // elimination des autres lignes
        for (y = 0; y < m_rref->nr; y++)
        {
            if (y==x)
                continue;
            double coef = m_rref->data[y][x];
            for (t = 0; t < matrix->nc; t++)
                m_rref->data[y][t] -= coef * m_rref->data[x][t];
        }
    }

    return m_rref;
}

/*
 ToReducedRowEchelonForm(Matrix M)
  Let lead = 0
  Let rowCount be the number of rows in M
  Let columnCount be the number of columns in M
  FOR r = 0 to rowCount - 1
    IF columnCount <= lead
      STOP
    END IF
    Let i = r
    WHILE M[i, lead] = 0
      Increment i
      IF rowCount = i
        Let i = r
        Increment lead
        IF columnCount = lead
          STOP
        END IF
      END IF
    END WHILE
    Swap rows i and r
    Divide row r by M[r, lead]
    FOR i = 0 to rowCount - 1
      IF i ≠ r
        Subtract M[i, lead] multiplied by row r from row i
      END IF
    END FOR
    Increment lead
  END FOR
END ToReducedRowEchelonForm
 */
/*! @brief  Reduce Row Echelon Form
 */
struct Matrix* matrix_rref (struct Matrix* matrix)
{
    struct Matrix *m_rref = NULL;
    double *m_wrow = NULL;
    size_t lead = 0;
    size_t rowCount, colCount;
    size_t r = 0, i = 0;

    if (!matrix)
        return NULL;

    m_rref = matrix_copy(matrix);

    //
    rowCount = matrix->nr;
    colCount = matrix->nc;
    for (r = 0; r < rowCount; r++)
    {
        if (colCount <= lead)
            break;

        i = r;

        while (m_rref->data[i][lead] == 0)
        {
            i++;
            if (rowCount == i)
            {
                i = r;
                lead++;
                if (colCount == lead)
                    break;
            }
        }
        // Swap row i and r
        m_wrow = m_rref->data[i];
        m_rref->data[i] = m_rref->data[r];
        m_rref->data[r] = m_wrow;

        for (i = 0; i < rowCount; i++)
        {
            if (i != r)
                m_rref->data[i][lead] -= m_rref->data[r][lead] * m_rref->data[i][lead];
            //Subtract M[i, lead] multiplied by row r from row i
        }
        lead++;
    }

    return m_rref;
}

/*! @brief		Function for rref to convert for our code
				Not usable with our code
 */
int LinearEquationsSolving (int nDim,
                            double* pfMatr, double* pfVect,
                            double* pfSolution)
{
    double fMaxElem;
    double fAcc;

    int i = 0, j = 0, k = 0, m = 0;

    for (k=0; k<(nDim-1); k++) // base row of matrix
    {
        // search of line with max element
        //fMaxElem = fabs( pfMatr[k*nDim + k] );
        m = k;
        for (i=k+1; i<nDim; i++)
        {
//			if(fMaxElem < fabs(pfMatr[i*nDim + k]) )
            {
                fMaxElem = pfMatr[i*nDim + k];
                m = i;
            }
        }

        // permutation of base line (index k) and max element line(index m)
        if (m != k)
        {
            for (i=k; i<nDim; i++)
            {
                fAcc               = pfMatr[k*nDim + i];
                pfMatr[k*nDim + i] = pfMatr[m*nDim + i];
                pfMatr[m*nDim + i] = fAcc;
            }
            fAcc = pfVect[k];
            pfVect[k] = pfVect[m];
            pfVect[m] = fAcc;
        }

        if ( pfMatr[k*nDim + k] == 0.)
            return 1; // needs improvement !!!

        // triangulation of matrix with coefficients
        for (j=(k+1); j<nDim; j++) // current row of matrix
        {
            fAcc = - pfMatr[j*nDim + k] / pfMatr[k*nDim + k];
            for (i=k; i<nDim; i++)
            {
                pfMatr[j*nDim + i] = pfMatr[j*nDim + i]
                                     + fAcc*pfMatr[k*nDim + i];
            }
            pfVect[j] = pfVect[j] + fAcc*pfVect[k]; // free member recalculation
        }
    }

    for (k=(nDim-1); k>=0; k--)
    {
        pfSolution[k] = pfVect[k];
        for (i=(k+1); i<nDim; i++)
        {
            pfSolution[k] -= (pfMatr[k*nDim + i]*pfSolution[i]);
        }
        pfSolution[k] = pfSolution[k] / pfMatr[k*nDim + k];
    }

    return 0;
}

/*! @brief			Function which compute
					the reduce row echelon form of a matrix.
					This function doesn't work as expected.
	@param matrix   Matrix for which to compute the rref
	@return			The reduce row echelon form of the matrix
 */
struct Matrix* matrix_rref_gauss_wikipedia (struct Matrix *matrix)
{
    size_t i = 0, j = 0, k = 0, e = 0, u = 0, maxi = 0;
    struct Matrix *m_rref = NULL;

    if (!matrix)
    {
        printf("matrix_rref_gauss: Matrix not allocated\n");
        return NULL;
    }

    m_rref = matrix_copy(matrix);

    while ( (i < m_rref->nr) && (j < m_rref->nc) )
    {
        maxi = i;
        for (k = i+1; k < m_rref->nr; k++)
        {
            if ( fabs(m_rref->data[k][j]) > fabs(m_rref->data[maxi][j]) )
            {
                maxi = k;
            }
        }
        if ( m_rref->data[maxi][j] != 0 )
        {
            // swap rows i and maxi, but do not change the value of i
            matrix_row_swap (m_rref, i, maxi);
            for ( e = 0; e < m_rref->nc; e++)
                m_rref->data[i][e] = m_rref->data[i][e]/m_rref->data[i][j];
            for ( u = i+1; u < m_rref->nr; u++)
                m_rref->data[u][j] -= m_rref->data[i][j] * m_rref->data[u][j];
            i = i + 1;
        }
        j = j + 1;
    }

    return m_rref;
}

/*! @brief			Function which compute
					the reduce row echelon form of a matrix.
					This function doesn't work as expected
					and isn't complete.
	@param matrix   Matrix for which to compute the rref
	@return			The reduce row echelon form of the matrix
 */
void matrix_rref_gauss_octave (struct Matrix *matrix)
{
    size_t m_row = 0, m_col = 0, k = 0, e = 0, u = 0, maxi = 0, m = 0;
    size_t i = 0, j = 0;
    double eps = 2.2e-16, tolerance = 0;
    // Matrix with zeros
    struct Matrix *m_used = NULL;
    struct Matrix_max *m_max = NULL;
    // Temp matrix
    double *line = NULL;

    if (!matrix)
    {
        printf("matrix_rref_gauss: Matrix not allocated\n");
        return;
    }

    // max (rows, cols)
    // we compare rows and cols
    if (matrix->nr > matrix->nc)
        maxi = matrix->nr;
    else if (matrix->nr < matrix->nc)
        maxi = matrix->nc;
    else
        maxi = matrix->nr;

    tolerance = eps * maxi * matrix_norm_inf (matrix);

    // Matrix with zeros
    m_used = matrix_create(1, matrix->nc);

    for (m_col = 0; m_col < matrix->nc; m_col++)
    {
        m_max = matrix_max(matrix);
        // index du maximum
        m = m_max->index;
        // pivot
        m_max->index = m_max->index + m_row - 1;

        if (m_max->matrix->data[0][m] < tolerance)
        {
            // A (r:rows, c) = zeros (rows-r+1, 1);
            for (i = m_row; i < matrix->nr; i++)
                matrix->data[i][m_col] = 0;
        }
        else
        {
            // keep track of bound variables
            m_used->data[0][m_col] = 1;

            // Swap current row and pivot row
            line = matrix->data[i];
            matrix->data[i] = matrix->data[m_max->index];
            matrix->data[m_max->index] = line;

            // Normalize pivot row
            for (j = m_col; j < matrix->nc; j++)
                // A (r, c:cols) = A (r, c:cols) / A (r, c);
                matrix->data[m_row][j] = matrix->data[m_row][j]
                                         / matrix->data[m_row][m_col];

            // Eliminate the current column
            for (i = 0; i < m_row; i++)
            {
                for (j = m_col; j < matrix->nc; j++)
                    matrix->data[i][j] = matrix->data[i][j]
                                         - matrix->data[i][m_col]
                                         * matrix->data[m_row][j];
            }

            for (i = m_row+1; i < matrix->nr; i++)
            {
                for (j = m_col; j < matrix->nc; j++)
                    matrix->data[i][j] = matrix->data[i][j]
                                         - matrix->data[i][m_col]
                                         * matrix->data[m_row][j];
            }

            // Check if done
            if (++m_row == matrix->nr)
                break;
        }

        /*
         else

        ## Swap current row and pivot row
        A ([pivot, r], c:cols) = A ([r, pivot], c:cols);

        ## Normalize pivot row
        A (r, c:cols) = A (r, c:cols) / A (r, c);

        ## Eliminate the current column
        ridx = [1:r-1, r+1:rows];
        A (ridx, c:cols) = A (ridx, c:cols) - A (ridx, c) * A(r, c:cols);

        ## Check if done
        if (r++ == rows)
        break;
        endif
        endif
        endfor
        k = find (used);
         */
    }
}

/*! @brief  Search max values for each columns of a matrix
			and the index of the first maximum value of this vector
	@param  matrix  Matrix where to search for the maximum values of each col
	@return A matrix_max which contain the index and the vector
 */
struct Matrix_max* matrix_max (struct Matrix *matrix)
{
    size_t i = 0, j = 0;
    // Max value in column, track to compute index
    double m_maxc = -100000, t = -0x7fffffff;
    // Vector containing the max values
    struct Matrix *m_vector = NULL;
    // Struct containing data to be returned
    struct Matrix_max *m_return = NULL;

    if (!matrix)
    {
        printf("matrix_max: Matrix not allocated\n");
        return NULL;
    }

    m_vector = matrix_create(1, matrix->nc);
    m_return = malloc(sizeof(*m_return));
    m_return->matrix = m_vector;

    for (j = 0; j < matrix->nc; j++)
    {
        for (i = 0; i < matrix->nr; i++)
        {
            if (m_maxc < matrix->data[i][j])
                m_maxc = matrix->data[i][j];
        }
        // Keep track of the index of the first maximum value
        if (m_maxc > t)
        {
            // Keep track of the max value
            t = m_maxc;
            // Index of the first maximum value
            m_return->index = j;
        }

        m_vector->data[0][j] = m_maxc;
        m_maxc = -100000;
    }

    return m_return;
}

// Matrix infinite norm
/*! @brief				Compute matrix infinite norm
	@param  matrix		Matrix for which we want the infinite norm
	@return				Infinite norm of matrix
 */
double matrix_norm_inf (struct Matrix *matrix)
{
    size_t j = 0;
    // Norm
    double m_norm = 0;
    // Vector of the max values of each cols
    struct Matrix_max *m_vector = NULL;

    if (!matrix)
    {
        printf("matrix_norm_inf: Matrix not allocated\n");
        return 0;
    }

    m_vector = matrix_max(matrix);

    // Compute infinite matrix norm
    for (j = 0; j < matrix->nc; j++)
        m_norm += m_vector->matrix->data[0][j];

    matrix_max_destroy(&m_vector);

    return m_norm;
}

/*! @brief				Compute determinant for 2x2 and 3x3 matrix
	@param matrix		Matrix to compute determinant from
	@return				Structure with return code and determinant
 */
int matrix_det_sarrus (struct Matrix *matrix)
{
    size_t i = 0, j = 0, k = 0;
    double val = 1, det = 0;
    // struct SRet Ret = {0};

    if (!matrix)
    {
        // Ret.ret = ERROR_NULL_POINTER;
        // return Ret;
        return ERROR_NULL_POINTER;
    }

    // Check if matrix are square
    if (matrix->nr != matrix->nc)
    {
        // Ret.ret = ERROR_MATRIX_NOTSQUARE;
        // return Ret;
        return ERROR_MATRIX_NOTSQUARE;
    }/*
	 else if ( ((matrix->nr == 3) || (matrix->nr == 2))
			  && (matrix->nc == matrix->nr) )*/
    // Matrix 3x3
    else if ( (matrix->nr == 3)
              && (matrix->nc == matrix->nr) )
    {
        // Diagonal going down
        for (i = 0; i < matrix->nr; i++)
        {
            for (j = 0; j < matrix->nc; j++)
            {
                k = (i + j)%matrix->nr;
                val *= matrix->data[k][j];
            }
            det += val;
            val = 1;
        }

        // Diagonal going up
        for (i = 2; i < 2*matrix->nr-1; i++)
        {
            for (j = 0; j < matrix->nc; j++)
            {
                k = (i - j)%matrix->nr;
                val *= matrix->data[k][j];
            }
            det -= val;
            val = 1;
        }

        // Result
        // Ret.ret = det;
    }
    // Matrice 2x2
    else if  ( (matrix->nr == 2)
               && (matrix->nc == matrix->nr) )
    {
        // Diagonal going down
        det = matrix->data[0][0] * matrix->data[1][1];
        // Diagonal going up
        det -= (matrix->data[1][0] * matrix->data[0][1]);
        // Result
        // Ret.ret = det;
    }

    return det;
}

/*! @brief				Fill a matrix row
	@param matrix		Matrix to fill
	@param rowNb		Row number to fill
	@param row			String with values of row
	@return
 */
int matrix_fill_row (struct Matrix *matrix, size_t rowNb, char *row)
{
    // Whole matrix, a cell
    char *string = NULL, *cell = NULL;
    // Reference for strtok_r
    char *ref = NULL;
    size_t j = 0;

    // Check pointers
    if (!matrix)
        return ERROR_NULL_POINTER;
    if (!row)
        return ERROR_NULL_POINTER;

    // Check range
    if ( (rowNb < 0) || (rowNb >= matrix->nr) )
        return ERROR_OUTOFRANGE;

    // Duplicate string to avoid segfault because of static strings
    string = strdup(row);
    // Get the first cell
    cell = strtok_r(string, " ", &ref);

    // Fill matrix while there is cell and not overflowing j
    while ( cell && (j < matrix->nc) )
    {
        matrix->data[rowNb][j] = atof(cell);
        cell = strtok_r(NULL, " ", &ref);
        j++;
    }

    free(string);

    if (j != matrix->nc)
    {
        fprintf(stderr, "matrix_fill_row: Matrix wasn't filled correctly\n");
        return ERROR_MATRIX_NOT_FILLED;
    }

    return 0;
}

/*! @brief				Fill a matrix
	@param matrix		Matrix to fill
	@param data			String with values of each rows separated with ';'
	@return
 */
int matrix_fill (struct Matrix *matrix, char *data)
{
    size_t i = 0, j = 0;
    // Whole matrix
    char *string = NULL;
    // matrix row, matrix cell
    char *strRow = NULL, *strCell = NULL;
    // First reference for row and second reference for cell (using strktok_r)
    char *refRow = NULL, *refCell = NULL;

    // Check pointers
    if (!matrix)
        return ERROR_NULL_POINTER;

    if (!data)
        return ERROR_NULL_POINTER;

    // Duplicate string to avoid segfault because of static strings
    string = strdup(data);

    // Get first row
    strRow = strtok_r(string, ";", &refRow);

    // Fill matrix
    while (strRow && (i < matrix->nr))
    {
        strCell = strtok_r(strRow, " ", &refCell);
        while (strCell && (j < matrix->nc))
        {
            matrix->data[i][j] = atof(strCell);
            strCell = strtok_r(NULL, " ", &refCell);
            j++;
        }
        strRow = strtok_r(NULL, ";", &refRow);
        i++;
        j = 0;
    }

    return 0;
}

/*! @brief				Show matrix content
	@param  matrix		Matrix to show
	@return				ret code
 */
int matrix_show (struct Matrix *matrix)
{
    size_t i = 0, j = 0;

    // Check pointers
    if (!matrix)
        return ERROR_NULL_POINTER;

    // Print matrix m*n
    for (i = 0; i < matrix->nr; i++)
    {
        for (j = 0; j < matrix->nc; j++)
        {
            printf("%lf\t", matrix->data[i][j]);
        }
        putchar('\n');
    }

    return 0;
}

/*! @brief			Matrix reduction
	@param  matrix  Matrix to reduce
	@return			Reduced matrix
 */
struct Matrix* matrix_reduction (struct Matrix* matrix)
{
    struct Matrix *m_reduced = NULL;

    return m_reduced;
}

/*! @brief		Create an identity matrix of the size specified
	@param  nr  Number of rows
	@param  nc  Number of columns
	@return		Identity matrix
 */
struct Matrix *matrix_identity (size_t nr, size_t nc)
{
    size_t i = 0;
    struct Matrix *identity = NULL;

    if (!(nr == nc))
    {
        printf("matrix_identity: Identity matrix asked isn't square\n");
        return NULL;
    }

    identity = matrix_create(nr, nc);

    for (i = 0; i < nr; i++)
    {
        identity->data[i][i] = 1;
    }

    return identity;
}

/*! @brief		Add two matrix between them
	@param  A   First matrix
	@param  B   Second matrix
	@return		Added matrix
 */
struct Matrix *matrix_addition (struct Matrix *A, struct Matrix *B)
{
    struct Matrix *m_added = NULL;
    size_t i = 0, j = 0;

    // Check pointers
    if (!A)
    {
        printf("matrix_addition: Matrix A is null\n");
        return NULL;
    }

    if (!B)
    {
        printf("matrix_addition: Matrix B is null\n");
        return NULL;
    }

    // A and B must be of the same size
    if ( (A->nc != B->nc) && (A->nr != B->nr) )
    {
        printf("matrix_addition: Matrix A and B are not of the same size\n");
        return NULL;
    }

    // Allocate a matrix object
    m_added = matrix_create(A->nr, A->nc);

    // Compute matrix addition
    for (i = 0; i < A->nr; i++)
        for (j = 0; j < A->nc; j++)
            m_added->data[i][j] = A->data[i][j] + B->data[i][j];

    return m_added;
}

/*! @brief			Multiply a matrix with a scalar
	@param matrix   Matrix to multiply
	@param scalar   Scalar
	@return			Multiplied matrix
 */
struct Matrix *matrix_multiplication_scalar (struct Matrix *matrix,
                    double scalar)
{
    size_t i = 0, j = 0;

    // Check pointers
    if (!matrix)
    {
        printf("matrix_multiplication_scalar: Matrix is null\n");
        return NULL;
    }

    // Compute multiplication with scalar
    for (i = 0; i < matrix->nr; i++)
        for (j = 0; j < matrix->nc; j++)
            matrix->data[i][j] *= scalar;

    return matrix;
}

/*! @brief			Multiply a matrix with another matrix
	@param A		First Matrix
	@param B		Second Matrix
	@return			Multiplied matrix
 */
struct Matrix *matrix_multiplication (struct Matrix *A, struct Matrix *B)
{
    // A column number is equal to B row number
    size_t rowA = 0, colB = 0;
    size_t colA = 0, rowB = 0;
    double lineValue = 0;
    // Result matrix
    struct Matrix *matrix = NULL;

    // Check pointers
    if (!A)
    {
        printf("matrix_multiplication: Matrix A is null\n");
        return NULL;
    }

    if (!B)
    {
        printf("matrix_multiplication: Matrix B is null\n");
        return NULL;
    }

    // A column number must be equal to B row number
    if ( A->nc != B->nr )
    {
        printf("matrix_multiplication: A->nc != B->nr\n");
        return NULL;
    }

    // Allocate memory for multiplied matrix
    matrix = matrix_create(A->nr, B->nc);

    // Compute multiplication ( complexity of O(n^3) ,
    // the best is O(n^2,36) but isn't implemented here )
    for (rowA = 0; rowA < A->nr; rowA++)
    {
        for (colB = 0; colB < B->nc; colB++)
        {
            for (colA = 0; colA < A->nc; colA++)
            {
                rowB = colA;
                lineValue += A->data[rowA][colA] * B->data[rowB][colB];
            }
            matrix->data[rowA][colB] = lineValue;
            lineValue = 0;
        }
    }

    return matrix;
}

/*! @brief			Compute transpose of a matrix
	@param  matrix  Matrix to compute transpose from
	@return			Transpose of matrix
 */
struct Matrix *matrix_transpose (struct Matrix *matrix)
{
    size_t i = 0, j = 0;
    // Transpose
    struct Matrix *m_transpose = NULL;

    // Check pointers
    if (!matrix)
    {
        printf("matrix_transpose: matrix is null\n");
        return NULL;
    }

    // Allocate memory for transpose
    m_transpose = matrix_create(matrix->nc, matrix->nr);

    // Tranpose
    for (i = 0; i < m_transpose->nr; i++)
        for (j = 0; j < m_transpose->nc; j++)
            m_transpose->data[j][i] = matrix->data[i][j];

    return m_transpose;
}

/*! @brief			Swap two rows between them
	@param  matrix  Matrix where the swap occurs
	@param  row1	Row number of the first row to swap
	@param  row2	Row number of the second row to swap
	@return			ret code
 */
int matrix_row_swap (struct Matrix *matrix, size_t row1, size_t row2)
{
    // Temporary pointer of a row
    double *m_row = NULL;

    // Check pointers
    if (!matrix)
    {
        printf("matrix_row_swap: matrix is null\n");
        return ERROR_NULL_POINTER;
    }

    // Swapping rows
    m_row = matrix->data[row1];
    matrix->data[row1] = matrix->data[row2];
    matrix->data[row2] = m_row;

    return 0;
}

/*! @brief  Comatrix function
*   @param  matrix  Matrix to search co-matrix for
*   @param  row     Row index to cross out
*   @return comatrix
*/
struct Matrix *matrix_com (struct Matrix *matrix, size_t row)
{
    size_t i, j;
    struct Matrix *comatrix;

    // Check pointers
    if (!matrix)
    {
        printf("matrix_com: matrix is null\n");
        return NULL;
    }

    if (row >= matrix->nr)
    {
        printf("matrix_com: row deprecated is higher than max rows\n");
        return NULL;
    }

    comatrix = matrix_create (matrix->nr, matrix->nc);

    for (i = row; i < matrix->nr; i++)
    {
        for (j = 0; j < matrix->nc; j++)
        {
        }
    }

    return comatrix;
}

/*! @brief Sort vector of dots
*   @param matrix   Vector of dots to sort
*   @return Sorted vector or NULL if error
*/
struct Matrix *matrix_sort_vector2d (struct Matrix *matrix)
{
    size_t i, j;
    double temp;

    // We check for matrix existence
    if (!matrix)
    {
        fprintf(stderr, "matrix_sort_vector: Matrix NULL\n");
        return NULL;
    }

    // We check for matrix type : 2 lines, x columns
    //  / x1 x2 x3 x4 ... xn \
    //  \ y1 y2 y3 y4 ... yn /
    if (matrix->nr > 2)
    {
        fprintf(stderr, "matrix_sort_vector: Matrix not a 2d vector\n");
        return NULL;
    }

    // We sort the vectors according to their abscisses
    for (i = 0; i < matrix->nc - 1; i++)
    {
        for (j = i + 1; j < matrix->nc; j++)
        {
            if (matrix->data[X_AXIS][i] > matrix->data[X_AXIS][j])
            {
                // Swap abscisses
                temp = matrix->data[X_AXIS][i];
                matrix->data[X_AXIS][i] = matrix->data[X_AXIS][j];
                matrix->data[X_AXIS][j] = temp;
                // Swap ordonnee
                temp = matrix->data[Y_AXIS][i];
                matrix->data[Y_AXIS][i] = matrix->data[Y_AXIS][j];
                matrix->data[Y_AXIS][j] = temp;
            }
        }
    }

    return matrix;
}

/*! @brief Convert an array of dots to a matrix
*   @param dots     Array of dots
*   @return Converted array of dots
*/
struct Matrix *dotArray_to_vector2d (struct t_dot *dots, size_t size)
{
    size_t i;
    struct Matrix *vector2d;

    vector2d = matrix_create(2, size);

    for (i = 0; i < size; i++)
    {
        vector2d->data[X_AXIS][i] = dots[i].x;
        vector2d->data[Y_AXIS][i] = dots[i].y;
    }

    return vector2d;
}
