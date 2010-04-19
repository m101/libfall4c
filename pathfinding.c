#include <stdio.h>
#include <stdlib.h>

#include <allegro.h>

#include "pathfinding.h"
#include "structures.h"
#include "arbres_binaires.h"

#define DEBUG

// A* ou A Star

/*
Position * AStar_Search(Position Start, Position Goal, Unite Unit)
{
    // Open:    liste de recherche des nouveaux points
    // Closed:  liste des points déjà examinés
    // Start:   point de départ
    // Goal:    point à atteindre
    // Unit:    unité à déplacer (pour le calcul du poids du chemin)

    // Initialisation du point de départ
    New.Loc = Start
    New.CostFromStart = 0
    New.CostTOGoal = PathCostEstimate(Start, Goal, Unit)
    New.Parent = NULL
    Open.Add(New)

    // On parcours la liste Open
    while(Open != NULL)
    {
        // Récupérer le point de poids le plus faible
        Node = Open.GetLowest()
        // but atteint
        if (Node == Goal)
        {
            // On construit le chemin en remontant les points au fur et à mesure
            Liste = Open.MakePath()
            return (Position *)Liste
        }
        else
        {
            Pour chaque voisin NodeNew de Node
            {
                NewCost = Node.CostFromStart + Cost(Node,NodeNew,Unit)
                // on ignore les points déjà examinés qui ne sont pas améliorables
                if ((NodeNew is in Open or Closed) and (NodeNew.CostFromStart >= NewCost))
                {
                    continue
                }
                // on enregistre le nouveau point ou on le met à jour
                //(on a trouvé un chemin plus court pour arriver à ce point)
                else
                {
                    NodeNew.Parent = Node
                    NodeNew.CostFromStart = NewCost
                    NodeNew.CostToGoal = PathCostEstimate(NodeNew.Loc, Goal, Unit)
                    NodeNew.TotalCost = NodeNew.CostFromStart + NodeNew.CostToGoal
                    if (NodeNew is in Closed)
                    {
                        Closed.Remove(NodeNew)
                    }
                    if (NodeNew is in Open)
                    {
                        // ajuste la position de NodeNew en le mettant en première position
                        Open.AdjustPosition(NodeNew)
                    }
                    else
                    {
                        Open.Add(NodeNew)
                    }
                }
            } // on a terminé avec Node
        }
        Closed.Add(Node)
    }
    // aucun chemin n'existe pour rejoindre Goal
    return NULL
}
*/

struct List* path_find_astar (struct t_position Depart, struct t_position Arrivee)
{
    struct List *Arbre = NULL;
    struct List *NodeCostLowestArbre = NULL;
    long tempCostFromStart = 0;
    int astarContinuer = 1;

    struct t_path_node NodeNew;
    struct t_path_node NodeCurrent;

    long i = 0, j = 0;

    // Noeud courant
    path_node_zero(&NodeCurrent);
    NodeCurrent.Position.x = Depart.x;
    NodeCurrent.Position.x = Depart.y;
    NodeCurrent.costFromStart = 0;
    NodeCurrent.costToGoal_heuristic = path_calcul_manhattan_heuristic(Depart, Arrivee); //, Unite);
    NodeCurrent.cost = NodeCurrent.costFromStart + NodeCurrent.costToGoal_heuristic;
    NodeCurrent.isOpen = 1;

#ifdef DEBUG
    printf("Avant la boucle while\n");
    printf("Arrivee.x : %ld\n", Arrivee.x);
    printf("Arrivee.y : %ld\n\n", Arrivee.y);
#endif

