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

struct list_node {
    // doubly linked list
    struct list_node *next, *prev;
    // data
    void *data;
};

struct list_simple {
    struct list_node *head, *tail;
    size_t size;
};

#define list_get_size(list) (list ? (list)->size : -1)
#define list_begin(list) (list ? (list)->head : NULL)
#define list_end(list) (list ? (list)->tail : NULL)

#define list_for_each(list, it, _data)   if (list) for (it = list->head, _data = it->data; it != NULL; it = it->next, _data = (it ? it->data : NULL))

    // default constructor for list
    struct list_simple *list_new (void);
    // default destructor
    int list_destroy (struct list_simple **list, void (*destroy_data)(void *));
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
    struct list_simple *list_has_data (struct list_simple *list, void *data, int (*compare)(void *data1, void* data2));

#ifdef __cplusplus
}
#endif

#endif /* _LIST_H_ */
