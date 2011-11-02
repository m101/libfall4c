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

#include "math/geometry_space.h"
#include "collision.h"

/*! @brief                    Detection de collision pour rectangles
*   @param Object1             Object1
*   @param Object2             Object2
*/
int collision_rect (struct solid_t *Object1, struct solid_t *Object2)
{
    long booleenCollision = 1;

    if ( (Object1 != NULL) && (Object2 != NULL) )
    {
        // Si l'Object 1 est a gauche de l'Object 2
        // Alors pas de collision
        if ( (Object1->Position.x + Object1->width) < Object2->Position.x )
            booleenCollision = 0;
        // Si l'Object 1 est a droite de l'Object 2
        // Alors pas de collision
        else if ( Object1->Position.x > (Object2->Position.x + Object2->width) )
            booleenCollision = 0;

        // Si l'Object 1 est au dessus de l'Object 2
        // Alors pas de collision
        if ( (Object1->Position.y + Object1->height) < Object2->Position.y )
            booleenCollision = 0;
        // Si l'Object 1 est en dessous de l'Object 2
        // Alors pas de collision
        else if ( Object1->Position.y > (Object2->Position.y + Object2->height) )
            booleenCollision = 0;
    }

    return booleenCollision;
}

/*! @brief                    Detection de collision pour rectangles
*                             avec un cadre
*   @param Object1             Object1
*   @param Object2             Object2
*/
int collision_rect_box (struct solid_t *Object1, struct solid_t *Object2)
{
    long booleenCollision = 1;

    if ( (Object1 != NULL) && (Object2 != NULL) )
    {
        // On calcul la collision box
        // Object1
        Object1->collisionWidth = Object1->width * 0.80;
        Object1->collisionHeight = Object1->height * 0.80;
        Object1->collisionOffsetX = (Object1->width - Object1->collisionWidth)/2;
        Object1->collisionOffsetY = (Object1->height - Object1->collisionHeight)/2;
        // Object2
        Object2->collisionWidth = Object2->width * 0.80;
        Object2->collisionHeight = Object2->height * 0.80;
        Object2->collisionOffsetX = (Object2->width - Object2->collisionWidth)/2;
        Object2->collisionOffsetY = (Object2->height - Object2->collisionHeight)/2;

        // Si l'Object 1 est a gauche de l'Object 2
        // Alors pas de collision
        if ( (Object1->Position.x + Object1->width + Object1->collisionOffsetX)
                < (Object2->Position.x + Object2->collisionOffsetX) )
            booleenCollision = 0;
        // Si l'Object 1 est a droite de l'Object 2
        // Alors pas de collision
        else if ( (Object1->Position.x + Object1->collisionOffsetX)
                  > (Object2->Position.x + Object2->collisionOffsetX + Object2->width) )
            booleenCollision = 0;

        // Si l'Object 1 est au dessus de l'Object 2
        // Alors pas de collision
        if ( (Object1->Position.y + Object1->height + Object1->collisionOffsetY)
                < (Object2->Position.y + Object2->collisionOffsetY) )
            booleenCollision = 0;
        // Si l'Object 1 est en dessous de l'Object 2
        // Alors pas de collision
        else if ( (Object1->Position.y + Object1->collisionOffsetY)
                  > (Object2->Position.y + Object2->height + Object2->collisionOffsetY) )
            booleenCollision = 0;
    }

    return booleenCollision;
}


/*! @brief                    Pixel Perfect
*                             Detection de collision pour 2 Object
*   @param screenBuffer       Bitmap a analyse pour les collisions
*   @param Object1             Object1
*   @param Object2             Object2
*   @param collisionColor     Couleur de collision
*/
/*
int collision_pixel_perfect (BITMAP *screenBuffer, struct solid_t *Object1, struct solid_t *Object2, long collisionColor)
{
    int left1, left2, over_left;
    int right1, right2, over_right;
    int top1, top2, over_top;
    int bottom1, bottom2, over_bottom;
    int i = 0, j = 0;

    left1 = Object1->Position.x;
    left2 = Object2->Position.x;
    right1 = Object1->Position.x + Object1->width;
    right2 = Object2->Position.x + Object2->width;
    top1 = Object1->Position.y;
    top2 = Object2->Position.y;
    bottom1 = Object1->Position.y + Object1->height;
    bottom2 = Object2->Position.y + Object2->height;

    // Les collisions simples (Bounding Box)
    // Si le bas de l'Object 1 est au dessus du haut de l'Object 2
    // Alors il n'y a pas collision
    if (bottom1 < top2)
        return 0 ;
    // Si le haut de l'Object 1 est en dessous du bas de l'Object 2
    // Alors il n'y a pas collision
    if (top1 > bottom2)
        return 0 ;
    // Si la droite de l'Object 1 est gauche du cote gauche de l'Object 2
    // Alors il n'y a pas collision
    if (right1 < left2)
        return 0 ;
    // Si la gauche de l'Object 1 est droite du cote droit de l'Object 2
    // Alors il n'y a pas collision
    if (left1 > right2)
        return 0 ;


    // Ok, compute the rectangle of overlap:
    // Si l'Object 1 est en dessous de l'Object 2
    // Alors l'Object 2 est l'Object se trouvant le plus en haut
    if (bottom1 > bottom2)
        over_bottom = bottom2;
    // Sinon l'Object 1 est au dessus
    else
        over_bottom = bottom1;

    // Si l'Object 1 est au dessus de l'Object 2
    // Alors l'Object 2 est l'Object se trouvant le plus en bas
    if (top1 < top2)
        over_top = top2;
    // Sinon l'Object 1 est en dessous
    else
        over_top = top1;
    // Si la droite de l'Object 1 est droite du cote droite de l'Object 2
    // Alors la droite du rectangle d'overlap vaut right2
    if (right1 > right2)
        over_right = right2;
    // Sinon il vaut right1
    else
        over_right = right1;

    // Si la gauche de l'Object 1 est a gauche du cote gauche de l'Object 2
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
//*/

