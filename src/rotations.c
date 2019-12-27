/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** set planes rotations
*/

#include <stdlib.h>
#include <math.h>
#include "my_radar.h"

void take_off(plane_t *plane)
{
    float rotation = sfSprite_getRotation(plane->sprite->sprite);
    sfVector2f scale;

    do {
        scale = sfSprite_getScale(plane->sprite->sprite);
        scale.x--;
        scale.y--;
        rotation--;
        sfSprite_setScale(plane->sprite->sprite, scale);
        sfSprite_setRotation(plane->sprite->sprite, rotation);
    } while (scale.x > 1 && scale.y > 1);
}

void set_plane_rotation(plane_t *plane)
{
    float angle = atan((plane->dest_x - plane->x)
                        / (plane->dest_y - plane->y)) * 180 / M_PI;

    if (angle < 0)
        angle = -angle;
    sfRectangleShape_setRotation(plane->hitbox, angle);
    //sfSprite_setRotation(plane->sprite->sprite, angle);
}