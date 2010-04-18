/***************************************************************************
 *            piles.h
 *
 *  Wed Dec 17 12:07:15 2008
 *  Copyright  2008  kurapix
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

typedef struct t_stack
{
	char *data;
	size_t size;
	struct t_stack *next, *prev;
} t_stack;

// Empilement
struct t_stack *push (struct t_stack **p, struct t_stack *elt);
// Depilement
struct t_stack *pop (struct t_stack **p);
// Allouer stack
struct t_stack *alloc_stack_node (void);

#endif
