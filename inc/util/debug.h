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

#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define _DEBUG_ 1
#define MESSAGE_ERROR       1
#define MESSAGE_WARNING     2
#define MESSAGE_INFO        3
#define MESSAGE_DEBUG       4

#if _DEBUG_
    #define debug_message(level, fmt, ...)                      \
        if (level == MESSAGE_ERROR)                             \
            debug_printf(level, stderr, fmt, ##__VA_ARGS__);    \
        else                                                    \
            debug_printf(level, stdout, fmt, ##__VA_ARGS__);
#else
    #define debug_message(level, fmt, ...)
#endif

int dump (unsigned char *bytes, size_t nbytes, size_t align);
int hexdump (unsigned int line_len, char *str);

int debug_printf (int level, FILE *stream, char *fmt, ...);
int debug_set_verbose_level (int level);
int debug_get_verbose_level (void);

#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H */
