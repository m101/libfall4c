/***************************************************************************
 *            stack.c
 *
 *  Wed Dec 17 12:06:10 2008
 *  Copyright  2010  kurapix
 *  <kurapix@<host>>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

// push data on the stack
struct stack_t *push (struct t_stack **p, void *data)
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
void* pop (struct stack_t **p)
{
    void *data;
	struct stack_element_t *elt = NULL;
	
    // pointers check
	if (!p)
		return NULL;
	if (!(*p))
		return NULL;
	
    // get element at the top of the stack
	elt = (*p)->top;
    // remove it from the stack
    if (elt)
    {
        // stack top
        if (elt->prev)
            elt->prev->next = NULL;
        // node prev
        elt->prev = NULL;
        // get correct count
        (*p)->szStack--;
    }
    // update top element of the stack
	(*p)->top = (*p)->prev;
    // node elements? then destruct it
    if ( (*p)->top == NULL )
        free (*p), *p = NULL;

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