    while (astarContinuer)
    {
        // On cherche le noeud ayant le cout le plus bas
        NodeCostLowestArbre = binary_search_tree_search_lowestCostNode (Arbre);


#ifdef DEBUG
        printf("binary_tree_display_path(Arbre);\n");
        binary_tree_display_path (Arbre);

        printf("NodeCostLowestArbre = binary_search_tree_search_lowestCostNode (Arbre);\n");
        printf("NodeCurrent.Position.x : %ld\n", NodeCurrent.Position.x);
        printf("NodeCurrent.Position.y : %ld\n\n", NodeCurrent.Position.y);
#endif

        path_mov_list_to_node (&NodeCurrent, NodeCostLowestArbre);

#ifdef DEBUG
        printf("path_mov_list_to_node (&NodeCurrent, NodeCostLowestArbre);\n");
        printf("NodeCurrent.Position.x : %ld\n", NodeCurrent.Position.x);
        printf("NodeCurrent.Position.y : %ld\n\n", NodeCurrent.Position.y);
#endif

        // On l'ajoute parmis les fermes
        NodeCurrent.isOpen = 0;
        Arbre = binary_search_tree_add_path (Arbre, &NodeCurrent);

#ifdef DEBUG
        printf("Arbre = binary_search_tree_add_path (Arbre, &NodeCurrent);\n");
        printf("NodeCurrent.Position.x : %ld\n", NodeCurrent.Position.x);
        printf("NodeCurrent.Position.y : %ld\n\n", NodeCurrent.Position.y);

        printf("Arbre = binary_search_tree_add_path (Arbre, &NodeCurrent);\n");
        printf("Arrivee.x : %ld\n", Arrivee.x);
        printf("Arrivee.y : %ld\n\n", Arrivee.y);
#endif

        // Si le noeud est le noeud d'arrivee alors on quitte la boucle
        if ( (NodeCurrent.Position.x == Arrivee.x)
                && (NodeCurrent.Position.x == Arrivee.x) )
            break;

        // On "regarde" les cases autours de la case courante
        for (i = -1; i <= 1; i++)
        {
            NodeNew.Position.x = NodeCurrent.Position.x + i;
            for (j = -1; j <= 1; j++)
            {
                NodeNew.Position.y = NodeCurrent.Position.y + j;

#ifdef DEBUG
                printf("Pour les cases alentours\n");
                printf("NodeNew.Position.x : %ld\n", NodeNew.Position.x);
                printf("NodeNew.Position.y : %ld\n", NodeNew.Position.y);

                getchar();
#endif

                // On cherche si le noeud est dans la liste ouverte

                // Sinon elle est soit dans la liste fermee ou aucune des deux

                // Diagonale : Bas Gauche + Bas Droit + Haut Gauche + Haut Droit
                if ( ((i == 1) && (j == 1)) || ((i == 1) && (j == -1))
                        || ((i == -1) && (j == -1)) || ((i == -1) && (j == 1)) )
                {
                    NodeNew.costNode = 14;
                }
                // Haut, Droit, Bas, Gauche
                else
                {
                    NodeNew.costNode = 10;
                }

                // Elle n'est ni dans la liste ouverte ou fermee
                NodeNew.isOpen = -1;
                // Elle est dans la liste ouverte?
                // Si elle est dans les branches de gauches alors elle ouverte
                binary_search_tree_search_isOpen (Arbre, &NodeNew);
                // Elle est dans la liste fermee?
                // Si elle est dans les branches de droite alors elle est fermee
                binary_search_tree_search_isClose (Arbre, &NodeNew);

                // Si le noeud est dans la liste ouverte
                if (NodeNew.isOpen == 1)
                {
                    // On calcule le cout from start de ce noeud
                    tempCostFromStart = NodeCurrent.costFromStart + NodeNew.costNode;
                    // Si G calcule est plus petit que l'ancien G
                    // Alors on recalcule F et on change le parent à CurrentNode
                    if (tempCostFromStart < NodeNew.costFromStart)
                    {
                        NodeNew.costFromStart = tempCostFromStart;
                        NodeNew.cost = NodeNew.costFromStart + NodeNew.costToGoal_heuristic;
                        NodeNew.ParentNodePoint = NodeCurrent.Position;
                        binary_search_tree_add_path (Arbre, &NodeNew);
                        // Ajout et verifs a faire
                        // Tri a faire
                    }
                }
                // Si le noeud n'est ni ouvert ni fermer
                else if (NodeNew.isOpen < 0)
                {
                    // On ajoute le noeud a la liste ouverte
                    // printf("Ajout d'un noeud dans la liste ouverte : ");
                    // Dernier noeud de OpenList
                    // OpenListLastNode = NodeNew;
                    NodeNew.isOpen = 1;
                    // Calcul du cout du point de depart : G
                    NodeNew.costFromStart = NodeCurrent.costFromStart + NodeNew.costNode;
                    // Calcul du cout heuristique : H
                    NodeNew.costToGoal_heuristic = path_calcul_manhattan_heuristic(NodeNew.Position, Arrivee); //, Unite);
                    // Calcul du cout total estime : F = G + H
                    NodeNew.cost = NodeNew.costFromStart + NodeNew.costToGoal_heuristic;
                    // Le parent de ce noeud est le noeud courant
                    NodeNew.ParentNodePoint = NodeCurrent.Position;
                    binary_search_tree_add_path (Arbre, &NodeNew);
                }
            }
        }
    }

