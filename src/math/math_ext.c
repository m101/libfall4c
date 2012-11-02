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

#include <stdint.h>

// great common divisor recursive
uint64_t gcd_r (uint64_t dividend, uint64_t divisor) {
    uint64_t rest;

    rest = dividend % divisor;

    //
    if (rest == 0)
        return divisor;
    gcd_r(divisor, rest);

    return rest;
}

// great common divisor
uint64_t gcd (uint64_t dividend, uint64_t divisor) {
    if (dividend == 0 || divisor == 0)
        return -1;
    return gcd_r(dividend, divisor);
}

// lowest common multiple
uint64_t lcm (uint64_t dividend, uint64_t divisor) {
    uint64_t valGcd;

    // get gcd
    valGcd = gcd(dividend, divisor);
    if (valGcd < 0)
        return -1;

    // lcm
    return (dividend * divisor / valGcd);
}

