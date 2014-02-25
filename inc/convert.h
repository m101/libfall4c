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

#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <stdint.h>

uint8_t *bin_to_ascii (uint8_t *hash, int len);
// hex string to binary digits
unsigned int hexstr_to_num (unsigned char *str, size_t len);

#endif /* _CONVERT_H_ */
