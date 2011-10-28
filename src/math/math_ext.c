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

