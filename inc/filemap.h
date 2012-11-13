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

#ifndef _FILEMAP_H_
#define _FILEMAP_H_

#include <stdlib.h>
#include <stdint.h>

struct filemap_t
{
    uint64_t hash;
    char *filename;
	size_t sz_filename;
    FILE *fp;
    // filemap
    unsigned char *map;
    size_t sz_map;
};

// create filemap
struct filemap_t *filemap_create (char *filename);
struct filemap_t *filemap_create_from_fp (FILE *fp);
// destroy filemap
void filemap_destroy (struct filemap_t **filemap);

#endif /* _FILEMAP_H_ */

