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

#ifndef _DICTIONNARY_H
#define _DICTIONNARY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#define POINTERS_NB     16

// dictionnary structure
struct dict_t {
    //
    int count;
    //
    struct dict_node_t *root;
    struct dict_node_t *nodes;
    // base str
    char *str;
    long sz_str;
};

struct dict_node_t {
    int count;
    //
    char *str;
    int sz_str;
    //
    unsigned long base;
    int *offsets;
    int szOffsets;
    //
    char *description;
    int szDescription;

    union {
        struct {
            struct dict_node_t *left, *right;
        };
        struct {
            struct dict_node_t *prev, *next;
        };
    };
};

struct dict_t *dict_load (char *filename);
// default dict constructor
struct dict_t *dict_new (struct dict_t **dict);
// destroy dictionnary recursively
void dict_destroy (struct dict_t **dict);
// dictionnary : insert a word
int dict_insert_word (struct dict_t *dict, char *word, int sz_word);
// search a word in the dictionnary
struct dict_node_t *dict_search_word (struct dict_t *dict, char *word, int sz_word);
// find and destroy duplicates
struct dict_t *dict_destroy_dupes (struct dict_t *dict);
// build a dictionnary from a sequence of characters
struct dict_t *dict_build_from_str_static_size (struct dict_t *dict, char *str, int sz_str, int szToken);
// build a dictionnary from a sequence of characters
struct dict_t *dict_build_from_str (struct dict_t *dict, char *str, int sz_str, int szTokenMax);
// build a dictionnary from a sequence of characters
struct dict_t *dict_build_from_str_kasiski (struct dict_t *dict, char *str, int sz_str, int szTokenMax);
// compute distance between equal words
struct dict_t *dict_distance (struct dict_t *dict);
// count number of offsets
int dict_offsets_count (struct dict_t *dict);
// count number of nodes
int dict_nodes_count (struct dict_t *dict);
// load a dictionnary file
// struct dict_node_t *dict_load (char *dict_filename);
// dictionnary : save to a file
// int dict_save (char *dict_file, struct dict_node_t *dict);
// show dictionnary
void dict_show (struct dict_t *dict);

#ifdef __cplusplus
}
#endif

#endif
