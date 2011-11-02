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

#include "queue.h"

// INTERNAL
// allocate queue element
struct queue_element_t *queue_element_new(void)
{
    struct queue_element_t elt = {0};
    struct queue_element_t *node = NULL;

    node = malloc(sizeof(elt));
    *node = elt;

    return node;
}



// PUBLIC
// push data on the queue
struct queue_t* queue_push (struct queue_t **p, void *data)
{
    struct queue_element_t *elt;

    // pointer check
	if (!p)
		return NULL;
	
    // allocate element
    elt = queue_element_new();
    // was queue allocated?
	if (!(*p))
    {
		*p = queue_new(); 
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
void* queue_pop (struct queue_t **p)
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
    if ( (*p)->front == NULL )
    {
        free (*p), *p = NULL;
        return NULL;
    }

    elt = (*p)->front;
    // remove it from the queue
    // queue front follower become the queue front
    if (elt->next)
        elt->next->prev = NULL;
    // update top element of the queue
    (*p)->front = (*p)->front->next;
    // get element at the front of the queue
    // node prev and next
    elt->prev = NULL;
    elt->next = NULL;
    // get correct count
    (*p)->size--;
    // get data
    data = elt->data;

    // destroy element
    free (elt);

    return data;
}

// allocate a new queue
struct queue_t *queue_new(void)
{
    struct queue_t elt = {0};
    struct queue_t *node = NULL;

    node = malloc(sizeof(elt));
    *node = elt;

    return node;
}

// destroy a queue
void queue_destroy (struct queue_t **queue)
{
    struct queue_element_t *elt, *next;
    // pointers check
    if (!queue)
        return;
    if (!(*queue))
        return;

    // traverse queue and destroy each element
    elt = (*queue)->front;
    while (elt)
    {
        next = elt->next;
        free (elt);
        elt = next;
    }

    // destroy queue
    free (*queue);
    *queue = NULL;
}

