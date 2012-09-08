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
