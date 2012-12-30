#include <stdlib.h>
#include <stdio.h>

#include "data/cache.h"
#include "data/list.h"

// init cache
struct cache_t *cache_init (struct cache_t *cache, int n_objects)
{
    if (!cache || n_objects <= 0)
        return NULL;

    cache->objects = calloc(n_objects, sizeof(*cache->objects));
    if (!cache->objects) {
        free(cache);
        return NULL;
    }

    cache->capacity = n_objects;

    return cache;
}

// allocate cache
struct cache_t *cache_new (int n_objects)
{
    struct cache_t *cache;

    if (n_objects <= 0)
        return NULL;

    cache = calloc(1, sizeof(*cache));
    if (!cache)
        return NULL;

    return cache_init(cache, n_objects);
}

// allocate gadget cache by copy
struct cache_t *cache_new_copy (struct cache_t *cache) 
{
    struct cache_t *copy, *res;

    // allocate copy
    copy = cache_new(cache_get_capacity(cache));
    // make copy
    res = cache_copy(copy, cache);
    if (res == NULL)
        cache_destroy(&copy, NULL);

    return copy;
}

// destroy cache
void cache_destroy (struct cache_t **cache, void (*destroy)(void **data))
{
    // check parameters
    if (!cache || !*cache)
        return;

    // destroy object cache
    cache_purge(*cache, destroy);
    free((*cache)->objects);
    free(*cache);
    *cache = NULL;
}

// purge cache: "free" and re-init the cache
int cache_purge (struct cache_t *cache, void (*destroy)(void **data))
{
    int idx_object;

    // check parameters
    if (!cache)
        return -ERR_CACHE_UNDEFINED;

    // reinit whole cache
    for (idx_object = 0; idx_object < cache_get_capacity(cache); idx_object++) {
        if (destroy)
            destroy(&(cache->objects[idx_object]));
        cache_set(cache, idx_object, NULL);
    }

    // reset the used counter
    cache->used = 0;

    return CACHE_OK;
}

// purge cache: just "free" by resetting the used counter
int cache_reset (struct cache_t *cache)
{
    // check parameters
    if (!cache)
        return -ERR_CACHE_UNDEFINED;

    // just reset the used counter :) (we overwrite over it)
    cache->used = 0;

    return CACHE_OK;
}

// gadget cache copy (both cache must have the same size)
struct cache_t *cache_copy (struct cache_t *dest, struct cache_t *src)
{
    int idx_cache;
    int dest_capacity, src_capacity;
    void *copied, *cached;

    // check parameters
    if ((!dest || !src) || (src == dest)) {
        fprintf(stderr, "error: cache_copy(): Bad parameters\n");
        return NULL;
    }

    // cache must be of same sizes
    dest_capacity = cache_get_capacity(dest);
    src_capacity = cache_get_capacity(src);
    if (dest_capacity != src_capacity) {
        fprintf(stderr, "error: cache_copy(): dest and src are not of the same size\n");
        return NULL;
    }

    // copy cache
    for (idx_cache = 0; idx_cache < cache_get_size(src); idx_cache++) {
        // copying
        cached = cache_get (src, idx_cache);
        cache_set (dest, idx_cache, copied);
    }
    dest->used = src->used;

    return dest;
}

// add gadget to cache
int cache_add (struct cache_t *cache, void *object)
{
    // check parameters
    if (!cache || !object) {
        printf("cache_add(): cache does not exist\n");
        return -ERR_CACHE_UNDEFINED;
    }

    // re-adjust used if inferior or equal to 0
    cache->used = (cache->used <= 0) ? 0 : cache->used;

    // if cache full
    if (cache->used >= cache->capacity) {
        // re-adjust used so it never goes above capacity
        cache->used = (cache->used > cache->capacity) ? cache->capacity : cache->used;
        return -ERR_CACHE_FULL;
    }

    // add to cache
    if (cache_set(cache, cache->used, object) != NULL)
        cache->used++;

    return CACHE_OK;
}

// get element at index
void *cache_get (struct cache_t *cache, int index)
{
    if (!cache)
        return NULL;

    if (index < 0 || index >= cache->used || index >= cache->capacity)
        return NULL;

    return cache->objects[index];
}

// set element at index
void *cache_set (struct cache_t *cache, int index, void *object)
{
    if (!cache)
        return NULL;

    if (index < 0 || index >= cache->capacity)
        return NULL;

    cache->objects[index] = object;

    return object;
}

// zero entirely the cache
int cache_zero (struct cache_t *cache)
{
    int idx_object;

    // check parameters
    if (!cache)
        return -ERR_CACHE_UNDEFINED;

    // reset cache (heavy one)
    for (idx_object = 0; idx_object < cache_get_capacity(cache); idx_object++)
        cache_set(cache, idx_object, NULL);

    // reset used counter
    cache->used = 0;

    return CACHE_OK;
}

// get number of elements in cache
int cache_get_size (struct cache_t *cache)
{
    // bye
    if (!cache) {
        fprintf(stderr, "cache_get_size(): cache is NULL\n");
        return -ERR_CACHE_UNDEFINED;
    }

    if (cache->used < 0)
        cache->used = 0;
    if (cache->used > cache->capacity)
        return cache->capacity;

    return cache->used;
}

// set number of elements in cache
int cache_set_size (struct cache_t *cache, int size)
{
    // bye
    if (!cache) {
        fprintf(stderr, "cache_get_size(): cache is NULL\n");
        return -ERR_CACHE_UNDEFINED;
    }

    cache->used = size;
    if (size <= 0)
        cache->used = 0;
    if (size > cache->capacity)
        cache->used = cache->capacity;

    return cache->used;
}

// get max elements that can be stored in cache
int cache_get_capacity (struct cache_t *cache)
{
    // bye
    if (!cache) {
        fprintf(stderr, "cache_get_capacity(): cache is NULL\n");
        return -ERR_CACHE_UNDEFINED;
    }

    return cache->capacity;
}

