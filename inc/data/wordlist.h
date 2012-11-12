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

#ifndef _WORDLIST_H
#define _WORDLIST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdint.h>

#define POINTERS_NB     16

// wordlist structure
struct wlist_t {
    //
    int count;
    //
    struct wlist_node_t *root;
    struct wlist_node_t *nodes;
    // base str
    char *str;
    long sz_str;
};

struct wlist_node_t {
    int count;
    //
    uint64_t hash;
    char *str;
    int sz_str;
    //
    unsigned long base;
    int *offsets;
    int sz_offsets;
    //
    char *description;
    int sz_description;

    union {
        struct {
            struct wlist_node_t *left, *right;
        };
        struct {
            struct wlist_node_t *prev, *next;
        };
    };
};

struct wlist_t *wlist_load (char *filename);
// default wlist constructor
struct wlist_t *wlist_new (struct wlist_t **wlist);
// destroy wordlist recursively
void wlist_destroy (struct wlist_t **wlist);
// wordlist : insert a word
int wlist_insert_word (struct wlist_t *wlist, char *word, int sz_word);
// search a word in the wordlist
struct wlist_node_t *wlist_search_word (struct wlist_t *wlist, char *word, int sz_word);
// find and destroy duplicates
struct wlist_t *wlist_destroy_dupes (struct wlist_t *wlist);
// build a wordlist from a sequence of characters
struct wlist_t *wlist_build_from_str_static_size (struct wlist_t *wlist, char *str, int sz_str, int szToken);
// build a wordlist from a sequence of characters
struct wlist_t *wlist_build_from_str (struct wlist_t *wlist, char *str, int sz_str, int szTokenMax);
// build a wordlist from a sequence of characters
struct wlist_t *wlist_build_from_str_kasiski (struct wlist_t *wlist, char *str, int sz_str, int szTokenMax);
// compute distance between equal words
struct wlist_t *wlist_distance (struct wlist_t *wlist);
// count number of offsets
int wlist_offsets_count (struct wlist_t *wlist);
// count number of nodes
int wlist_nodes_count (struct wlist_t *wlist);
// load a wordlist file
// struct wlist_node_t *wlist_load (char *wlist_filename);
// wordlist : save to a file
// int wlist_save (char *wlist_file, struct wlist_node_t *wlist);
// show wordlist
void wlist_show (struct wlist_t *wlist);

#ifdef __cplusplus
}
#endif

#endif