    // On remonte le chemin
    binary_tree_display_path (Arbre);

    return Arbre;
}

long path_heuristic_manhattan (struct t_position Depart, struct t_position Arrivee)
{
    struct t_position Manhattan = {0, 0};
    long manhattan = 0;
    Manhattan.x = abs(Depart.x - Arrivee.x) * 10;
    Manhattan.y = abs(Depart.y - Arrivee.y) * 10;

    manhattan = Manhattan.x + Manhattan.y;

    return manhattan;
}

/*! @brief              Find the lowest cost
*   @param Node         Node to check for lowest cost
*/
struct List* path_find_lowestcost (struct List *Node)
{
    struct List *l_lowestCostNode = Noeud;
    struct List *NoeudCurrent = Noeud;
    long min = 0;

    if (Noeud != NULL)
        min = ((struct t_path_node *)(Noeud->data))->cost;

    while (NoeudCurrent != NULL)
    {
        printf("Current node - x : %ld, y : %ld\n",\
               ((struct t_path_node *)(NoeudCurrent->data))->Position.x,\
               ((struct t_path_node *)(NoeudCurrent->data))->Position.y);
        printf("G cost : %ld\n", ((struct t_path_node *)(NoeudCurrent->data))->costFromStart);
        printf("H cost : %ld\n", ((struct t_path_node *)(NoeudCurrent->data))->costToGoal_heuristic);
        printf("F cost : %ld\n\n", ((struct t_path_node *)(NoeudCurrent->data))->cost);

        if ( ((struct t_path_node *)(NoeudCurrent->data))->cost < min)
        {
            min = ((struct t_path_node *)(NoeudCurrent->data))->cost;
            l_lowestCostNode = NoeudCurrent;
        }

        NoeudCurrent = NoeudCurrent->next;
    }

    printf("Noeud plus petit : %p\n", l_lowestCostNode);

    return l_lowestCostNode;
}

// find a node according to it's position
struct List* path_find_node (struct List *List, struct t_position Position)
{
    struct List *NodeCurrent = List;
    struct List *NodeReturned = NULL;

    while (NodeCurrent != NULL)
    {
        if ( ((struct t_path_node *)(NodeCurrent->data))->Position.x == Position.x
                && ((struct t_path_node *)(NodeCurrent->data))->Position.y == Position.y )
        {
            NodeReturned = NodeCurrent;
            break;
        }

        NodeCurrent = NodeCurrent->next;
    }

    return NodeReturned;
}

// append a node to path
int path_list_node_add (struct List *List, struct List *Node)
{
        return list_append_node (List, Node);
}

// remove a node from path
int path_list_node_delete (struct List *Node)
{
        list_remove_node (Node);
}

// convert a path node to a list
struct List* path_node_to_list (struct t_path_node *Node)
{
        struct List *List;

        if (!Node)
                return NULL;

        List = list_new ();

