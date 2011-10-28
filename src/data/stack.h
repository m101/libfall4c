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

#ifndef _STACK_H
#define _STACK_H

// stack
struct stack_t {
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
struct stack_element_t {
    // data stored
    char *data;
    // size of data
    size_t size;
    // next and previous element
    struct stack_element_t *next, *prev;
};

// push data on the stack
struct stack_t* stack_push (struct stack_t **p, void *data);
// get last data added to the stack
void* stack_pop (struct stack_t **p);
// allocate a new stack
struct stack_t* stack_new (void);
// destroy a stack
void stack_destroy (struct stack_t **stack);

#endif
