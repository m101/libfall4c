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

#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

// push data on the stack
struct stack_t *stack_push (struct t_stack **p, void *data)
{
    struct stack_element_t *elt;

    // pointer check
	if (!p)
		return NULL;
	
    elt = stack_element_new();
    // was stack allocated?
	if (!(*p))
    {
		*p = stack_new();
        // update base pointer
        (*p)->base = elt;
    }
    // add data
    elt->data = data;
    // add element
	elt->prev = (*p)->top;
    if ((*p)->top)
    	(*p)->top->next = elt;
    // update stack pointer
    (*p)->top = elt;
    // update counter
    (*p)->szStack++;
	
	return elt;
}

// get last data added to the stack
void* stack_pop (struct stack_t **p)
{
    void *data;
	struct stack_element_t *elt = NULL;
	
    // pointers check
	if (!p)
		return NULL;
	if (!(*p))
		return NULL;
	
    // if no node elements
    // then destruct it
    if ( (*p)->top == NULL )
    {
        free (*p), *p = NULL;
        return NULL;
    }

    // get element at the top of the stack
    elt = (*p)->top;
    // remove it from the stack
    // stack top follower become the stack top
    if (elt->prev)
        elt->prev->next = NULL;
    // update top element of the stack
    (*p)->top = (*p)->top->prev;
    // node prev and next
    elt->prev = NULL;
    elt->next = NULL;
    // get correct count
    (*p)->szStack--;
    // get data
    data = elt->data;

    // destroy element
    free (elt);

    return data;
}

// allocate stack element
struct stack_element_t *stack_element_new(void)
{
    struct stack_element_t elt = {0};
    struct stack_element_t *node = NULL;

    node = malloc(sizeof(elt));
    *node = elt;

    return node;
}

// allocate a new stack
struct stack_t *stack_new(void)
{
    struct stack_t elt = {0};
    struct stack_t *node = NULL;

    node = malloc(sizeof(elt));
    *node = elt;

    return node;
}

// destroy a stack
void stack_destroy (struct stack_t **stack)
{
    struct stack_element_t *elt, *next;
    // pointers check
    if (!stack)
        return;
    if (!(*stack))
        return;

    // traverse stack and destroy each element
    elt = (*stack)->base;
    while (elt)
    {
        next = elt->next;
        free (elt);
        elt = next;
    }

    // destroy stack
    free (*stack);
    *stack = NULL;
}