        if (List != NULL)
        {
                ((struct t_path_node *)(List->data))->Position.x = Node->Position.x;
                ((struct t_path_node *)(List->data))->Position.y = Node->Position.y;
                ((struct t_path_node *)(List->data))->ParentNodePoint.x = Node->ParentNodePoint.x;
                ((struct t_path_node *)(List->data))->ParentNodePoint.y = Node->ParentNodePoint.y;
                ((struct t_path_node *)(List->data))->type = Node->type;
                ((struct t_path_node *)(List->data))->poids = Node->poids;
                ((struct t_path_node *)(List->data))->direction = Node->direction;
                ((struct t_path_node *)(List->data))->cost = Node->cost;
                ((struct t_path_node *)(List->data))->costFromStart = Node->costFromStart;
                ((struct t_path_node *)(List->data))->costToGoal_heuristic = Node->costToGoal_heuristic;
                ((struct t_path_node *)(List->data))->isOpen = Node->isOpen;
        }

        return List;
}

// convert a list to a path node
struct t_path_node* path_list_to_node (struct List *List)
{
        struct t_path_node *Node;
        
        if (!List)
                return NULL;

        Node = path_node_new ();

        if ( (Liste != NULL) && (Node != NULL) )
        {
                Node->Position.x = ((struct t_path_node *)(List->data))->Position.x;
                Node->Position.y = ((struct t_path_node *)(List->data))->Position.y;
                Node->ParentNodePoint.x = ((struct t_path_node *)(List->data))->ParentNodePoint.x;
                Node->ParentNodePoint.y = ((struct t_path_node *)(List->data))->ParentNodePoint.y;
                Node->type = ((struct t_path_node *)(List->data))->type;
                Node->poids = ((struct t_path_node *)(List->data))->poids;
                Node->direction = ((struct t_path_node *)(List->data))->direction;
                Node->cost = ((struct t_path_node *)(List->data))->cost;
                Node->costFromStart = ((struct t_path_node *)(List->data))->costFromStart;
                Node->costToGoal_heuristic = ((struct t_path_node *)(List->data))->costToGoal_heuristic;
                Node->isOpen = ((struct t_path_node *)(List->data))->isOpen;
        }

        return Node;
}

struct List* path_sort_list (struct List *Liste)
{
        struct List *CurrentNode = NULL;
        struct List *TempNode = NULL;
        long min = 0;

        if (Liste != NULL)
                min = ((struct t_path_node *)(Liste->data))->cost;

        for (CurrentNode = Liste; CurrentNode != NULL; CurrentNode = CurrentNode->next)
        {
                if (((struct t_path_node *)(CurrentNode->data))->cost < min)
                {
                        min = ((struct t_path_node *)(CurrentNode->data))->cost;
                        TempNode = CurrentNode->next;
                        CurrentNode->next = CurrentNode;
                        CurrentNode->prev = TempNode;
                }
        }

        return Liste;
}

void path_node_zero (struct t_path_node *Node)
{
        if (Node != NULL)
        {
                Node->Position.x = 0;
                Node->Position.y = 0;
                // Noeud parent
                Node->ParentNodePoint.x = 0;
                Node->ParentNodePoint.y = 0;
                Node->type = 0;
                Node->poids = 0;
                Node->direction = 0;
                // Manhattan : F = G + H
                // F : Cout estimer
                // G : Cout a partir du point de depart
                // H : Cout "heuristique" jusqu'a l'arrivee
                Node->cost = 0;                   // F
                Node->costFromStart = 0;          // G
                Node->costToGoal_heuristic = 0;   // H
                Node->costNode = 0;
                Node->isOpen = 0;
        }
}

// Tri Liste Open
void path_ajouter_noeud_liste_ouverte ()
{
}

void path_ajouter_noeud_liste_fermee ()
{
}

void binary_tree_display_path (struct tree_t *root)
{
    if (root != NULL)
    {
        // binary_tree_display_right (root->prev);
        printf("x : %3ld, y : %3ld\n", ((struct t_path_node *)(root->data))->Position.x, ((struct t_path_node *)(root->data))->Position.y);
        binary_tree_display_path (root->prev);
    }
}

