/*
    libbparse - Binary file parser library
    Copyright (C) 2010  m_101

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include "data/bytes.h"

struct bytes *bytes_new (size_t size)
{
    struct bytes *bytes;

    bytes = calloc(1, sizeof(*bytes));
    bytes->data = calloc(size, sizeof(*(bytes->data)));
    bytes->capacity = size;

    return bytes;
}

struct bytes *bytes_realloc (struct bytes *bytes, size_t size)
{
    if (!bytes)
        return NULL;

    bytes->capacity = size;
    bytes->data = realloc(bytes->data, bytes->capacity);
    if (bytes->data == NULL)
        return NULL;

    return bytes;
}

void bytes_destroy (struct bytes **bytes)
{
    if (!bytes)
        return;
    if (!*bytes)
        return;

    free((*bytes)->data);
    free(*bytes);
    *bytes = NULL;
}

