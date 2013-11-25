#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

uint8_t *bin_to_ascii (uint8_t *hash, int len)
{
    int idx_hash;
    char *token, *token_ptr;

    // bad parameters
    if (!hash || len <= 0) {
        fprintf (stderr, "error: Bad parameter(s)\n");
        return NULL;
    }

    //
    token = calloc (len * 2 + 1, sizeof (*token));
    if (!token) {
        fprintf (stderr, "error: bin_to_ascii(): Failed allocating token\n");
        return NULL;
    }

    //
    token_ptr = token;
    for (idx_hash = 0; idx_hash < len; idx_hash++) {
        snprintf (token_ptr, 3, "%02x", hash[idx_hash]);
        token_ptr += 2;
    }

    return token;
}

// hex string to binary digits
unsigned int hexstr_to_num (unsigned char *str, size_t len)
{
    int num;
    size_t i;

    // check pointers
    if (!str || !len)
        return -1;

    //
    num = 0;
    for (i = 0; *str && i < len; ++str, ++i) {
        if (!isdigit(*str))
            continue;
        // get decimal digit
        num |= *str - '0';
        // get hex digit
        if (num >= 0xa)
            num -= 7;
        num <<= 4;
    }

    return num;
}

