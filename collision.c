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

#include <stdio.h>
#include <stdlib.h>

#include <allegro.h>

#include "structures.h"
#include "collision.h"

/*! @brief                    Detection de collision pour rectangles
*   @param Objet1             Objet1
*   @param Objet2             Objet2
*/
int collision_rect (struct t_object *Objet1, struct t_object *Objet2)
{
    long booleenCollision = 1;

    if ( (Objet1 != NULL) && (Objet2 != NULL) )
    {
        // Si l'objet 1 est a gauche de l'objet 2
        // Alors pas de collision
        if ( (Objet1->Position.x + Objet1->width) < Objet2->Position.x )
            booleenCollision = 0;
        // Si l'objet 1 est a droite de l'objet 2
        // Alors pas de collision
        else if ( Objet1->Position.x > (Objet2->Position.x + Objet2->width) )
            booleenCollision = 0;

        // Si l'objet 1 est au dessus de l'objet 2
        // Alors pas de collision
        if ( (Objet1->Position.y + Objet1->height) < Objet2->Position.y )
            booleenCollision = 0;
        // Si l'objet 1 est en dessous de l'objet 2
        // Alors pas de collision
        else if ( Objet1->Position.y > (Objet2->Position.y + Objet2->height) )
            booleenCollision = 0;
    }

    return booleenCollision;
}

/*! @brief                    Detection de collision pour rectangles
*                             avec un cadre
*   @param Objet1             Objet1
*   @param Objet2             Objet2
*/
int collision_rect_box (struct t_object *Objet1, struct t_object *Objet2)
{
    long booleenCollision = 1;

    if ( (Objet1 != NULL) && (Objet2 != NULL) )
    {
        // On calcul la collision box
        // Objet1
        Objet1->collisionWidth = Objet1->width * 0.80;
        Objet1->collisionHeight = Objet1->height * 0.80;
        Objet1->collisionOffsetX = (Objet1->width - Objet1->collisionWidth)/2;
        Objet1->collisionOffsetY = (Objet1->height - Objet1->collisionHeight)/2;
        // Objet2
        Objet2->collisionWidth = Objet2->width * 0.80;
        Objet2->collisionHeight = Objet2->height * 0.80;
        Objet2->collisionOffsetX = (Objet2->width - Objet2->collisionWidth)/2;
        Objet2->collisionOffsetY = (Objet2->height - Objet2->collisionHeight)/2;

        // Si l'objet 1 est a gauche de l'objet 2
        // Alors pas de collision
        if ( (Objet1->Position.x + Objet1->width + Objet1->collisionOffsetX)
                < (Objet2->Position.x + Objet2->collisionOffsetX) )
            booleenCollision = 0;
        // Si l'objet 1 est a droite de l'objet 2
        // Alors pas de collision
        else if ( (Objet1->Position.x + Objet1->collisionOffsetX)
                  > (Objet2->Position.x + Objet2->collisionOffsetX + Objet2->width) )
            booleenCollision = 0;

        // Si l'objet 1 est au dessus de l'objet 2
        // Alors pas de collision
        if ( (Objet1->Position.y + Objet1->height + Objet1->collisionOffsetY)
                < (Objet2->Position.y + Objet2->collisionOffsetY) )
            booleenCollision = 0;
        // Si l'objet 1 est en dessous de l'objet 2
        // Alors pas de collision
        else if ( (Objet1->Position.y + Objet1->collisionOffsetY)
                  > (Objet2->Position.y + Objet2->height + Objet2->collisionOffsetY) )
            booleenCollision = 0;
    }

    return booleenCollision;
}


/*! @brief                    Pixel Perfect
*                             Detection de collision pour 2 objet
*   @param screenBuffer       Bitmap a analyse pour les collisions
*   @param Objet1             Objet1
*   @param Objet2             Objet2
*   @param collisionColor     Couleur de collision
*/
int collision_pixel_perfect (BITMAP *screenBuffer, struct t_object *Objet1, struct t_object *Objet2, long collisionColor)
{

    int left1, left2, over_left;
    int right1, right2, over_right;
    int top1, top2, over_top;
    int bottom1, bottom2, over_bottom;
    int i = 0, j = 0;

    left1 = Objet1->Position.x;
    left2 = Objet2->Position.x;
    right1 = Objet1->Position.x + Objet1->width;
    right2 = Objet2->Position.x + Objet2->width;
    top1 = Objet1->Position.y;
    top2 = Objet2->Position.y;
    bottom1 = Objet1->Position.y + Objet1->height;
    bottom2 = Objet2->Position.y + Objet2->height;

    // Les collisions simples (Bounding Box)
    // Si le bas de l'objet 1 est au dessus du haut de l'objet 2
    // Alors il n'y a pas collision
    if (bottom1 < top2)
        return 0 ;
    // Si le haut de l'objet 1 est en dessous du bas de l'objet 2
    // Alors il n'y a pas collision
    if (top1 > bottom2)
        return 0 ;
    // Si la droite de l'objet 1 est gauche du cote gauche de l'objet 2
    // Alors il n'y a pas collision
    if (right1 < left2)
        return 0 ;
    // Si la gauche de l'objet 1 est droite du cote droit de l'objet 2
    // Alors il n'y a pas collision
    if (left1 > right2)
        return 0 ;


    // Ok, compute the rectangle of overlap:
    // Si l'objet 1 est en dessous de l'objet 2
    // Alors l'objet 2 est l'objet se trouvant le plus en haut
    if (bottom1 > bottom2)
        over_bottom = bottom2;
    // Sinon l'objet 1 est au dessus
    else
        over_bottom = bottom1;

    // Si l'objet 1 est au dessus de l'objet 2
    // Alors l'objet 2 est l'objet se trouvant le plus en bas
    if (top1 < top2)
        over_top = top2;
    // Sinon l'objet 1 est en dessous
    else
        over_top = top1;
    // Si la droite de l'objet 1 est droite du cote droite de l'objet 2
    // Alors la droite du rectangle d'overlap vaut right2
    if (right1 > right2)
        over_right = right2;
    // Sinon il vaut right1
    else
        over_right = right1;

    // Si la gauche de l'objet 1 est a gauche du cote gauche de l'objet 2
    // Alors la gauche du rectangle d'overlap vaut left2
    if (left1 < left2)
        over_left = left2;
    // Sinon il vaut left1
    else
        over_left = left1;

    // Now start scanning the whole rectangle of overlap,
    // checking the corresponding pixel of each object's
    // bitmap to see if they're both non-zero:

    for (i = over_top; i < over_bottom; i++)
    {
        for (j = over_left; j < over_right; j++)
        {
            if ( getpixel(screenBuffer, j, i) == collisionColor )
                return 1;
        }
    }

    // Le plus mauvais cas : On a pas de collisions malgre avoir scanner tout
    // le rectangle d'overlap

    return 0;
}
