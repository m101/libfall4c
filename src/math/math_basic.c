/*
    This file is part of fall4c.

    fall4c is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fall4c is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with fall4c.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#define strtok_r strtok_s
#endif

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
