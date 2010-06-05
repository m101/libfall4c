#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

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

struct list_t {
    struct list_node_t *head, *tail;
    size_t szList;
};

struct list_node_t {
    // doubly linked list
    struct list_node_t *next, *prev;
    // data
    void *data;
};

    // default constructor for list
    struct list_t* list_new (struct list_t **list);
    // default destructor
    int list_destroy (struct list_t **list, void (*destroy_data)(void *));
    // default constructor for node
    struct list_node_t* list_node_new (struct list_node_t **node);
    // default destructor for node
    int list_node_destroy (struct list_node_t **node, void (*destroy_data)(void *));
    // append a node to existing list
    int list_append_node (struct list_t **list, struct list_t *node);
    // append data to existing struct list_t
    int list_append_data (struct list_t **list, void *data);
    // prepend a node to existing list
    int list_prepend_node (struct list_t **list, struct list_t *node);
    // prepend data to existing list
    int list_prepend_data (struct list_t **list, void *data);
    // insert a node at specified position
    int list_insert_node (struct list_t **list, struct list_t *node, size_t pos);
    // insert data at specified position
    int list_insert_data (struct list_t **list, void *data, size_t pos);
    // remove current node
    int list_remove_node (struct list_t *list, struct list_node_t **node);
    // remove a node at specified position
    int list_remove_node_at_pos (struct list_t **list, size_t pos);
    // get data at specified node position
    void* list_get_data_at_pos (struct list_t **list, size_t pos);

    // show all elements of the list
    void list_show_all (struct list_t *list);
    // get list size
    size_t list_get_size (struct list_t *list);
    // return head of list
    struct list_t* list_begin (struct list_t *list);
    // return tail of list
    struct list_t* list_end (struct list_t *list);

#ifdef __cplusplus
}
#endif

#endif /* _LIST_H_ */
