#include <stdio.h>
#include <stdlib.h>

// dump
int dump (unsigned char *bytes, size_t nbytes, size_t align) {
    size_t i, j, last;
    
    if (!bytes || !nbytes)
        return -1;

    // first part of line is hex
    for (i = 0, last = 0; i < nbytes; i++) {
        printf ("%02x ", bytes[i]);
        // if we got to the alignment value or end of bytes
        // we print the second part of the line
        if ( (i + 1) % align == 0 || i == nbytes - 1 ) {
            // we print spaces if we arrived at end of bytes
            if (i == nbytes - 1) {
                for (j = nbytes % align; j < align; j++)
                    printf("   ");
            }
            // separation
            printf ("| ");
            // second part of line is corresponding character
            for (j = last; j < last + align && j < nbytes;  j++) {
                if (isprint(bytes[j]))
                    printf ("%c", bytes[j]);
                else
                    putchar ('.');
            }
            putchar ('\n');
            last = i + 1;
        }
    }

    return 0;
}
