#include <stdio.h>
#include <stdlib.h>
#include "listes_doubles.h"

/*! @brief            Init first node
*/
t_double_linked_list *double_linked_list_new (void)
{
    t_double_linked_list *newList = malloc(sizeof(t_double_linked_list));

    double_linked_list_zero(newList);

    return newList;
}

/* @brief             Allocate space for data
*/
t_double_linked_list *double_linked_list_data_new (long numberOfBytes)
{
    t_double_linked_list *newList = malloc(sizeof(char) * numberOfBytes);

    return newList;
}

/*! @brief                            Insert a node after
*   @param p_double_linked_list       Node where to insert after
*   @param data                       Data contained in node
*/
void double_linked_list_insert (t_double_linked_list **p_double_linked_list, void *data)
{
    if (p_double_linked_list != NULL)
    {
        t_double_linked_list *p_previous = *p_double_linked_list;
        t_double_linked_list *p_node = NULL;
        t_double_linked_list *p_next = NULL;

        if (p_previous != NULL)
            p_next = p_previous->next;

        p_node = malloc (sizeof (*p_node));
        if (p_node != NULL)
        {
            p_node->data = data;
            p_node->next = p_next;
            if (p_next != NULL)
                p_next->prev = p_node;
            p_node->prev = p_previous;
            if (p_previous != NULL)
                p_previous->next = p_node;
            *p_double_linked_list = p_node;
        }
        else
        {
            fprintf (stderr, "Memoire insuffisante\n");
            exit (EXIT_FAILURE);
        }
    }
}

/*! @brief                            Remove a node
*   @param p_double_linked_list       Node to remove
*/
void double_linked_list_remove (t_double_linked_list **p_double_linked_list)
{
    if (p_double_linked_list != NULL && *p_double_linked_list != NULL)
    {
        t_double_linked_list *p_node = *p_double_linked_list;
        t_double_linked_list *p_previous = p_node->prev;
        t_double_linked_list *p_next = p_node->next;

        if (p_previous != NULL)
            p_previous->next = p_next;
        // If p_next is NULL then
        if (!p_next)
            *p_double_linked_list = p_previous;
        else
        {
            p_next->prev = p_previous;
            *p_double_linked_list = p_next;
        }
        // We destroy the removed node
        free (p_node), p_node = NULL;
    }
}

/*! @brief                            Put address of next node
*   @param p_double_linked_list       Node to put the address of next node into
*/
void double_linked_list_next (t_double_linked_list **p_double_linked_list)
{
    if (p_double_linked_list != NULL && *p_double_linked_list != NULL)
        *p_double_linked_list = (*p_double_linked_list)->next;
}

/*! @brief                            Put address of previous node
*   @param p_double_linked_list       Node to put the address of previous node into
*/
void double_linked_list_prev (t_double_linked_list **p_double_linked_list)
{
    if (p_double_linked_list != NULL && *p_double_linked_list != NULL)
        *p_double_linked_list = (*p_double_linked_list)->prev;
}

/*! @brief                            Return the address of data
*   @param p_double_linked_list       Node to return data address from
*/
void *double_linked_list_data (t_double_linked_list *p_double_linked_list)
{
    return ((p_double_linked_list != NULL) ? p_double_linked_list->data : NULL);
}

/*! @brief                            Get the address of the firt node
*   @param p_double_linked_list       Node to modify
*/
void double_linked_list_first (t_double_linked_list **p_double_linked_list)
{
    if (p_double_linked_list != NULL && *p_double_linked_list != NULL)
    {
        while ((*p_double_linked_list)->prev != NULL)
            double_linked_list_prev (p_double_linked_list);
    }
}

/*! @brief                            Get the address of the last node
*   @param p_double_linked_list       Node to modify
*/
void double_linked_list_last (t_double_linked_list **p_double_linked_list)
{
    if (p_double_linked_list != NULL && *p_double_linked_list != NULL)
    {
        while ((*p_double_linked_list)->next != NULL)
            double_linked_list_next (p_double_linked_list);
    }
}

