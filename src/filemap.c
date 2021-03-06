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

#include <string.h>

// for mmap
#if !defined (WIN32) && !defined (_WIN32_)
#include <sys/mman.h>
#endif

#include "file.h"
#include "filemap.h"
#include "filemap_internal.h"
#include "string_ext.h"

#include "util/debug.h"

#define MB  1024*1024
#define _FASTER_FILEMAP_

static struct filemap_list_t *filemaps = NULL;

// check if file was loaded in memory
struct filemap_t *_filemap_search_fp (struct filemap_list_t *root, FILE *fp, int sz);
struct filemap_t *_filemap_exist_fp (FILE *fp, int sz);
struct filemap_t *_filemap_create_from_fp_ex (FILE *fp, int sz);
// for mem
struct filemap_t *_filemap_search_mem (struct filemap_list_t *root, uint8_t *mem, int sz);
struct filemap_t *_filemap_exist_mem (uint8_t *mem, int sz);

// create filemap
struct filemap_t *filemap_create (char *filename)
{
    int sz_file;
    FILE *fp;

    fp = fopen (filename, "r");
    if (!fp) {
        debug_printf (MESSAGE_ERROR, stderr, "error: filemap_create(): Failed opening (r) %s\n", filename);
        return NULL;
    }

    sz_file = file_get_size(fp);

    fclose (fp);

    return filemap_create_ex (filename, sz_file);
}

// create filemap
struct filemap_t *filemap_create_ex (char *filename, int sz)
{
    struct filemap_t *fmap;
    FILE *fp;

    if (!filename ||  sz <= 0) {
        debug_printf (MESSAGE_ERROR, stderr, "error: filemap_create_ex(): Bad parameters\n");
        return NULL;
    }

    fp = fopen (filename, "r");
    if (!fp) {
        debug_printf (MESSAGE_ERROR, stderr, "error: filemap_create_ex(): Failed opening (r) %s\n", filename);
        return NULL;
    }

    fmap = filemap_create_from_fp_ex (fp, sz);
    fmap->sz_hashed = sz;

    fclose (fp);

    return fmap;
}

struct filemap_t *filemap_create_from_fp (FILE *fp)
{
    return filemap_create_from_fp_ex (fp, file_get_size (fp));
}

struct filemap_t *filemap_create_from_fp_ex (FILE *fp, int sz)
{
    struct filemap_t *filemap;

    // check filemap existence
    filemap = _filemap_exist_fp (fp, sz);
    if (filemap) {
        debug_printf (MESSAGE_INFO, stdout, "info : filemap_create_from_fp_ex(): Filemap already exist, borrowing it\n");
        return filemap;
    }

    return _filemap_create_from_fp_ex (fp, sz);
}

struct filemap_t *_filemap_create_from_fp_ex (FILE *fp, int sz)
{
    struct filemap_t *filemap;
    size_t foffset, sz_map;

    // add filemap
    filemap = malloc (sizeof(struct filemap_t));
    filemap->fp = fp;

    // original offset
    foffset = ftell(fp);
    // file size
    sz_map = file_get_size (fp);

    // map file
#if !defined (WIN32) && !defined (_WIN32_)
    // use OS filemap
    filemap->map = mmap (NULL, sz_map, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_POPULATE, fileno (fp), 0);

    // if OS filemap is successful
    // then set mmaped flag
    if (filemap->map != MAP_FAILED)
        filemap->is_mmaped = 1;
    // else use custom filemap
    else {
        debug_printf (MESSAGE_ERROR, stderr, "error: _filemap_create_from_fp_ex(): Failed OS mapping\n");
#endif
        // set mmap flag to 0
        filemap->is_mmaped = 0;
        // map file
        filemap->map = malloc (sz_map);
        fseek (fp, 0, SEEK_SET);
        fread (filemap->map, filemap->sz_map, 1, fp);
#if !defined (WIN32) && !defined (_WIN32_)
    }
#endif

