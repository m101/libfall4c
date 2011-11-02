#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// minimum value
int min (char *fmt, ...)
{
    int minimum = 0, value = 0, first = 0;
    char *fmtCopy = malloc(strlen(fmt) * sizeof(*fmt));
    char *pFmt = NULL, *pFmtCopy = NULL;
    va_list arg;

    va_start(arg, fmt);

    strcpy(fmtCopy, fmt);

    pFmt = strtok_r(fmtCopy, "%", &pFmtCopy);
    while ( pFmt != NULL )
    {
        if ( strcmp(pFmt, "%ld") || strcmp(pFmt, "%d") || strcmp(pFmt, "%u") )
        {
            value = va_arg(arg, int);
            if ( minimum > value )
                minimum = value;
            else if ( !first )
            {
                minimum = value;
                first = 1;
            }
        }
        pFmt = strtok_r(NULL, "%", &pFmtCopy);
    }

    va_end(arg);

    return minimum;
}

// maximum value
int max (char *fmt, ...)
{
    int maximum = 0, value = 0, first = 0;
    char *fmtCopy = malloc(strlen(fmt) * sizeof(*fmt));
    char *pFmt = NULL, *pFmtCopy = NULL;
    va_list arg;

    va_start(arg, fmt);

    strcpy(fmtCopy, fmt);

    pFmt = strtok_r(fmtCopy, "%", &pFmtCopy);
    while ( pFmt != NULL )
    {
        if ( strcmp(pFmt, "%ld") || strcmp(pFmt, "%d") || strcmp(pFmt, "%u") )
        {
            value = va_arg(arg, int);
            if ( maximum < value )
                maximum = value;
            else if ( !first )
            {
                maximum = value;
                first = 1;
            }
        }
        pFmt = strtok_r(NULL, "%", &pFmtCopy);
    }

    va_end(arg);

    return maximum;
}
