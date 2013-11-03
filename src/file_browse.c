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

// k&r
#include <stdio.h>
#include <stdlib.h>

#include <string.h>


#include <sys/stat.h>

#ifdef __linux__
#include <dirent.h>
#include <unistd.h>

#include "data/list.h"
#include "file_browse.h"

#define MAX_PATH 2048

// show directory entry 1st level
int dirwalk (char *dirname, int (*function)(char *, void **), void **data, int depth)
{
    char *name;
    struct stat statbuf;
    struct dirent *dp;
    DIR *dfd;

    if (!dirname || !function || !data || depth <= 0) {
        printf("debug: dirwalk(): Bad parameters\n");
        return -1;
    }

    if ((dfd = opendir(dirname)) == NULL) {
        fprintf(stderr, "error: dirwalk(): can't open %s\n", dirname);
        return -1;
    }

    name = calloc(MAX_PATH, sizeof(*name));
    if (!name)
        goto out_dirwalk;

    while ((dp = readdir(dfd)) != NULL) {
        snprintf(name, MAX_PATH, "%s/%s", dirname, dp->d_name);

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        if (stat(name, &statbuf) < 0) {
            fprintf(stderr, "error: dirwalk(): can't access '%s'\n", name);
            goto out_dirwalk;
        }

        if (S_ISDIR(statbuf.st_mode) && depth > 0) {
            printf("debug: dirwalk(): this is a directory: '%s' (depth = %d)\n", name, depth);
            dirwalk (name, function, data, depth - 1);
        }
        else if (S_ISREG(statbuf.st_mode)) {
            printf("debug: dirwalk(): this is a file: '%s'\n", name);
            (*function)(strdup(name), data);
        }
    }

out_dirwalk:
    printf("debug: dirwalk(): Freeing dfd and name\n");
    closedir(dfd);
    free(name);

    return 0;
}

// show all directory entries - subdirs included
int _dirls (char *filename, void **data)
{
    struct stat statbuf;

    if (stat(filename, &statbuf) < 0) {
        fprintf(stderr, "error: _dirls(): can't access '%s'\n", filename);
        return -1;
    }

    printf("%8ld %s\n", statbuf.st_size, filename);

    return 0;
}

int dirls (char *dirname, int depth)
{
    dirwalk (dirname, _dirls, NULL, depth);
}

int _dir_list (char *filename, void **data)
{
    struct list_simple **list_filenames;

    printf("debug: _dir_list(): filename: '%s'\n", filename);
    list_filenames = data;
    printf("debug: _dir_list(): list_filenames: %p\n", list_filenames);

    list_append_data (list_filenames, filename);

    return 0;
}

struct list_simple *dir_list (char *dirname, int depth)
{
    struct list_simple *list_files = NULL;

    dirwalk (dirname, _dir_list, &list_files, depth);

    return list_files;
}

#endif
