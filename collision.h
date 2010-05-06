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

#ifndef _COLLISION_H
#define _COLLISION_H

#include <stdio.h>
#include <stdlib.h>

#include <allegro.h>

#include "structures.h"
#include "collision.h"

struct struct t_object
{
    // Image de l'objet
    BITMAP *ObjetImage;
    // Position de l'image
    struct t_position Position;
    // Vecteur (donne le sens et la direction)
    struct t_position Vecteur;
    // Hauteur et largeur de l'objet
    unsigned width;
    unsigned height;
    // Collision box
    unsigned collisionWidth;
    unsigned collisionHeight;
    unsigned collisionOffsetX;
    unsigned collisionOffsetY;
    t_images Tiles;
};

long collisionOlimarEnvironment (BITMAP *screenBuffer, struct t_position positionOlimar);
// Detection de collision pour rectangles
int collision_rect (struct t_object *Objet1, struct t_object *Objet2);
// Detection de collision pour rectangles avec un cadre
int collision_rect_box (struct t_object *Objet1, struct t_object *Objet2);
// Pixel Perfect : Detection de collision pour 2 objet
int collision_pixel_perfect (BITMAP *screenBuffer, struct t_object *Objet1, struct t_object *Objet2, long collisionColor);

#endif
