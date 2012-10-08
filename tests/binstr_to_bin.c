#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "util/debug.h"
#include "string_ext.h"

#define HEXSTR  "0x0xdeadbeefcafebabef"

int main (int argc, char *argv[])
{
    uint8_t *bin;
    char *binstr;
    int len_binstr;

    if (argc < 2) {
        printf("Usage: %s binstr\n", argv[0]);
        exit(1);
    }

    binstr = strdup(argv[1]);
    len_binstr = strlen(binstr);
    bin = binstr_to_bin(binstr, len_binstr);
    if (!bin) {
        fprintf(stderr, "error: Failed to convert\n");
        exit(1);
    }

    printf("original: '%s'\n", binstr);
    dump(bin, len_binstr, 16);

    free(binstr);

    return 0;
}

