// k&r
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fileBrowse.h"

#define MAX_PATH 1000

// show directory entry 1st level
void dirls (char *dirname, void (*fonction)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dirname)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dirname);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name, ".") == 0
                || strcmp(dp->d_name, ".."))
            continue;     /* skip self and parent */
        if (strlen(dirname)+strlen(dp->d_name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                    dirname, dp->d_name);
        else
        {
            sprintf(name, "%s/%s", dirname, dp->d_name);
            (*fonction)(name);
        }
    }
    closedir(dfd);
}

// show all directory entries - subdirs included
void dirwalk (char *dirname)
{
    struct stat statbuf;

    if (stat(dirname, &statbuf) != 0)
    {
        fprintf(stderr, "readTreeNode : can't access %s\n", dirname);
        return;
    }

    if (S_ISDIR(statbuf.st_mode))
        dirls (dirname, dirwalk);

    printf("%8ld %s\n", statbuf.st_size, dirname);
}
