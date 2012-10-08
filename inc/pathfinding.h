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

#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include "data/list.h"
#include "math/geometry_space.h"

struct path_node
{
    struct t_position Position;
    // Parent node
    struct t_position ParentNodePoint;
    struct List *ParentNodestruct List;
    long type;
    long weigth;
    long direction;
    // Manhattan : F = G + H
    // F : Estimated cost
    // G : Cost from starting position
    // H : Cost heuristic to arrival
    long cost;                   // F
    long costFromStart;          // G
    long costToGoal_heuristic;   // H
    long costNode;
    long isOpen;
};

/* A Star : Pathfinding
*/
// pathfinding : A*
struct List* path_find_astar (struct t_position Start, struct t_position Arrival);

// pathfinding heuristic : manhattan
long path_heuristic_manhattan (struct t_position Start, struct t_position Arrival);

// find the lowest cost
struct List* path_find_lowestcost (struct List *Noeud);

// append a node to path
int path_list_node_add (struct List *List, struct List *Node);

// remove a node from path
int path_list_node_delete (struct List *Node);

// convert a path node to a list
struct List* path_node_to_list (struct t_path_node *Node)

// convert a list to a path node
struct t_path_node* path_list_to_node (struct List *List)

// find a node according to it's position
struct List* path_find_node (struct List *List, struct t_position Position);

// sort path nodes according to cost
struct List* path_sort_list (struct List *List);

// Initialisation d'un t_path_node
void path_node_zero (t_path_node *Node);



struct tree_t* binary_search_tree_add_path (struct tree_t *node,
                    struct t_path_node *pathNode);
void binary_tree_display_path (struct tree_t *racine);
struct tree_t* binary_search_tree_search_lowestCostNode (struct tree_t *Root);

// Ouvert ou ferme?
void binary_search_tree_search_isOpen (struct tree_t *Root, t_path_node *Node);
void binary_search_tree_search_isClose (struct tree_t *Root, t_path_node *Node);

#endif

