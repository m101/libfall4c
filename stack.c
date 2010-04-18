/***************************************************************************
 *            piles.c
 *
 *  Wed Dec 17 12:06:10 2008
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

#include <stdlib.h>
#include <stdio.h>

#include "piles.h"

// Empilement
struct t_stack *push (struct t_stack **p, struct t_stack *elt)
{
	if (!p)
		return NULL;
	if (!(*p))
		*p = alloc_stack_node();
	
	elt->prev = *p;
	(*p)->next = elt;
	*p = elt;
	
	printf("pushed : '%s'\n", elt->data);
	
	return elt;
}

// Depilement
struct t_stack *pop (struct t_stack **p)
{
	struct t_stack *elt = NULL;
	
	if (!p)
		return NULL;
	if (!(*p))
		return NULL;
	
	elt = (*p);
	*p = (*p)->prev;
	elt->prev = NULL;
	
	printf("popped : '%s'\n", elt->data);
	
	return elt;
}

// Allouer stack
struct t_stack *alloc_stack_node (void)
{
	struct t_stack elt = {0};
	struct t_stack *node = NULL;
	
	node = malloc(sizeof(struct t_stack));
	*node = elt;
	
	return node;
}