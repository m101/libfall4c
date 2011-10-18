/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DICTIONNARY_H
#define _DICTIONNARY_H

#include <stdlib.h>

#define POINTERS_NB     32

// dictionnary structure
struct dict_t {
    //
    size_t count;
    //
    struct dict_elt_t *root;
    struct dict_elt_t *nodes;
    // base str
    char *str;
    long szStr;
};

struct dict_elt_t {
    size_t count;
    //
    char *str;
    size_t szStr;
    //
    unsigned long base;
    unsigned long *offsets;
    size_t szOffsets;
    //
    char *description;
    size_t szDescription;

    union {
        struct {
            struct dict_elt_t *left, *right;
        };
        struct {
            struct dict_elt_t *prev, *next;
        };
    };
};

// default dict constructor
struct dict_t* dict_new (struct dict_t **dict);
// destroy dictionnary recursively
void dict_destroy (struct dict_t **dict);
// dictionnary : insert a word
int dict_insert_word (struct dict_t *dict, char *word, int szWord);
// search a word in the dictionnary
struct dict_elt_t* dict_search_word (struct dict_t *dict, char *word, int szWord);
// find and destroy duplicates
struct dict_t* dict_destroy_dupes (struct dict_t *dict);
// build a dictionnary from a sequence of characters
struct dict_t* dict_build_from_str_static_size (struct dict_t *dict, char *str, int szStr, int szToken);
// build a dictionnary from a sequence of characters
struct dict_t* dict_build_from_str (struct dict_t *dict, char *str, int szStr, int szTokenMax);
// compute distance between equal words
struct dict_t *dict_distance (struct dict_t *dict);
// count number of offsets
int dict_offsets_count (struct dict_t *dict);
// load a dictionnary file
// struct dict_elt_t *dict_load (char *dict_filename);
// dictionnary : save to a file
// int dict_save (char *dict_file, struct dict_elt_t *dict);
// show dictionnary
void dict_show (struct dict_t *dict);

#endif
