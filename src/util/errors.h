#ifndef _UTIL_ERRORS_H_
#define _UTIL_ERRORS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ERROR_NULL_POINTER  -1
#define ERROR_OUTOFRANGE    -2

// print fatal message
void fatal (char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_ERRORS_H_ */
