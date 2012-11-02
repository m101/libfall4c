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

#ifndef _PROBABILITE_H
#define _PROBABILITE_H

#ifdef __cplusplus
extern "C"
{
#endif

    unsigned long factorielleIter(unsigned long chiffre);
    unsigned long factorielle (unsigned long n, unsigned long accu);
    unsigned long nCr(unsigned long n, unsigned long p);
    double loiBinomiale(long n, long k, double p);

#ifdef __cplusplus
}
#endif

#endif /* _PROBABILITE_H */
