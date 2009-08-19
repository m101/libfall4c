#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <allegro.h>

#include "listes_doubles.h"
#include "structures.h"

typedef struct t_path_node
{
    t_position Position;
    // Noeud parent
    t_position ParentNodePoint;
    t_double_linked_list *ParentNodeList;
    long type;
    long poids;
    long direction;
    // Manhattan : F = G + H
    // F : Cout estimer
    // G : Cout a partir du point de depart
    // H : Cout "heuristique" jusqu'a l'arrivee
    long cost;                   // F
    long costFromStart;          // G
    long costToGoal_heuristic;   // H
    long costNode;
    long isOpen;
} t_path_node;

/* A Star : Pathfinding
*/
struct t_double_linked_list* path_find_astar (t_position Depart, t_position Arrivee); //, t_unit Unite);
long path_calcul_manhattan_heuristic (t_position Depart, t_position Arrivee); //, t_unit Unite);
t_double_linked_list* path_find_lowestcost (t_double_linked_list *Noeud);
// Ajouter un noeud a la liste chainee
t_double_linked_list* path_ajouter_noeud_liste (t_double_linked_list *Liste, t_double_linked_list *AppendedListe);
// Enlever un noeud a la liste chainee
t_double_linked_list* path_enlever_noeud_liste (t_double_linked_list *Liste, t_double_linked_list *AppendedListe);
// "Stocker" un t_path_node dans la liste
void path_mov_node_to_list (t_double_linked_list *Liste, t_path_node Node);
// "Stocker" une liste dans un t_path_node
void path_mov_list_to_node (t_path_node *Node, t_double_linked_list *Liste);
// Trouve un noeud selon sa position (x, y)
t_double_linked_list* path_find_noeud (t_double_linked_list *Liste, t_position Position);
// Tri de la liste par cout
t_double_linked_list* path_tri_liste (t_double_linked_list *Liste);
// Initialisation d'un t_path_node
void path_node_zero (t_path_node *Node);

#endif

