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
#include <stdint.h>

#include "data/data_ops.h"

struct data_ops *data_ops_new (void)
{
    struct data_ops *data_ops;

    data_ops = calloc (1, sizeof (*data_ops));
    if (!data_ops) {
        fprintf (stderr, "error: data_ops_new(): Failed allocating data_ops\n");
        return NULL;
    }

    data_ops->comparator = comparator_no_ops;
    data_ops->destroy = destroy_no_ops;
    data_ops->get_size = get_size_no_ops;
    data_ops->show = show_no_ops;

    return data_ops;
}

int comparator_no_ops (void *data1, void *data2)
{
    return (uint32_t) data1 - (uint32_t) data2;
}

void destroy_no_ops (void **data)
{
    return;
}

void free_no_ops (void *data)
{
    return;
}

void destroy_allocated (void **data)
{
    if (!data) {
        fprintf (stderr, "error: destroy_allocated(): Bad parameter(s)\n");
        return;
    }

    free (*data);
}

size_t get_size_no_ops (void *data)
{
    return 0;
}

void show_no_ops (void *data)
{
    return;
}

