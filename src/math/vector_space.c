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
