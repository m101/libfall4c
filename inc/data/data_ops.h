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

#ifndef _DATA_OPS_H_
#define _DATA_OPS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

struct data_ops {
    int (*comparator) (void *data1, void *data2);
    void (*destroy) (void **data);
    size_t (*get_size) (void *data);
    void (*show) (void *data);
};

int comparator_no_ops (void *data1, void *data2);
void destroy_no_ops (void **data);
void get_size_no_ops (void *data);
void show_no_ops (void *data);

#ifdef __cplusplus
}
#endif

#endif /* _DATA_OPS_H_ */

