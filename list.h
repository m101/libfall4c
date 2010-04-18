#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

// list management data
// A static attribute is shared among ALL instance of a class, so if we have many different lists
// they will all have the same head and tail pointer value which is not a correct behaviour.
// The node in a same lists share the same list head, tail and size attributes.
// The following structure will allow to have correct behaviour since other lists
// won't corrupt other lists head, tail and size.
struct ManagementData
{
    // pointer for head and tail of list
    // I have errors when using List * so I used the generic pointer void *
    void *m_head, *m_tail;
    // size of list
    size_t m_size;
};

// allocate a new management data unit
struct ManagementData* management_data_new (void);
// destroy a management data unit
int management_data_destroy (struct ManagementData **md);

struct List
{
    // management info (head, tail and list size)
    struct ManagementData *m_md;
    // doubly linked list
    struct List *m_next, *m_prev;
    // data
    void *m_data;
    // if node is used : true
    // else : false
    int m_used;
};

// node characteristic
// a node is defined by it's address and it's position in a linked list
struct NodeCharacteristics
{
    size_t m_pos;
    void* m_node;
};

    // default constructor for list
    struct List* list_new (struct List **list);
    // append a node to existing list
    int list_append_node (struct List **list, struct List *node);
    // append data to existing struct List
    int list_append_data (struct List **list, void *data);
    // prepend a node to existing list
    int list_prepend_node (struct List **list, struct List *node);
    // prepend data to existing list
    int list_prepend_data (struct List **list, void *data);
    // insert a node at specified position
    int list_insert_node (struct List **list, struct List *node, size_t pos);
    // insert data at specified position
    int list_insert_data (struct List **list, void* data, size_t pos);
    // remove current node
    int list_remove_node (struct List **node);
    // remove a node at specified position
    int list_remove_node_at_pos (struct List **list, size_t pos);

    // show all elements of the list
    void list_show_all (struct List *list);
    // get list size
    size_t list_get_size (struct List *list);
    // return head of list
    struct List* list_begin (struct List *list);
    // return tail of list
    struct List* list_end (struct List *list);

#ifdef __cplusplus
}
#endif

#endif /* _LIST_H_ */