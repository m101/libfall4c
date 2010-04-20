/***************************************************************************
 *            stack.h
 *
 *  Wed Dec 17 12:07:15 2008
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

#ifndef _STACK_H
#define _STACK_H

// stack
struct stack_t
{
    // elements of the stack
    struct stack_element_t *elements;
    // stack pointer
    struct stack_element_t *top;
    // base pointer
    struct stack_element_t *base;
    // number of elements in the stack
    size_t szStack;
};

// stack element
struct stack_element_t
{
    // data stored
    char *data;
    // size of data
    size_t size;
    // next and previous element
    struct t_stack *next, *prev;
};

// push data on the stack
struct stack_t* push (struct stack_t **p, void *data);
// get last data added to the stack
void* pop (struct stack_t **p);
// allocate a new stack
struct stack_new (void);
// destroy a stack
void stack_destroy (struct stack_t **stack);

#endif
