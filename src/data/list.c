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

#include "data/list.h"

struct list_node* _list_has_node (struct list_simple *list, struct list_node *node);
// default constructor for node
struct list_node* _list_node_new (void *data);
// default destructor for node
int _list_node_destroy (struct list_node **node, void (*destroy_data)(void *));
// append a node to existing list
int _list_append_node (struct list_simple **list, struct list_node *node);
// prepend a node to existing list
int _list_prepend_node (struct list_simple **list, struct list_node *node);
// insert a node at specified position
int _list_insert_node (struct list_simple **list, struct list_node *node, size_t pos);
// remove current node
int _list_remove_node (struct list_simple *list, struct list_node **node);
// remove a node at specified position
int _list_remove_node_at_pos (struct list_simple **list, size_t pos);

// default constructor for list
struct list_simple* list_new (void) 
{
    return calloc(1, sizeof(struct list_simple));
}

// default destructor
int list_destroy (struct list_simple **list, void (*destroy_data)(void *)) 
{
    struct list_node *node, *next;

    if (!list ||  !*list)
        return -1;

    // we traverse the linked list to destroy it
    for (node = list_begin(*list); node != NULL; ) {
        next = node->next;
        _list_node_destroy(&node, destroy_data);
        node = next;
    }

    free(*list);
    *list = NULL;

    return 0;
}

int list_count_nodes(struct list_simple *list)
{
    struct list_node *node;
    int count;

    if (!list)
        return -1;

    for (node = list_begin(list), count = 0; node != NULL; node = node->next, count++);

    return count;
}

int list_merge(struct list_simple *list1, struct list_simple *list2)
{
    if (!list1 || !list2)
        return -1;

    _list_append_node(&list1, list_begin(list2));
    list1->size = list_count_nodes(list1);

    return 0;
}

int list_check(struct list_simple *list)
{
    struct list_node *node;
    int count;

    if (!list)
        return -1;

    count = list_count_nodes(list);
    if (count != list->size)
        return -2;

    return 0;
}

// default constructor for node
struct list_node* _list_node_new (void *data)
{
    struct list_node *node = calloc (1, sizeof(*node));

    node->data = data;

    return node;
}

// default destructor for node
int _list_node_destroy (struct list_node **node, void (*destroy_data)(void *))
{
    if (!node || !*node)
        return -1;

    // unlink
    if ((*node)->prev)
        (*node)->prev->next = (*node)->next;
    if ((*node)->next)
        (*node)->next->prev = (*node)->prev;

    if ((*node)->data && destroy_data) {
        destroy_data((*node)->data);
        (*node)->data = NULL;
    }
    free(*node);
    *node = NULL;

    return 0;
}

// append a node to existing list
int _list_append_node (struct list_simple **list, struct list_node *node)
{
    if (!list || !node)
        return -1;
    if (!*list)
        *list = list_new();

    if (!(*list)->head)
        (*list)->head = node;
    if ((*list)->tail)
        (*list)->tail->next = node;

    node->prev = (*list)->tail;
    node->next = NULL;
    (*list)->tail = node;
    (*list)->size++;

    return 0;
}

// append data to existing list
int list_append_data (struct list_simple **list, void *data)
{
    int rc;
    struct list_node *node;

    node = _list_node_new (data);
    rc = _list_append_node (list, node);

    if (rc)
        _list_node_destroy (&node, NULL);

    return rc;
}

// prepend a node to existing list
int _list_prepend_node (struct list_simple **list, struct list_node *node)
{
    if (!list || !node)
        return -1;
    if (!*list)
        *list = list_new();

    if ((*list)->head)
        (*list)->head->prev = node;
    if (!(*list)->tail)
        (*list)->tail = node;

    node->prev = NULL;
    node->next = (*list)->head;
    (*list)->head = node;
    (*list)->size++;

    return 0;
}

// prepend data to existing list
int list_prepend_data (struct list_simple **list, void *data)
{
    int rc;
    struct list_node *node;

    node = _list_node_new (data);
    rc = _list_prepend_node(list, node);

    if (rc)
        _list_node_destroy (&node, NULL);

    return 0;
}