/*! @brief                            Count number of nodes
*   @param p_double_linked_list       List to count node(s) from
*/
size_t double_linked_list_sizeof (t_double_linked_list *p_double_linked_list)
{
    size_t n = 0;

    if (p_double_linked_list != NULL)
    {
        double_linked_list_first (&p_double_linked_list);
        while (p_double_linked_list != NULL)
        {
            n++;
            double_linked_list_next (&p_double_linked_list);
        }
    }
    return n;
}

/*! @brief                            Destroy the entire list
*   @param p_double_linked_list       List to destroy
*/
void double_linked_list_delete (t_double_linked_list **p_double_linked_list)
{
    if (p_double_linked_list != NULL && *p_double_linked_list != NULL)
    {
        double_linked_list_first (p_double_linked_list);
        while (*p_double_linked_list != NULL)
            double_linked_list_remove (p_double_linked_list);
    }
}

/*
Liste chainees
*/

/*! @brief                Initialise une variable de type t_double_linked_list
*   @param    liste       Liste doublement chainee a initialiser
*/
void double_linked_list_zero (t_double_linked_list *liste)
{
    t_double_linked_list listeInit = {0};
    if (liste)
        *liste = listeInit;
}

/*! @brief                                      Append new node after node given
*   @param    double_linked_list_previousNode   Node after which we append a new node
*/
t_double_linked_list *double_linked_list_append_new_node (t_double_linked_list *double_linked_list_previousNode)
{
    t_double_linked_list *temp = NULL;

    // We check that the pointer is valid
    if (double_linked_list_previousNode)
    {
        if (double_linked_list_previousNode->next)
        {
            // On fait une substitution de 2 variables (on parcours la liste)
            temp = double_linked_list_previousNode;
            // On alloue le noeud
            double_linked_list_previousNode = double_linked_list_new();
            double_linked_list_previousNode->prev = temp;
            // We link the new allocated node to the last previous node
            temp->next = double_linked_list_previousNode;
        }
    }

    return double_linked_list_previousNode;
}

/*! @brief                Libere une liste chainee dont les elements ont ete \
                           alloues avec malloc (variable de type t_double_linked_list)
*   @param    liste       Liste doublement chainee a liberer
*/
void double_linked_list_free (t_double_linked_list *double_linked_list)
{
    t_double_linked_list *pListe = double_linked_list;
    t_double_linked_list *temp = NULL;

    // Parcourir la liste chainee vers la fin
    // et liberer les noeuds
    while (pListe != NULL)
    {
        temp = pListe->next;
        free(pListe->data);
        free(pListe);
        pListe = temp;
    }
}

/*! @brief                     Va a la position qu'on veut
*   @param ListBegin           Noeud a partir duquel commencer
*   @param position            Position ou on souhaite se rendre
*/
t_double_linked_list* double_linked_list_parcourir_noeud (t_double_linked_list *ListBegin, size_t position)
{
    t_double_linked_list *NodePrev = NULL, *NodeLast = ListBegin;
    size_t i = 0;

    while (NodeLast)
    {
        if (i == position)
            break;

        i++;

        NodePrev = NodeLast;
        NodeLast = NodeLast->next;
    }

    return NodePrev;
}

/*! @brief                     Supprime un noeud
*   @param PListeDouble        Liste ou se trouve le noeud a supprimer
*   @param PNoeud              Noeud a supprimer
*/
void double_linked_list_supprimer_noeud (t_double_linked_list *PListeDouble,
        t_double_linked_list *PNoeud)
{
    t_double_linked_list *Parcours = PListeDouble;
    t_double_linked_list *NoeudTemPrev = NULL, *NoeudTempNext = NULL;

    if (PNoeud != NULL)
    {
        while (Parcours)
        {
            if (Parcours == PNoeud)
            {
                NoeudTempNext = PNoeud->next;
                NoeudTemPrev = PNoeud->prev;
                NoeudTempNext->prev = NoeudTemPrev;
                NoeudTemPrev->next = NoeudTempNext;

                free(Parcours);

                break;
            }
            Parcours = Parcours->next;
        }
    }
}
