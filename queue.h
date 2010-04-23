#ifndef _QUEUE_H_
#define _QUEUE_H_

// queue
struct queue_t
{
    // elements of the queue
    struct queue_element_t *elements;
    // front of the queue : first element
    struct queue_element_t *front;
    // back of the queue : last element
    struct queue_element_t *back;
    // number of elements in the queue
    size_t szQueue;
};

// queue element
struct queue_element_t
{
    // data stored
    char *data;
    // size of data
    size_t size;
    // next and previous element
    struct queue_element_t *next, *prev;
};

// push data on the queue
struct queue_t* queue_push (struct queue_t **p, void *data);
// get last data added to the queue
void* queue_pop (struct queue_t **p);
// allocate a new queue
struct queue_new (void);
// destroy a queue
void queue_destroy (struct queue_t **queue);

#endif
