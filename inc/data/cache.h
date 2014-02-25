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

#ifndef _CACHE_H_
#define _CACHE_H_

// generic
#define CACHE_OK                 0

// about the cache structure
enum {
    ERR_CACHE_UNDEFINED = 1,
    ERR_CACHE_FULL
};

struct cache_t {
    // number of gadgets in cache
    int used;
    // cache size
    int capacity;
    // stored objects in cache
    void **objects;
};

#define cache_for_each(cache, iter, data)   for (iter = 0; iter < cache_get_size(cache); data = cache_get(cache, iter), iter++)

/* cache structure */
// init cache
struct cache_t *cache_init (struct cache_t *cache, int n_objects);
// allocate cache
struct cache_t* cache_new(int n_objects);
// allocate cache by copy
struct cache_t* cache_new_copy(struct cache_t *cache);
// destroy cache
void cache_destroy(struct cache_t **cache, void (*destroy)(void **data));
// purge cache: "free" and re-init the cache
int cache_purge(struct cache_t *cache, void (*destroy)(void **data));
// purge cache: just "free" by resetting the used counter
int cache_reset(struct cache_t *cache);
// cache copy (both cache must have the same size)
struct cache_t *cache_copy(struct cache_t *dest, struct cache_t *src);
// add object to cache
int cache_add (struct cache_t *cache, void *object);
// get element at index
void *cache_get(struct cache_t *cache, int index);
// set element at index
void *cache_set(struct cache_t *cache, int index, void *object);
// zero entirely the cache
int cache_zero(struct cache_t *cache);
// get number of elements in cache
int cache_get_size(struct cache_t *cache);
// set number of elements in cache
int cache_set_size (struct cache_t *cache, int size);
// get max elements that can be stored in cache
int cache_get_capacity(struct cache_t *cache);

#endif /* _CACHE_H_ */
