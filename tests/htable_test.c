#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fall4c.h"

int main (int argc, char *argv[])
{
    int idx;
    char buffer[256];
    clock_t start, end, total;
    struct hashtable_t *htable;

    printf ("[+] Allocating memory\n");
    htable = hashtable_new();

    start = clock();
    for (idx = 0; idx < 10000000; idx++) {
        snprintf (buffer, 256, "key%d", idx);
        hashtable_set_value (&htable, buffer, "node");
    }
    end = clock();

    total = end - start;

    printf ("Clocks      : %d\n", total);
    printf ("Clocks / Sec: %d\n", CLOCKS_PER_SEC);
    printf ("time        : %lf sec\n", (double) total / CLOCKS_PER_SEC);

    printf ("[+] Freeing memory\n");
    start = clock();
    hashtable_destroy (&htable);
    end = clock();

    total = end - start;

    printf ("Clocks      : %d\n", total);
    printf ("Clocks / Sec: %d\n", CLOCKS_PER_SEC);
    printf ("time        : %lf sec\n", (double) total / CLOCKS_PER_SEC);

    return 0;
}

