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

#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

#include "data_ops.h"

struct list_node {
    // doubly linked list
    struct list_node *next, *prev;
    // data
    void *data;
    // size of data
    long size;
};

struct list_simple {
    struct list_node *head, *tail;
    size_t size;

    // methods
    struct data_ops *dops;
};

#define list_simple_set_callback(list, name, callback) if (list->dops) list->dops->name = callback

#define list_simple_get_size(list) (list ? (list)->size : 0)
#define list_simple_begin(list) (list ? (list)->head : NULL)
#define list_simple_end(list) (list ? (list)->tail : NULL)

#define list_simple_for_each(list, it, _data)            if (list) for (it = (list)->head; it && (_data = it->data); it = it->next)
#define list_simple_for_each_backward(list, it, _data)   if (list) for (it = (list)->tail; it && (_data = it->data); it = it->prev)

    // default constructor for list
    struct list_simple *list_new (void);
    // free list without destructing objects
    int list_delete (struct list_simple **list);
    // default destructor
    int list_destroy (struct list_simple **list);
    int list_count_nodes (struct list_simple *list);
    // append data to existing struct list
    int list_append_data (struct list_simple **list, void *data);
    // prepend data to existing list
    int list_prepend_data (struct list_simple **list, void *data);
    // insert data at specified position
    int list_insert_data (struct list_simple **list, void *data, size_t pos);
    // remove data from existing list
    int list_remove_data (struct list_simple *list, void *data);
    // get data at specified node position
    void *list_get_data_at_pos (struct list_simple *list, size_t pos);
    // show all elements of the list
    void list_show_all (struct list_simple *list);
    struct list_simple *list_has_data (struct list_simple *list, void *data);

    // merge two list in one, no dupes checks, return new list
    struct list_simple *list_append_list (struct list_simple **list1, struct list_simple **list2);

    // node functions
    // remove current node
    int _list_remove_node (struct list_simple *list, struct list_node **node);

#ifdef __cplusplus
}
#endif

#endif /* _LIST_H_ */
