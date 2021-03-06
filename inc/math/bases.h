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

#ifndef _BASES_H
#define _BASES_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32
#define snprintf _snprintf
#define strdup _strdup
#endif

    long concatenationBinaire(long *binaire, long i);
    long bin2dec(long *binaire, long i);
    long dec2bin(long decimal);

#ifdef __cplusplus
}
#endif

#endif /* _BASES_H */

