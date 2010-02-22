#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <allegro.h>

#include "struct Listes_doubles.h"
#include "structures.h"

struct path_node
{
    struct t_position Position;
    // Noeud parent
    struct t_position ParentNodePoint;
    struct List *ParentNodestruct List;
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
};

/* A Star : Pathfinding
*/
struct List* path_find_astar (struct t_position Depart, struct t_position Arrivee); //, t_unit Unite);
long path_calcul_manhattan_heuristic (struct t_position Depart, struct t_position Arrivee); //, t_unit Unite);
struct List* path_find_lowestcost (struct List *Noeud);
// Ajouter un noeud a la struct Liste chainee
struct List* path_ajouter_noeud_struct Liste (struct List *List, struct List *Appendedstruct Liste);
// Enlever un noeud a la struct Liste chainee
struct List* path_enlever_noeud_struct Liste (struct List *List, struct List *Appendedstruct Liste);
// "Stocker" un t_path_node dans la struct Liste
void path_mov_node_to_struct List (struct List *List, t_path_node Node);
// "Stocker" une struct Liste dans un t_path_node
void path_mov_struct List_to_node (t_path_node *Node, struct List *List);
// Trouve un noeud selon sa position (x, y)
struct List* path_find_noeud (struct List *List, struct t_position Position);
// Tri de la struct Liste par cout
struct List* path_tri_struct Liste (struct List *List);
// Initialisation d'un t_path_node
void path_node_zero (t_path_node *Node);

#endif

