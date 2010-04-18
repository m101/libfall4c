#ifdef _WIN32

#include "_ansi.h"

char *
_DEFUN (strtok_r, (s, delim, lasts),
	register char *s _AND
	register const char *delim _AND
	char **lasts);

#endif
