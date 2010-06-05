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
struct list_t* list_new (struct list_t **list) {
    struct list_t *pList;

    pList = calloc(1, sizeof(**list));
    // check list validity
    if (list)
        *list = pList;

    return pList;
}

// default destructor
int list_destroy (struct list_t **list, void (*destroy_data)(void *)) {
    // node for traversing linked list
    struct list_node_t *node;
    // head and tail to ease reading
    struct list_node_t *head, *tail;

    // check list validity
    if (!list)
        return -1;

    if (!destroy_data)
        destroy_data = free;

    head = (*list)->head;
    tail = (*list)->tail;
    // we destroy data management unit
    free((*list));
    (*list) = NULL;

    // we traverse the linked list to destroy it
    for (node = head; node != NULL; ) {
        node = node->next;

        // we destroy the current node
        if (node) {
            // we destroy node
            free(node->prev);
            if (node->data)
                destroy_data(node->data);
            // we ensure m_prev value in case of double frees
            node->prev = NULL;
        }
    }
    
    return 0;
}

// default constructor for node
struct list_node_t* list_node_new (struct list_node_t **node) {
    struct list_node_t *pNode;

    pNode = calloc (1, sizeof(**node));
    if (node)
        *node = pNode;

    return pNode;
}

// default destructor for node
int list_node_destroy (struct list_node_t **node, void (*destroy_data)(void *)) {
    if (!node)
        return -1;
    if (!*node)

    if (!destroy_data)
        destroy_data = free;

    destroy_data((*node)->data);
    free(*node);
    *node = NULL;

    return 0;
}

// append a node to existing list
int list_append_node (struct list_t **list, struct list_node_t *node) {
    // check list and node validity
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);

    // if not defined
    // we update head pointer
    if (!(*list)->head)
        (*list)->head = node;
    // we end the list
    if ((*list)->tail)
        (*list)->tail->next = node;

    // we link the node to the list
    node->prev = (*list)->tail;
    node->next = NULL;
    // we update the tail pointer
    (*list)->tail = node;
    // we added a new node
    (*list)->szList++;

    return 0;
}

// append data to existing list
int list_append_data (struct list_t **list, void *data) {
    int rc;
    struct list_node_t *node;

    node = list_node_new (NULL);
    node->data = data;
    rc = list_append_node (list, node);

    if (rc)
        list_node_destroy (&node, NULL);

    return rc;
}

// prepend a node to existing list
int list_prepend_node (struct list_t **list, struct list_node_t *node) {
    // check list and node validity
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);

    // we link the node to the list
    node->next = (*list)->head;

    // update head and tail
    if ((*list)->head)
        (*list)->head->prev = node;
    if (!(*list)->tail)
        (*list)->tail = node;

    // we link node
    node->prev = NULL;
    node->next = (*list)->head;
    // we update the head pointer
    (*list)->head = node;
    // we added a new node
    (*list)->szList++;

    return 0;
}

// prepend data to existing list
list_prepend_data (struct list_t **list, void *data) {
    int rc;
    struct list_node_t *node;

    node = list_node_new (NULL);
    node->data = data;
    rc = list_prepend_node(list, node);

    if (rc)
        list_node_destroy (&node, NULL);

    return 0;
}

// insert a node at specified position
int list_insert_node (struct list_t **list, struct list_node_t *node, size_t pos) {
    // node for traversing linked list
    struct list_node_t *pNode;
    // variable to ease reading
    struct list_node_t *head;
    // iterator for position
    size_t i;

    // check list and node validity
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);
    // position inexistent
    if ((*list)->szList < pos)
        return -1;

    // we cast
    head = (*list)->head;

    // we traverse the linked list
    for (pNode = head, i = 0; pNode != NULL; pNode = pNode->next, i++) {
        // if we found the specified position
        // then we add the node
        if (i == pos) {
            // if we are at the last node
            // then we append it
            if (!pNode->next)
                list_append_node(list, node);
            // else we insert between nodes
            else {
                // we link node
                // the new node is put at specified position (starting from 1)
                node->next = pNode;
                node->prev = pNode->prev;

                //
                if (node->prev)
                    node->prev->next = node;
                else
                    (*list)->head = node;

                // we update links in nodes
                pNode->prev = node;
            }

            // since we added a node, the list size increase
            (*list)->szList++;

            // success
            return 0;
        }
    }

    printf("failed insertion tat\n");
    // failed to insert node
    return -1;
}

// insert data at specified position
int list_insert_data (struct list_t **list, void *data, size_t pos) {
    struct list_node_t *node;
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
int list_remove_node (struct list_t *list, struct list_node_t **node) {
    // node not valid
    if (!list || !node)
        return -1;
    if (!*node)
        return -1;

    // we first check for pointer validity
    // then we fix links
    if ((*node)->next)
        (*node)->next->prev = (*node)->prev;
    if ((*node)->prev)
        (*node)->prev->next = (*node)->next;

    // we remove the actual node
    free(node);
    *node = NULL;
    list->szList--;

    return 0;
}

// remove a node at specified position
int list_remove_node_at_pos (struct list_t **list, size_t pos) {
    struct list_node_t *node;
    size_t i;

    // check pointer validity
    if (!list || !pos || !*list)
        return -1;

    // position inexistent
    if ((*list)->szList < pos)
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
void* list_get_data_at_pos (struct list_t **list, size_t pos) {
    struct list_node_t *node;
    size_t i;

    // check list and node validity
    if (!list)
        return NULL;
    if (!(*list))
        list_new(list);

    // we check if position specified is in range
    if (pos > (*list)->szList)
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

// show all elements
void list_show_all (struct list_t *list) {
    size_t i;
    struct list_node_t *node;

    // check list and node validity
    if (!list)
        return;

    // we traverse link list and show all node value
    for (node = list->head, i = 0; node != NULL; node = node->next, i++)
        printf("node %u : %p\n", i, node->data);
}

// get list size
size_t list_get_size (struct list_t *list) {
    if (list)
        return list->szList;
    else
        return -1;
}

// return head of list
struct list_node_t* list_begin (struct list_t *list) {
    //
    if (list)
        return list->head;
    // else it's a standalone node
    else
        return NULL;
}

// return tail of list
struct list_node_t* list_end (struct list_t *list) {
    //
    if (list)
        return list->tail;
    // else it's a standalone node
    else
        return NULL;
}

