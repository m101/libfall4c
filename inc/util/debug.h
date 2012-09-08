#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define _DEBUG_ 1

#if _DEBUG_
    #define debug_message(stream, fmt, ...)  fprintf(stream, fmt, ##__VA_ARGS__)
#else
    #define debug_message(level, fmt, ...)
#endif

int dump (unsigned char *bytes, size_t nbytes, size_t align);

#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H */
