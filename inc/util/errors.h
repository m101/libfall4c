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

#ifndef _UTIL_ERRORS_H_
#define _UTIL_ERRORS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ERROR_NULL_POINTER  -1
#define ERROR_OUTOFRANGE    -2

// print fatal message
void fatal (char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_ERRORS_H_ */
