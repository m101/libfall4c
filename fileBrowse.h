#ifndef _FILE_BROWSE_H
#define _FILE_BROWSE_H

#include <stdlib.h>
#include <stdio.h>

void dirwalk (char *dirname, void (*fonction)(char *));
void readTreeNode (char *dirname);

#endif
