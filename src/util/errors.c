#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "errors.h"

// print fatal message
void fatal (char *fmt, ...) {
    va_list va;

    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
    perror("perror");

    exit(1);
}

