#ifndef _VECTOR_SPACE_H
#define _VECTOR_SPACE_H

#include <stdlib.h>

/*! @brief Dot structure */
typedef struct t_dot
{
	double x, y, z;
} t_dot;

/*! @brief  Cubic Interpolation */
void dot_array_sort (struct t_dot *dots, size_t size);

#endif
