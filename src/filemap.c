/*
    libbparse - Binary file parser library
    Copyright (C) 2010  m_101

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "filemap.h"
#include "filemap_internal.h"
#include "string_ext.h"

static struct filemap_list_t *filemaps = NULL;

// create filemap
struct filemap_t *filemap_create (char *filename)
{
    struct filemap_t *fmap;
    FILE *fp;

    if (!filename) {
        fprintf (stderr, "error: filemap_create(): Bad parameters\n");
        return NULL;
    }

    // check filemap existence
    fmap = filemap_exist (filename);
    if (fmap) {
        fprintf (stderr, "info : filemap_create_from_fp(): Filemap already exist, borrowing it\n");
        return fmap;
    }

    fp = fopen (filename, "r");
    if (!fp) {
        fprintf (stderr, "error: filemap_create(): Failed opening (r) %s\n", filename);
        return NULL;
    }

    fmap = filemap_create_from_fp (fp);

    fclose (fp);

    return fmap;
}

struct filemap_t *filemap_create_from_fp (FILE *fp) {
    struct filemap_t *filemap;
    size_t foffset, sz_map;

    // TODO: check filemap existence

    // add filemap
    filemap = malloc (sizeof(struct filemap_t));
    filemap->fp = fp;

    // map file
    // original offset
    foffset = ftell(fp);
    fseek (fp, 0, SEEK_END);
    // file size
    sz_map = ftell(fp);
    filemap->map = malloc (sz_map);
    filemap->sz_map = sz_map;
    // map file
    fseek (fp, 0, SEEK_SET);
    fread (filemap->map, filemap->sz_map, 1, fp);
    // restore original file offset
    fseek (fp, foffset, SEEK_SET);

    // hash
    filemap->hash = fnv_hash (filemap->map, filemap->sz_map);

    // add filemap in binary tree
    filemap_add_fmap (&filemaps, filemap);

    return filemap;
}

// destroy filemap
void filemap_destroy (struct filemap_t **filemap) {
    if (!filemap)
        return;
    if (!*filemap)
        return;

    // remove filemap from binary tree
    filemap_remove_fmap (&filemaps, *filemap);

    // free allocated memory for filemap
    if ((*filemap)->map)
        free((*filemap)->map);
    free(*filemap);
    *filemap = NULL;
}

// add filemap in tree
struct filemap_t *filemap_add_fmap (struct filemap_list_t **root, struct filemap_t *filemap) {
    if (!root || !filemap)
        return NULL;
    // if leaf node
    // then add filemap
    if (!(*root)) {
        *root = malloc (sizeof(**root));
        (*root)->filemap = filemap;
        (*root)->next = NULL;
        (*root)->prev = NULL;
        return filemap;
    }

    // traverse tree
    if (filemap->hash < (*root)->filemap->hash)
        return filemap_add_fmap (&((*root)->prev), filemap);
    else if (filemap->hash > (*root)->filemap->hash)
        return filemap_add_fmap (&((*root)->next), filemap);
    else
        return filemap;
}

// remove filemap from tree
void filemap_remove_fmap (struct filemap_list_t **root, struct filemap_t *filemap) {
    if (!root || !filemap)
        return;
    if (!(*root))
        return;
    // if found node
    // then remove filemap
    if ((*root)->filemap == filemap) {
        if ((*root)->prev == NULL && (*root)->next == NULL) {
            free(*root);
            *root = NULL;
            return;
        }
        if ((*root)->next)
            (*root)->next->prev = (*root)->prev;
        if ((*root)->prev)
            (*root)->prev->next = (*root)->next;
        return;
    }

    // traverse tree
    if (filemap->hash < (*root)->filemap->hash)
        return filemap_remove_fmap (&((*root)->prev), filemap);
    else if (filemap->hash > (*root)->filemap->hash)
        return filemap_remove_fmap (&((*root)->next), filemap);
}

// search file pointer in tree
struct filemap_t *__filemap_search (struct filemap_list_t *root, uint64_t hash)
{
    // pointers check
    if (!root)
        return NULL;
    if (root->filemap == NULL)
        return NULL;
    // find it
    if (root->filemap->hash == hash)
        return root->filemap;

    // go through tree
    if (hash <= root->filemap->hash)
        __filemap_search (root->prev, hash);
    else if (hash > root->filemap->hash)
        __filemap_search (root->next, hash);
}

struct filemap_t *_filemap_search (struct filemap_list_t *root, char *filename)
{
    uint64_t hash;
    struct filemap_t *fmap, *needle;
    FILE *fp;

    // create filemap
    fp = fopen (filename, "r");
    if (!fp) {
        fprintf (stderr, "error: filemap_create(): Failed opening (r) %s\n", filename);
        return NULL;
    }
    needle = filemap_create_from_fp (fp);
    fclose (fp);

    // hash and all
    hash = fnv_hash (needle->map, needle->sz_map);
    fmap = __filemap_search (root, hash);
    filemap_destroy (&needle);

    return fmap;
}

// check if file was loaded in memory
struct filemap_t *filemap_exist (char *filename)
{
    // if list doesn't exist then it isn't loaded
    if (!filemaps || !filename)
        return NULL;

    return _filemap_search (filemaps, filename);
}

