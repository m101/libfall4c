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

// create a new management data unit
struct ManagementData* management_data_new (void)
{
    struct ManagementData* md;

    // we allocate memory
    md = malloc(sizeof(*md));
    // we initialize correctly the structure
    md->m_head = NULL;
    md->m_tail = NULL;
    md->m_size = 0;

    return md;
}

// destroy a management data unit
int management_data_destroy (struct ManagementData **md)
{
    // bad pointer given
    if (!md)
        return -1;
    // we free md unit
    if (*md)
    {
        free(*md);
        *md = NULL;
        return 1;
    }

    return 0;
}

// default constructor for list
struct List* list_new (struct List **list)
{
    // check list validity
    if (!list)
        return NULL;

    *list = malloc(sizeof(*list));
    //
    (*list)->m_next = NULL;
    (*list)->m_prev = NULL;
    // management data
    (*list)->m_md = NULL;
    //
    (*list)->m_data = 0;
    (*list)->m_used = 0;

    return *list;
}

// default destructor
int list_destroy (struct List **list)
{
    // node for traversing linked list
    struct List *nodeTraverse;
    // head and tail to ease reading
    struct List *head, *tail;

    // check list validity
    if (!list)
        return -1;

    head = (*list)->m_md->m_head;
    tail = (*list)->m_md->m_tail;
    // we destroy data management unit
    free((*list)->m_md);
    (*list)->m_md = NULL;

    // we traverse the linked list to destroy it
    for (nodeTraverse = head; nodeTraverse != NULL; )
    {
        nodeTraverse = nodeTraverse->m_next;

        // we destroy the current node
        if (nodeTraverse)
        {
            // we destroy node
            free(nodeTraverse->m_prev);
            // we ensure m_prev value in case of double frees
            nodeTraverse->m_prev = NULL;
        }
    }
    
    return 0;
}

// append a node to existing list
int list_append_node (struct List **list, struct List *node)
{
    // check list and node validity
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);
    // we check that management data exist
    if (!(*list)->m_md)
    {
        // we create a data management unit
        (*list)->m_md = management_data_new();
        // we update the head pointer
        (*list)->m_md->m_head = *list;
    }

    // we link the node to the list
    node->m_prev = (*list)->m_md->m_tail;

    // we end the list
    if ((*list)->m_md->m_tail)
        ((struct List *)(*list)->m_md->m_tail)->m_next = node;

    // we end list
    node->m_next = NULL;
    // the node is used
    node->m_used = 1;
    // we update node management data
    node->m_md = (*list)->m_md;
    // we update the tail pointer
    (*list)->m_md->m_tail = node;
    // we added a new node
    (*list)->m_md->m_size++;

    return 0;
}

// append data to existing list
int list_append_data (struct List **list, void *data)
{
    struct List *nodeNew;

    // check list and node validity
    if (!list || !data)
        return -1;
    if (!(*list))
        list_new(list);

    // we ensure that the management data zone exist
    if (!(*list)->m_md)
        (*list)->m_md = management_data_new();

    // if not defined
    // we update head pointer
    if (!(*list)->m_md->m_head)
        (*list)->m_md->m_head = *list;
    // if not defined
    // we update tail pointer
    if (!(*list)->m_md->m_tail)
        (*list)->m_md->m_tail = (*list)->m_md->m_head;

    // if the current node isn't marked as used
    // then we only add data
    if (!(*list)->m_used)
    {
        (*list)->m_md->m_size++;
        (*list)->m_used = 1;
        (*list)->m_data = data;
    }
    // else we append a new node and add data
    else
    {
        list_new(&nodeNew);
        nodeNew->m_data = data;
        list_append_node (list, nodeNew);
    }

    // printf("append data - m_size : %u\n", (*list)->m_md->m_size);

    return 0;
}

// prepend a node to existing list
int list_prepend_node (struct List **list, struct List *node)
{
    // check list and node validity
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);

    // we check that management data exist
    if (!(*list)->m_md)
    {
        // we create a data management unit
        (*list)->m_md = management_data_new();
        // we update the tail pointer
        (*list)->m_md->m_tail = *list;
    }

    // we link the node to the list
    node->m_next = (*list)->m_md->m_head;

    // we end the list
    if ((*list)->m_md->m_head)
        ((struct List *)(*list)->m_md->m_head)->m_prev = node;

    // we end list
    node->m_prev = NULL;
    // the node is used
    node->m_used = 1;
    // we update node management data
    node->m_md = (*list)->m_md;
    // we update the head pointer
    (*list)->m_md->m_head = node;
    // we added a new node
    (*list)->m_md->m_size++;

    return 0;
}

// prepend data to existing list
list_prepend_data (struct List **list, void *data)
{
    struct List *nodeNew;

    // check list and node validity
    if (!list || !data)
        return -1;
    if (!(*list))
        list_new(list);

    // we ensure that the management data zone exist
    if (!(*list)->m_md)
        (*list)->m_md = management_data_new();

    // if not defined
    // we update head pointer
    if (!(*list)->m_md->m_head)
        (*list)->m_md->m_head = list;
    // if not defined
    // we update tail pointer
    if (!(*list)->m_md->m_tail)
        (*list)->m_md->m_tail = (*list)->m_md->m_head;

    // if the current node isn't marked as used
    // then we only add data
    if (!(*list)->m_used)
    {
        (*list)->m_md->m_size++;
        (*list)->m_used = 1;
        (*list)->m_data = data;
    }
    // else we append a new node and add data
    else
    {
        list_new(&nodeNew);
        nodeNew->m_data = data;
        list_prepend_node(list, nodeNew);
    }

    printf("prepend data - m_size : %u\n", (*list)->m_md->m_size);

    return 0;
}