// insert a node at specified position
int _list_insert_node (struct list_simple **list, struct list_node *node, size_t pos)
{
    struct list_node *pNode;
    struct list_node *head;
    size_t i;

    if (!list || !node)
        return -1;
    if (!*list)
        *list = list_new();
    if ((*list)->size < pos)
        return -1;

    head = (*list)->head;

    // we traverse the linked list
    for (pNode = head, i = 0; pNode != NULL; pNode = pNode->next, i++) {
        if (i == pos) {
            if (!pNode->next)
                _list_append_node(list, node);
            else {
                node->next = pNode;
                node->prev = pNode->prev;

                if (node->prev)
                    node->prev->next = node;
                else
                    (*list)->head = node;

                pNode->prev = node;
            }

            (*list)->size++;

            return 0;
        }
    }

    printf("failed insertion tat\n");
    // failed to insert node
    return -1;
}

// insert data at specified position
int list_insert_data (struct list_simple **list, void *data, size_t pos)
{
    struct list_node *node;
    int failed;

    // check list and node validity
    if (!list || !data)
        return -1;
    if (!*list)
        *list = list_new();

    // we allocate a new node
    node = _list_node_new(NULL);
    // we insert data
    node->data = data;

    // we insert the node in the list
    failed = _list_insert_node(list, node, pos);
    // if successful
    if (!failed)
        return 0;
    // else we failed
    else {
        _list_node_destroy(&node, NULL);
        return -1;
    }
}

// remove current node
int _list_remove_node (struct list_simple *list, struct list_node **node)
{
    if (!list || !node || !*node)
        return -1;

    if ((*node)->next)
        (*node)->next->prev = (*node)->prev;
    if ((*node)->prev)
        (*node)->prev->next = (*node)->next;

    // we remove the actual node
    free(*node);
    *node = NULL;
    free(node);
    list->size--;

    return 0;
}

// remove data from existing list
int list_remove_data (struct list_simple *list, void *data)
{
    int rc;
    struct list_node *iter;

    list_for_each (list, iter, data)
        if (iter->data == data)
            _list_remove_node (list, &iter);

    return rc;
}

// remove a node at specified position
int _list_remove_node_at_pos (struct list_simple **list, size_t pos)
{
    struct list_node *node;
    size_t i;

    // check pointer validity
    if (!list || !pos || !*list)
        return -1;

    // position inexistent
    if ((*list)->size < pos)
        return -1;

    for (node = (*list)->head, i = 0; node != NULL; node = node->next, i++)
    {
        if (i == pos) {
            _list_remove_node(*list, &node);
            return 0;
        }
    }

    // we didn't remove any node
    return -1;
}

// get data at specified node position
void* list_get_data_at_pos (struct list_simple *list, size_t pos)
{
    struct list_node *iter;
    size_t idx_iter;
    void *data;

    // check list and node validity
    if (!list) {
        fprintf (stderr, "error: list_get_data_at_pos(): list not initialized\n");
        return NULL;
    }

    // we check if position specified is in range
    if (pos >= list->size) {
        fprintf (stderr, "error: list_get_data_at_pos(): Bad pos\n");
        return NULL;
    }

    // we traverse the linked list
    idx_iter = 0;
    list_for_each (list, iter, data) {
        // if we found the specified node
        // then we return the data
        if (idx_iter == pos)
            return data;
        ++idx_iter;
    }

    // failed to get the data at the specified location
    fprintf (stderr, "error: list_get_data_at_pos(): Data was not found\n");
    return NULL;
}

struct list_node* _list_has_node (struct list_simple *list, struct list_node *node)
{
    struct list_node *iter = NULL;

    if (!list)
        return NULL;

    for (iter = list->head; iter != node && iter != NULL; iter = iter->next);

    return iter;
}

struct list_simple *list_has_data (struct list_simple *list, void *data, int (*compare)(void *data1, void* data2))
{
    struct list_node *node;

    if (!list)
        return NULL;

    for (node = list->head; node != NULL; node = node->next) {
        if (compare(node->data, data) == 0)
            return list;
    }

    return NULL;
}

// show all elements
void list_show_all (struct list_simple *list)
{
    size_t i;
    struct list_node *node;

    // check list and node validity
    if (!list)
        return;

    // we traverse link list and show all node value
    for (node = list->head, i = 0; node != NULL; node = node->next, i++)
        printf("node %u : %p\n", i, node->data);
}

