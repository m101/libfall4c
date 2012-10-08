#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

// dump
int dump (unsigned char *bytes, size_t nbytes, size_t align) {
    size_t idx_bytes, j, last;
    int n_disp;
    
    if (!bytes || !nbytes)
        return -1;

    // first part of line is hex
    for (idx_bytes = 0, last = 0; idx_bytes < nbytes; idx_bytes++) {
        printf ("%02x ", bytes[idx_bytes]);
        // if we got to the alignment value or end of bytes
        // we print the second part of the line
        if ( (idx_bytes + 1) % align == 0 || idx_bytes == nbytes - 1 ) {
            // we print spaces if we arrived at end of bytes
            if (idx_bytes == nbytes - 1) {
                // compute the number of spaces to show
                n_disp = align - (nbytes % align);
                n_disp = (nbytes % align) ? n_disp : 0;
                for (j = 0; j < n_disp; j++)
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
            last = idx_bytes + 1;
        }
    }

    return 0;
}

int hexdump (unsigned int line_len, char *str)
{
    char *c, *hex;
    size_t i;

    if (!line_len || !str) {
        fprintf(stderr, "Error: couldn't dump correctly data\n");
        return -1;
    }

    c = str;
    hex = c;
    do {
        printf("%2x ", *c);
        if ( ((c - str + 1) % line_len == 0 && c != str)
                || ((c - str + 1)%line_len != 0 && *(c+1) == '\0') ) {
            if ( (c - str + 1) % line_len != 0 && *(c+1) == '\0' ) {
                for (i = 0; i < line_len - ((c - str + 1) % line_len); i++)
                    printf("%2c ", ' ');
            }

            printf("| ");
            do {
                if ( (unsigned long)hex % (unsigned long)(c+1) == 0 )
                    break;

                if ( isdigit(*hex) || isalpha(*hex) )
                    printf("%c ", *hex);
                else
                    printf(". ");

            }
            while (hex++);
            printf("\n");
        }

        c++;
    }
    while(*c);
    printf("\n");

    return 0;
}


