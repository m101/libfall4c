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

double sequence_sum_arithmethic (long n, double nfirst, double nlast) {
    double sum_results = n * (nfirst + nlast)/2;

    return sum_results;
}

double sequence_sum_geometric (long n, double nfirst, double nlast) {
    double sum_results = n * (nfirst + nlast)/2;

    return sum_results;
}

long fibonacci (long position) {
    int i = 0;
    long nombre1 = 0, nombre2 = 1, temp = 0;


    for (i = 0; i < position; i++) {
        temp = nombre1;
        nombre1 = nombre2;
        nombre2 = temp + nombre2;
    }

    return nombre1;
}

