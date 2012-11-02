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

#include "math/vector_space.h"

/*! @brief  Cubic Interpolation
*   @param  dots    Matrix of dots
*   @param  size    Size of matrix
*/
void dot_array_sort (struct t_dot *dots, size_t size)
{
    size_t i, j;
    struct t_dot temp;

    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (dots[i].x > dots[j].x)
            {
                temp = dots[i];
                dots[i] = dots[j];
                dots[j] = temp;
            }
        }
    }
}
