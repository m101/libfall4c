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

#include <stdio.h>
#include <stdlib.h>

#include "data/queue.h"

// push data on the queue
struct queue_t *queue_push (struct queue_t **p, void *data)
{
    struct queue_element_t *elt;

    // pointer check
    if (!p || !data) {
        fprintf (stderr, "error: queue_push(): Bad parameter(s)\n");
        return NULL;
    }

    elt = calloc (1, sizeof(*elt));
    if (!elt) {
        fprintf (stderr, "error: queue_push(): Failed allocating node\n");
        return NULL;
    }

    // was queue allocated?
    if (!*p) {
        *p = calloc (1, sizeof(**p));
        if (!*p) {
            fprintf (stderr, "error: queue_push(): Failed allocating root node\n");
            return NULL;
        }
        // update base pointer
        (*p)->front = elt;
    }

    // add data
    elt->data = data;
    // add element
    elt->prev = (*p)->back;
    if ((*p)->back)
        (*p)->back->next = elt;
    // update queue pointer
    (*p)->back = elt;
    // update counter
    (*p)->size++;

    return *p;
}

// get last data added to the queue
void *queue_pop (struct queue_t **p)
{
    void *data;
    struct queue_element_t *elt = NULL;

    // pointers check
    if (!p)
        return NULL;
    if (!(*p))
        return NULL;

    // if no node elements
    // then destruct it
    if ( (*p)->front == NULL || (*p)->size <= 0 ) {
        free (*p), *p = NULL;
        return NULL;
    }

    // since we are popping front
    // we ought to unref back if it's the same
    if ((*p)->front == (*p)->back)
        (*p)->back = NULL;

    elt = (*p)->front;
    // update top element of the queue
    (*p)->front = (*p)->front->next;
    // remove it from the queue
    // queue front follower become the queue front
    if ((*p)->front)
        (*p)->front->prev = NULL;
    // get correct count
    (*p)->size--;
    // get data
    data = elt->data;

    // destroy element
    free (elt);

    if ( (*p)->front == NULL || (*p)->back == NULL )
        free (*p), *p = NULL;

    return data;
}

// destroy a queue
void queue_destroy (struct queue_t **queue, void (*fct_destroy)(void **data))
{
    struct queue_element_t *elt, *next;
    // pointers check
    if (!queue)
        return;
    if (!*queue)
        return;

    // traverse queue and destroy each element
    elt = (*queue)->front;
    while (elt) {
        next = elt->next;
        if (fct_destroy)
            fct_destroy (&(elt->data));
        free (elt);
        elt = next;
    }

    // destroy queue
    free (*queue);
    *queue = NULL;
}

