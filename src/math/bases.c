#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include "math/bases.h"

// concat bits
long bincat (long *binaire, long i) {
    double nombreBinaire = 0;
    long j = 0;

    for (j = i-1; j >= 0; j--)
        nombreBinaire = nombreBinaire + (binaire[j] * pow(10, j));

    return nombreBinaire;
}

// Converti le binaire en decimal
long bin2dec(long *bit, long nombreDeBit) {
    long valeurDecimale = 0;
    long i = 0, j = 0;

    // On parcoure bit en sens inverse car sinon on aurait 001 au lieu de 100
    for (i = nombreDeBit-1; i >= 0; i--) {
        valeurDecimale = valeurDecimale + (bit[i] * (1 << j));
        j++;
    }
    return valeurDecimale;
}

// Convertit le decimal en binaire
long dec2bin(long decimal) {
    long modulo = 0;
    long binaire = 0;
    short int i = 0;

    do {
        modulo = decimal%2;
        decimal = decimal - modulo;
        decimal = decimal/2;

        binaire = binaire + modulo * pow(10, i);

        i++;
    }
    while (decimal >= 1);

    return binaire;
}

// 
char* num2binstr (unsigned long n) {
    unsigned short int bit;
    int idxBuf;
    char *buf, *str;

    // alloc buffer
    buf = calloc(sizeof(unsigned long) * 8 + 1, sizeof(*buf));
    if (!buf)
        return NULL;

    //
    idxBuf = sizeof(unsigned long) * 8;
    while (n && idxBuf >= 0) {
        bit = n & 0x1;
        buf[idxBuf--] = bit + '0';
        n >>= 1;
    }

    str = strdup(buf + idxBuf + 1);
    free(buf);

    return str;
}

unsigned long hex2dec (char *hex, int hexlen) {
    size_t i = 0;
    unsigned long dec = 0, temp = 0;

    while (hex[i] != '\0') {
        const int isHEXA = (hex[i] >= 'A') && (hex[i] <= 'F');
        const int ishexa = (hex[i] >= 'a') && (hex[i] <= 'f');
        const int isdigit = (hex[i] >= '0') && (hex[i] <= '9');

        if (ishexa) {
            temp = hex[i] - 'a' + 10;
        }
        else if (isHEXA) {
            temp = hex[i] - 'A' + 10;
        }
        else if (isdigit) {
            temp = hex[i] - '0';
        }
        //dec = dec + temp * pow(16, j);
        dec = dec * 16 + temp;
        //dec = dec + temp * ((1 << 4) << j);

        i++;
        hexlen--;
    }

    return dec;
}

long* bin2bits (long bin, long *bits) {
    size_t i = 0;
    size_t length = sizeof(bin) * 8;
    char *buffer = malloc (sizeof(*buffer) * length);
    bits = realloc (bits, sizeof(*bits) * length);

    if ((buffer != NULL) && (bits != NULL)) {
        snprintf (buffer, length, "%ld", bin);

        while (*buffer) {
            bits[i] = *buffer - '0';
            i++;
            buffer++;
        }
    }
    
    return bits;
}

