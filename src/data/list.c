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

#include "list.h"

// default constructor for list
struct list* list_new (struct list_simple **list) {
    if (!list)
        return NULL;

    *list = calloc(1, sizeof(**list));

    return *list;
}

// default destructor
int list_destroy (struct list_simple **list, void (*destroy_data)(void *)) {
    struct list_node *node;
    struct list_node *head, *tail;

    if (!list || !*list)
        return -1;

    if (!destroy_data)
        destroy_data = free;

    head = (*list)->head;

    // we traverse the linked list to destroy it
    for (node = head; node != NULL; node = node->next) {
        free(node->prev);
        if (node->data)
            destroy_data(node->data);
        tail = node;
    }

    free(tail);
    free(*list);

    return 0;
}

// default constructor for node
struct list_node* list_node_new (struct list_node **node) {
    *node = calloc (1, sizeof(**node));

    return *node;
}

// default destructor for node
int list_node_destroy (struct list_node **node, void (*destroy_data)(void *)) {
    struct list_node *prev, *next;

    if (!node || !*node)
        return -1;

    prev = (*node)->prev;
    next = (*node)->next;
    if (prev)
        (*next)->prev->next = next;
    if (next)
        (*next)->next->prev = prev;

    if (!destroy_data)
        destroy_data = free;
    if ((*node)->data)
        destroy_data((*node)->data);
    free(*node);
    *node = NULL;

    return 0;
}

// append a node to existing list
int list_append_node (struct list_simple **list, struct list_node *node) {
    if (!list || !node)
        return -1;
    if (!*list)
        list_new(list);

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
int list_append_data (struct list_simple **list, void *data) {
    int rc;
    struct list_node *node;

    node = list_node_new (NULL);
    node->data = data;
    rc = list_append_node (list, node);

    if (rc)
        list_node_destroy (&node, NULL);

    return rc;
}

// prepend a node to existing list
int list_prepend_node (struct list_simple **list, struct list_node *node) {
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);

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
list_prepend_data (struct list_simple **list, void *data) {
    int rc;
    struct list_node *node;

    node = list_node_new (NULL);
    node->data = data;
    rc = list_prepend_node(list, node);

    if (rc)
        list_node_destroy (&node, NULL);

    return 0;
}

// insert a node at specified position
int list_insert_node (struct list_simple **list, struct list_node *node, size_t pos) {
    struct list_node *pNode;
    struct list_node *head;
    size_t i;

    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);
    if ((*list)->size < pos)
        return -1;

    head = (*list)->head;

    // we traverse the linked list
    for (pNode = head, i = 0; pNode != NULL; pNode = pNode->next, i++) {
        if (i == pos) {
            if (!pNode->next)
                list_append_node(list, node);
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
int list_insert_data (struct list_simple **list, void *data, size_t pos) {
    struct list_node *node;
    int failed;

    // check list and node validity
    if (!list || !data)
        return -1;
    if (!(*list))
        list_new(list);

    // we allocate a new node
    list_node_new(&node);
    // we insert data
    node->data = data;

    // we insert the node in the list
    failed = list_insert_node(list, node, pos);
    // if successful
    if (!failed)
        return 0;
    // else we failed
    else {
        list_node_destroy(&node, NULL);
        return -1;
    }
}

// remove current node
int list_remove_node (struct list_simple *list, struct list_node **node) {
    if (!list || !node || !*node)
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

// remove a node at specified position
int list_remove_node_at_pos (struct list_simple **list, size_t pos) {
    struct list_node *node;
    size_t i;

    // check pointer validity
    if (!list || !pos || !*list)
        return -1;

    // position inexistent
    if ((*list)->size < pos)
        return -1;

    for (node = (*list)->head, i = 0; node != NULL; node = node->next, i++) {
        if (i == pos) {
            list_remove_node(*list, &node);
            return 0;
        }
    }

    // we didn't remove any node
    return -1;
}

// get data at specified node position
void* list_get_data_at_pos (struct list_simple **list, size_t pos) {
    struct list_node *node;
    size_t i;

    // check list and node validity
    if (!list)
        return NULL;
    if (!(*list))
        list_new(list);

    // we check if position specified is in range
    if (pos > (*list)->size)
        return NULL;

    // we traverse the linked list
    for (node = (*list)->head, i = 0; node != NULL; node = node->next, i++) {
        // if we found the specified node
        // then we return the data
        if (i == pos)
            return node->data;
    }

    // failed to get the data at the specified location
    return NULL;
}

struct list_node* list_has_node (struct list_simple **list, struct list_node *node) {
    struct list_node *iter = NULL;

    for (iter = list->head; iter != node && iter != NULL; iter = iter->next);

    return iter;
}

struct list_node* list_has_data (struct list_simple **list, void *data, int (*compare)(void *data1, void* data2)) {
    struct list_node *node;

    for (node = list->head; node != NULL; node = node->next) {
        if (compare(node->data, data) == 0)
            return node;
    }

    return NULL;
}

// show all elements
void list_show_all (struct list_simple *list) {
    size_t i;
    struct list_node *node;

    // check list and node validity
    if (!list)
        return;

    // we traverse link list and show all node value
    for (node = list->head, i = 0; node != NULL; node = node->next, i++)
        printf("node %u : %p\n", i, node->data);
}

