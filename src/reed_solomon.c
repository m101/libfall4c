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
#include <stdio.h>

#include "simpleMaths.h"

long reed_solomon_error (long data[], size_t i, long dataSum, long dataSumBalanced, long *i_error)
{
    // size_t parite = (i + 1) % 2;
    long sum = 0, m_balancedSum = 0, error = 0;
    //size_t i_error = 0;

    sum = accumulate(data, 3);

    m_balancedSum = balancedSum (data, 3);

    error = sum - dataSum;

    *i_error = (m_balancedSum - dataSumBalanced) / error;
    *i_error -= 1;

    return error;
}

void reed_solomon_correct_error (long data[], size_t i, long error, size_t i_error)
{
    data[i_error] -= error;
}