    // restore original file offset
    fseek (fp, foffset, SEEK_SET);

    filemap->sz_map = sz_map;

    // hash
#ifdef _FASTER_FILEMAP_
    filemap->hash = fnv_hash (filemap->map, (filemap->sz_map > 1*MB? 1*MB : filemap->sz_map));
#else
    filemap->hash = fnv_hash (filemap->map, filemap->sz_map);
#endif

    // add filemap in binary tree
    filemap_add_fmap (&filemaps, filemap);

    return filemap;
}

struct filemap_t *filemap_create_from_memory (uint8_t *bytes, int sz)
{
	struct filemap_t *fmap;

	// check filemap existence
	fmap = _filemap_exist_mem(bytes, sz);
	if (fmap) {
		debug_printf(MESSAGE_INFO, stdout, "info : filemap_create_from_memory(): Filemap already exist, borrowing it\n");
		return fmap;
	}

	// add filemap
	fmap = malloc(sizeof(*fmap));
	fmap->fp = NULL;

	// map file
	// set mmap flag to 0
	fmap->is_mmaped = 0;
	// map file
	fmap->map = malloc(sz);
	memcpy(fmap->map, bytes, sz);

	fmap->sz_map = sz;

	// hash
#ifdef _FASTER_FILEMAP_
	fmap->hash = fnv_hash(fmap->map, (fmap->sz_map > 1 * MB ? 1 * MB : fmap->sz_map));
#else
	fmap->hash = fnv_hash(fmap->map, fmap->sz_map);
#endif

	// add filemap in binary tree
	filemap_add_fmap(&filemaps, fmap);

	return fmap;
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
#if !defined (WIN32) && !defined (_WIN32_)
    if ((*filemap)->map) {
        if ((*filemap)->is_mmaped)
            munmap ((*filemap)->map, (*filemap)->sz_map);
        else
#endif
            free((*filemap)->map);
#if !defined (WIN32) && !defined (_WIN32_)
    }
#endif
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

struct filemap_t *_filemap_search_fp (struct filemap_list_t *root, FILE *fp, int sz)
{
    uint64_t hash;
    struct filemap_t *fmap, *needle;

    needle = _filemap_create_from_fp_ex (fp, sz);

    // hash and all
#ifdef _FASTER_FILEMAP_
    hash = fnv_hash (needle->map, (needle->sz_map > 1*MB? 1*MB : needle->sz_map));
#else
    hash = fnv_hash (needle->map, needle->sz_map);
#endif
    fmap = __filemap_search (root, hash);
    filemap_destroy (&needle);

    return fmap;
}

// check if file was loaded in memory
struct filemap_t *_filemap_exist_fp (FILE *fp, int sz)
{
    // if list doesn't exist then it isn't loaded
    if (!filemaps || !fp || sz <= 0) {
        debug_printf (MESSAGE_ERROR, stderr, "error: _filemap_exist_fp(): Bad parameters\n");
        return NULL;
    }

    return _filemap_search_fp (filemaps, fp, sz);
}

struct filemap_t *_filemap_search_mem (struct filemap_list_t *root, uint8_t *mem, int sz)
{
    uint64_t hash;
    struct filemap_t *fmap;

    // hash and all
#ifdef _FASTER_FILEMAP_
    hash = fnv_hash (mem, (sz > 1*MB? 1*MB : sz));
#else
    hash = fnv_hash (mem, sz);
#endif
    fmap = __filemap_search (root, hash);

    return fmap;
}

// check if file was loaded in memory
struct filemap_t *_filemap_exist_mem (uint8_t *mem, int sz)
{
    // if list doesn't exist then it isn't loaded
    if (!filemaps || !mem || sz <= 0) {
        debug_printf (MESSAGE_ERROR, stderr, "error: _filemap_exist_fp(): Bad parameters\n");
        return NULL;
    }

    return _filemap_search_mem (filemaps, mem, sz);
}
