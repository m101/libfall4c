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

#include <string.h>

#include "data/data_ops.h"
#include "data/list.h"

struct list_node* _list_has_node (struct list_simple *list, struct list_node *node);
// default constructor for node
struct list_node* _list_node_new (void *data);
// default destructor for node
int _list_node_destroy (struct list_node **node, void (*destroy_data)(void **));
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

static const struct data_ops list_data_ops = {
    .comparator = comparator_no_ops,
    .destroy = destroy_no_ops,
    .get_size = get_size_no_ops,
    .show = show_no_ops
};

// default constructor for list
struct list_simple* list_new (void) 
{
    struct list_simple *list = calloc (1, sizeof(*list));

    list->dops = calloc (1, sizeof(list_data_ops));
    memcpy (list->dops, &list_data_ops, sizeof(list_data_ops));

    return list;
}

// free list without destructing objects
int list_delete (struct list_simple **list)
{
    struct list_node *node, *next;

    if (!list ||  !*list)
        return -1;

    // we traverse the linked list to destroy it
    for (node = list_simple_begin(*list); node != NULL; ) {
        next = node->next;
        _list_node_destroy (&node, NULL);
        node = next;
    }

    free ( (*list)->dops );
    free (*list);
    *list = NULL;

    return 0;
}

// default destructor
int list_destroy (struct list_simple **list)
{
    struct list_node *node, *next;

    if (!list ||  !*list)
        return -1;

    // we traverse the linked list to destroy it
    for (node = list_simple_begin(*list); node != NULL; ) {
        next = node->next;
        _list_node_destroy(&node, (*list)->dops->destroy);
        node = next;
    }

    free ( (*list)->dops );
    free (*list);
    *list = NULL;

    return 0;
}

// only free list structure not all nodes
int list_free (struct list_simple *list)
{
    free (list);
}

/*  TODO: Take into account circular lists as well
 */
int list_count_nodes(struct list_simple *list)
{
    struct list_node *node;
    int count;

    if (!list)
        return -1;

    for (node = list_simple_begin(list), count = 0; node != NULL; node = node->next, count++);

    return count;
}

// merge two list in one, no dupes checks
// destroy list2
// return new list
struct list_simple *list_append_list (struct list_simple **list1, struct list_simple **list2)
{
    if (!list1 || !list2 || !*list2)
        return NULL;

#ifdef DEBUG
    printf ("list_merge(): number of nodes in list1: %d (before)\n", list_count_nodes(*list1));
    if (*list1) {
        printf ("   list1->head = %p\n", (*list1)->head);
        printf ("   list1->tail = %p\n", (*list1)->tail);
    }
    printf ("   list2->head = %p\n", (*list2)->head);
    printf ("   list2->tail = %p\n", (*list2)->tail);
    printf ("list_merge(): number of nodes in list2: %d (before)\n", list_count_nodes(*list2));
#endif

    if (*list1) {
        (*list1)->tail->next = (*list2)->head;
        (*list2)->head->prev = (*list1)->tail;
        (*list1)->size = (*list1)->size + (*list2)->size;

        free (*list2);
        *list2 = NULL;
    }
    else {
        *list1 = *list2;
        free (*list2);
        *list2 = NULL;
    }

#ifdef DEBUG
    printf ("list_merge: number of nodes in list: %d (after)\n", list_count_nodes(*list1));
#endif

