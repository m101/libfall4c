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

struct t_double_linked_list* path_find_astar (t_position Depart, t_position Arrivee) //, t_unit Unite)
{
    t_double_linked_list *Arbre = NULL;
    t_double_linked_list *NodeCostLowestArbre = NULL;
    long tempCostFromStart = 0;
    int astarContinuer = 1;

    t_path_node NodeNew;
    t_path_node NodeCurrent;

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

long path_calcul_manhattan_heuristic (t_position Depart, t_position Arrivee)// , t_unit Unite)
{
    t_position Manhattan = {0, 0};
    long manhattan = 0;
    Manhattan.x = abs(Depart.x - Arrivee.x) * 10;
    Manhattan.y = abs(Depart.y - Arrivee.y) * 10;

    manhattan = Manhattan.x + Manhattan.y;

    return manhattan;
}

/*! @brief Find the lowest cost
*   @param Noeud Node to check for lowest cost
*/
t_double_linked_list* path_find_lowestcost (t_double_linked_list *Noeud)
{
    t_double_linked_list *l_lowestCostNode = Noeud;
    t_double_linked_list *NoeudCurrent = Noeud;
    long min = 0;

    if (Noeud != NULL)
        min = ((t_path_node *)(Noeud->data))->cost;

    while (NoeudCurrent != NULL)
    {
        printf("Noeud courrant; x : %ld, y : %ld\n",\
               ((t_path_node *)(NoeudCurrent->data))->Position.x,\
               ((t_path_node *)(NoeudCurrent->data))->Position.y);
        printf("G cost : %ld\n", ((t_path_node *)(NoeudCurrent->data))->costFromStart);
        printf("H cost : %ld\n", ((t_path_node *)(NoeudCurrent->data))->costToGoal_heuristic);
        printf("F cost : %ld\n\n", ((t_path_node *)(NoeudCurrent->data))->cost);

        if ( ((t_path_node *)(NoeudCurrent->data))->cost < min)
        {
            min = ((t_path_node *)(NoeudCurrent->data))->cost;
            l_lowestCostNode = NoeudCurrent;
        }

        NoeudCurrent = NoeudCurrent->next;
    }

    printf("Noeud plus petit : %p\n", l_lowestCostNode);

    return l_lowestCostNode;
}

t_double_linked_list* path_find_noeud (t_double_linked_list *Liste, t_position Position)
{
    t_double_linked_list *NodeCurrent = Liste;
    t_double_linked_list *NodeReturned = NULL;

    while (NodeCurrent != NULL)
    {
        if ( ((t_path_node *)(NodeCurrent->data))->Position.x == Position.x
                && ((t_path_node *)(NodeCurrent->data))->Position.y == Position.y )
        {
            NodeReturned = NodeCurrent;
            break;
        }

        NodeCurrent = NodeCurrent->next;
    }

    return NodeReturned;
}

t_double_linked_list* path_ajouter_noeud_liste (t_double_linked_list *Liste, t_double_linked_list *AppendedListe)
{
    t_double_linked_list *ListNode = Liste, *ListLastNode = NULL;
    /*
    if (Liste != NULL)
        Liste->next = AppendedListe;
    */
    // On recherche le dernier noeud de la liste
    while (ListNode)
    {
        ListLastNode = ListNode;
        ListNode = ListNode->next;
    }
    printf("path_ajouter_noeud_liste : %p\n", ListLastNode);
    // Si la liste a "aPend" n'est pas nulle
    // Alors on verifie si la liste contenante n'est pas nulle
    if ((AppendedListe != NULL) && (AppendedListe != Liste))
    {
        // Si le dernier element de la liste n'est pas nul
        // Alors on ajoute le noeud en parametre à la suite de celui-ci
        if (ListLastNode != NULL)
        {
            ListLastNode->next = AppendedListe;
            AppendedListe->prev = ListLastNode;
            AppendedListe->next = NULL;
        }
    }

    return Liste;
}

t_double_linked_list* path_enlever_noeud_liste (t_double_linked_list *Liste, t_double_linked_list *AppendedListe)
{
    t_double_linked_list *ListPrev = NULL, *ListNext = NULL;
    t_double_linked_list *NoeudForward = NULL, *NoeudBackward = Liste;

    if ( (AppendedListe != NULL) )
    {
        ListPrev = AppendedListe->prev;
        ListNext = AppendedListe->next;

        if ( (ListPrev != NULL) && (ListNext != NULL) )
        {
            for (NoeudForward = Liste; NoeudForward != NULL;\
                    NoeudForward = NoeudForward->next)
            {
                if ( (NoeudForward == AppendedListe)
                        || (NoeudBackward == AppendedListe) )
                {
                    // On enleve le premier element
                    if (ListPrev == NULL)
                    {
                        AppendedListe->next = NULL;
                        ListNext->prev = NULL;
                    }
                    // On enleve le dernier element
                    else if (ListNext == NULL)
                    {
                        AppendedListe->prev = NULL;
                        ListPrev->next = NULL;
                    }
                    // On enlève les autres noeuds
                    else
                    {
                        ListPrev->next = ListNext;
                        ListNext->prev = ListPrev;
                    }
                    break;
                }
                if (NoeudBackward != NULL)
                    NoeudBackward = NoeudBackward->prev;
            }
        }
    }

    return Liste;
}

void path_mov_node_to_list (t_double_linked_list *Liste, t_path_node Node)
{
    if (Liste != NULL)
    {
        ((t_path_node *)(Liste->data))->Position.x = Node.Position.x;
        ((t_path_node *)(Liste->data))->Position.y = Node.Position.y;
        ((t_path_node *)(Liste->data))->ParentNodePoint.x = Node.ParentNodePoint.x;
        ((t_path_node *)(Liste->data))->ParentNodePoint.y = Node.ParentNodePoint.y;
        ((t_path_node *)(Liste->data))->type = Node.type;
        ((t_path_node *)(Liste->data))->poids = Node.poids;
        ((t_path_node *)(Liste->data))->direction = Node.direction;
        ((t_path_node *)(Liste->data))->cost = Node.cost;
        ((t_path_node *)(Liste->data))->costFromStart = Node.costFromStart;
        ((t_path_node *)(Liste->data))->costToGoal_heuristic = Node.costToGoal_heuristic;
        ((t_path_node *)(Liste->data))->isOpen = Node.isOpen;
    }
}

void path_mov_list_to_node (t_path_node *Node, t_double_linked_list *Liste)
{
    if ( (Liste != NULL) && (Node != NULL) )
    {
        Node->Position.x = ((t_path_node *)(Liste->data))->Position.x;
        Node->Position.y = ((t_path_node *)(Liste->data))->Position.y;
        Node->ParentNodePoint.x = ((t_path_node *)(Liste->data))->ParentNodePoint.x;
        Node->ParentNodePoint.y = ((t_path_node *)(Liste->data))->ParentNodePoint.y;
        Node->type = ((t_path_node *)(Liste->data))->type;
        Node->poids = ((t_path_node *)(Liste->data))->poids;
        Node->direction = ((t_path_node *)(Liste->data))->direction;
        Node->cost = ((t_path_node *)(Liste->data))->cost;
        Node->costFromStart = ((t_path_node *)(Liste->data))->costFromStart;
        Node->costToGoal_heuristic = ((t_path_node *)(Liste->data))->costToGoal_heuristic;
        Node->isOpen = ((t_path_node *)(Liste->data))->isOpen;
    }
}

t_double_linked_list* path_tri_liste (t_double_linked_list *Liste)
{
    t_double_linked_list *CurrentNode = NULL;
    t_double_linked_list *TempNode = NULL;
    long min = 0;

    if (Liste != NULL)
        min = ((t_path_node *)(Liste->data))->cost;

    for (CurrentNode = Liste; CurrentNode != NULL; CurrentNode = CurrentNode->next)
    {
        if (((t_path_node *)(CurrentNode->data))->cost < min)
        {
            min = ((t_path_node *)(CurrentNode->data))->cost;
            TempNode = CurrentNode->next;
            CurrentNode->next = CurrentNode;
            CurrentNode->prev = TempNode;
        }
    }

    return Liste;
}

void path_node_zero (t_path_node *Node)
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
