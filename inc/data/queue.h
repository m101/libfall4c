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

#ifndef _QUEUE_H_
#define _QUEUE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#include "data_ops.h"

#define queue_set_callback(queue, name, callback) if (queue->dops) queue->dops->name = callback
#define queue_get_size(queue) (queue ? (queue)->size : -1)

// queue
struct queue_t
{
    // front of the queue : first element
    struct queue_element_t *front;
    // back of the queue : last element
    struct queue_element_t *back;
    // number of elements in the queue
    long size;

    // methods
    struct data_ops *dops;
};

// queue element
struct queue_element_t
{
    // next and previous element
    struct queue_element_t *next, *prev;
    // data stored
    void *data;
    // size of data
    long size;
};

// push data on the queue
struct queue_t* queue_push (struct queue_t **p, void *data);
// get last data added to the queue
void *queue_pop (struct queue_t **p);
// destroy a queue
void queue_destroy (struct queue_t **queue);

#ifdef __cplusplus
}
#endif

#endif
