#ifndef LISTES_DOUBLES_H
#define LISTES_DOUBLES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>             /* pour size_t */
#include "listes_doubles.h"

typedef struct t_double_linked_list t_double_linked_list;
struct t_double_linked_list
{
    void *data;
    struct t_double_linked_list *prev;
    struct t_double_linked_list *next;
};

// Init first node
t_double_linked_list *double_linked_list_new (void);
// Allocate space for data
t_double_linked_list *double_linked_list_data_new (long numberOfBytes);
// Insert a node after
void double_linked_list_insert (t_double_linked_list **p_double_linked_list, void *data);
// Remove a node
void double_linked_list_remove (t_double_linked_list **p_double_linked_list);
// Put address of next node
void double_linked_list_next (t_double_linked_list **p_double_linked_list);
// Put address of previous node
void double_linked_list_prev (t_double_linked_list **p_double_linked_list);
// Return the address of data
void *double_linked_list_data (t_double_linked_list *p_double_linked_list);
// Get the address of the first node
void double_linked_list_first (t_double_linked_list **p_double_linked_list);
// Get the address of the last node
void double_linked_list_last (t_double_linked_list **p_double_linked_list);
// Count number of nodes
size_t double_linked_list_sizeof (t_double_linked_list *p_double_linked_list);
// Destroy the entire list
void double_linked_list_delete (t_double_linked_list **p_double_linked_list);

/*! @struct t_double_linked_list
*   @brief  Liste chainees
*/

// Fonctions d'initialisation de structures
void double_linked_list_zero (t_double_linked_list *liste);
// Fonction d'allocation de liste doublement chainee
t_double_linked_list *double_linked_list_append_new_node (t_double_linked_list *double_linked_list_previousNode);
void double_linked_list_free (t_double_linked_list *double_linked_list);
//
t_double_linked_list* double_linked_list_parcourir_noeud (t_double_linked_list *ListBegin, size_t position);

#ifdef __cplusplus
} // end extern "C"
#endif

#endif /* not H_LISTEDOUBLE */

