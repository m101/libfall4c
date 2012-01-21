#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

// dump
int dump (unsigned char *bytes, size_t nbytes, size_t align) {
    size_t idxBytes, j, last;
    int nDisp;
    
    if (!bytes || !nbytes)
        return -1;

    // first part of line is hex
    for (idxBytes = 0, last = 0; idxBytes < nbytes; idxBytes++) {
        printf ("%02x ", bytes[idxBytes]);
        // if we got to the alignment value or end of bytes
        // we print the second part of the line
        if ( (idxBytes + 1) % align == 0 || idxBytes == nbytes - 1 ) {
            // we print spaces if we arrived at end of bytes
            if (idxBytes == nbytes - 1) {
                // compute the number of spaces to show
                nDisp = align - (nbytes % align);
                nDisp = (nbytes % align) ? nDisp : 0;
                for (j = 0; j < nDisp; j++)
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
            last = idxBytes + 1;
        }
    }

    return 0;
}

