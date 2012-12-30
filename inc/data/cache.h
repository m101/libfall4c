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
