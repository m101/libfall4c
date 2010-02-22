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