// insert a node at specified position
int list_insert_node (struct List **list, struct List *node, size_t pos)
{
    // node for traversing linked list
    struct List *nodeTraverse;
    // variable to ease reading
    struct List *head;
    // iterator for position
    size_t i;

    // check list and node validity
    if (!list || !node)
        return -1;
    if (!(*list))
        list_new(list);

    // we check to see if data management unit exist
    if (!(*list)->m_md)
    {
        // we allocate a data management unit
        (*list)->m_md = management_data_new();
        // the node being inserted will have the same management unit as the list
        node->m_md = (*list)->m_md;
    }

    // we cast
    head = (*list)->m_md->m_head;

    // position inexistent
    if ((*list)->m_md->m_size < pos)
        return -1;

    // we traverse the linked list
    for (nodeTraverse = head, i = 1; nodeTraverse != NULL; nodeTraverse = nodeTraverse->m_next, i++)
    {
        // if we found the specified position
        // then we add the node
        if (i == pos)
        {
            // if we are at the last node
            // then we append it
            if (!nodeTraverse->m_next)
                list_append_node(list, node);
            // else we insert between nodes
            else
            {
                // we link node
                // the new node is put at specified position (starting from 1)
                node->m_next = nodeTraverse;
                node->m_prev = nodeTraverse->m_prev;

                //
                if (node->m_prev)
                    node->m_prev->m_next = node;
                else
                    (*list)->m_md->m_head = node;

                // we update links in nodes
                nodeTraverse->m_prev = node;
            }

            // since we added a node, the list size increase
            (*list)->m_md->m_size++;

            // success
            return 0;
        }
    }

    printf("failed insertion tat\n");
    // failed to insert node
    return -1;
}

// insert data at specified position
int list_insert_data (struct List **list, void* data, size_t pos)
{
    struct List *nodeNew;
    int failed;

    // check list and node validity
    if (!list || !data)
        return -1;
    if (!(*list))
        list_new(list);

    // we allocate a new node
    list_new(&nodeNew);
    // we insert data
    nodeNew->m_data = data;

    // we insert the node in the list
    failed = list_insert_node(list, nodeNew, pos);
    // if successful
    if (!failed)
        return 0;
    // else we failed
    else
    {
        list_destroy(&nodeNew);
        return -1;
    }
}

// remove current node
int list_remove_node (struct List **node)
{
    // node not valid
    if (!node)
        return -1;
    if (!*node)
        return -1;

    // we first check for pointer validity
    // then we fix links
    if ( (*node)->m_next)
        (*node)->m_next->m_prev = (*node)->m_prev;
    if ((*node)->m_prev)
        (*node)->m_prev->m_next = (*node)->m_next;

    // we remove the actual node
    free(node);
    *node = NULL;

    return 0;
}

// remove a node at specified position
int list_remove_node_at_pos (struct List **list, size_t pos)
{
    struct List *nodeTraverse;
    size_t i;

    // check pointer validity
    if (!list || !pos || !*list)
        return -1;

    // if we want to remove the first node
    // we remove it
    if (pos == 1)
        return list_remove_node(list);

    // we check for data management unit
    // if it doesn't exist, then we can't remove the node at the specified position
    if (!(*list)->m_md)
        return -1;

    // position inexistent
    if ((*list)->m_md->m_size < pos)
        return -1;

    for (nodeTraverse = (*list)->m_md->m_head, i = 1; nodeTraverse != NULL; nodeTraverse = nodeTraverse->m_next, i++)
    {
        if (i == pos)
            list_remove_node(&nodeTraverse);

    }

    // we didn't remove any node
    return -1;
}

// get data at specified node position
void* list_get_data_at_pos (struct List **list, size_t pos)
{
    struct List *nodeTraverse;
    size_t i;

    // check list and node validity
    if (!list)
        return NULL;
    if (!(*list))
        list_new(list);

    // we check if position specified is in range
    if (pos > (*list)->m_md->m_size)
        return (*list)->m_data;

    // we traverse the linked list
    for (nodeTraverse = (*list)->m_md->m_head, i = 1; nodeTraverse != NULL; nodeTraverse = nodeTraverse->m_next, i++)
    {
        // if we found the specified node
        // then we return the data
        if (i == pos)
            return nodeTraverse->m_data;
    }

    // failed to get the data at the specified location
    return (*list)->m_data;
}

// show all elements
void list_show_all (struct List *list)
{
    size_t i;
    struct List *nodeTraverse;

    // check list and node validity
    if (!list)
        return;

    // we traverse link list and show all node value
    for (nodeTraverse = list->m_md->m_head, i = 1; nodeTraverse != NULL; nodeTraverse = nodeTraverse->m_next, i++)
        printf("node %u : %p\n", i, nodeTraverse->m_data);
}

// get list size
size_t list_get_size (struct List *list)
{
    // check list and node validity
    if (!list)
        return -1;

    if (list->m_md)
        return list->m_md->m_size;
    else
        return 0;
}

// return head of list
struct List* list_begin (struct List *list)
{
    // check list pointer validity
    if (!list)
        return NULL;
    // if management data unit exist
    // then we have other nodes
    if (list->m_md)
        return list->m_md->m_head;
    // else it's a standalone node
    else
        return list;
}

// return tail of list
struct List* list_end (struct List *list)
{
    // check list pointer validity
    if (!list)
        return NULL;
    // if management data unit exist
    // then we have other nodes
    if (list->m_md)
        return list->m_md->m_tail;
    // else it's a standalone node
    else
        return list;
}
