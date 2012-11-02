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

#ifndef _TRIGO_H
#define _TRIGO_H

#ifndef M_PI
 #define M_PI 3,141 592 653 589 793 238 462 643 383 279 502 884 197 169 399 375
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    float degree2rad(long degree);

#define degree2rad(degree) degree * (2.0*M_PI)/360.0

#ifdef __cplusplus
}
#endif

#endif /* _PROBABILITE_H */