    return *list1;
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
int _list_node_destroy (struct list_node **node, void (*destroy_data)(void **))
{
    if (!node || !*node)
        return -1;

    // unlink
    if ((*node)->prev)
        (*node)->prev->next = (*node)->next;
    if ((*node)->next)
        (*node)->next->prev = (*node)->prev;

    if ((*node)->data && destroy_data) {
        destroy_data(&((*node)->data));
        (*node)->data = NULL;
    }
    free(*node);
    *node = NULL;

    return 0;
}

// append a node to existing list
int _list_append_node (struct list_simple **list, struct list_node *node)
{
    void *data;

    if (!list || !node)
        return -1;
    if (!*list)
        *list = list_new();

    // avoid duplicate node
    if ((*list)->tail == node)
        return -1;

    // corruption check
    if (node->prev && node != node->prev->next) {
        fprintf (stderr, "error: _list_append_node(): Link corruption detected\n");
        exit (1);
    }
    if (node->next && node != node->next->prev) {
        fprintf (stderr, "error: _list_append_node(): Link corruption detected\n");
        exit (1);
    }

    // unlink node
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    // zero node prev and next
    node->next = NULL;
    node->prev = (*list)->tail;

    if ((*list)->head == NULL)
        (*list)->head = node;

    if ((*list)->tail)
        (*list)->tail->next = node;

    // this is append_node and not append list!
    (*list)->tail = node;
    (*list)->size++;

    return 0;
}

// append data to existing list
int list_append_data (struct list_simple **list, void *data)
{
    int rc;
    struct list_node *node;

    if (!list || !data)
        return -1;

    node = _list_node_new (data);
    if (!node)
        return -1;
    rc = _list_append_node (list, node);
    if (rc < 0)
        _list_node_destroy (&node, NULL);

    return rc;
}

// prepend a node to existing list
int _list_prepend_node (struct list_simple **list, struct list_node *node)
{
    void *data;

    if (!list || !node)
        return -1;
    if (!*list)
        *list = list_new();

    // avoid duplicate node
    if ((*list)->head == node)
        return -1;

    // corruption check
    if (node->prev && node != node->prev->next) {
        fprintf (stderr, "error: _list_append_node(): Link corruption detected\n");
        exit (1);
    }
    if (node->next && node != node->next->prev) {
        fprintf (stderr, "error: _list_append_node(): Link corruption detected\n");
        exit (1);
    }

    // unlink node
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    // zero node prev
    // node next will be NULL or head
    node->next = (*list)->head;
    node->prev = NULL;

    if ((*list)->tail == NULL)
        (*list)->tail = node;

    if ((*list)->head)
        (*list)->head->prev = node;

    // this is prepend_node and not append list!
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

    // unlink node
    if ((*node)->next)
        (*node)->next->prev = (*node)->prev;
    if ((*node)->prev)
        (*node)->prev->next = (*node)->next;

    // if node is head
    // then new head is the node following the old head
    if (list->head == *node)
        list->head = list->head->next;
    // if node is tail
    // then new tail is the node preceding the old tail
    if (list->tail == *node)
        list->tail = list->tail->prev;

    // we remove the actual node
    free(*node);
    *node = NULL;
    list->size--;
    if (list->size < 0)
        list->size = 0;

    return 0;
}

// remove data from existing list
int list_remove_data (struct list_simple *list, void *data)
{
    int rc;
    struct list_node *iter_cur, *iter_next;

    if (!list || !data) {
        fprintf (stderr, "error: list_remove_data(): Bad parameter(s)\n");
        return -1;
    }

    if (!list->dops) {
        fprintf (stderr, "error: list_remove_data(): list->dops->comparator is NULL\n");
        return -1;
    }

    // we traverse the linked list to destroy it
    for (iter_cur = list_simple_begin(list); iter_cur != NULL; ) {
        iter_next = iter_cur->next;

        if (list->dops->comparator (iter_cur->data, data) == 0) {
            _list_remove_node (list, &iter_cur);
            return 0;
        }

        iter_cur = iter_next;
    }

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
        fprintf (stderr, "error: list_get_data_at_pos(): Bad pos %lu\n", pos);
        return NULL;
    }

    // we traverse the linked list
    idx_iter = 0;
    list_simple_for_each (list, iter, data) {
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

struct list_simple *list_has_data (struct list_simple *list, void *data)
{
    struct list_node *node;

    if (!list)
        return NULL;

    for (node = list->head; node != NULL; node = node->next) {
        if (list->dops->comparator(node->data, data) == 0)
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
        printf("node %lu : %p\n", i, node->data);
}

