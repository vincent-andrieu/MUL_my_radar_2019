/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** set planes rotations
*/

#include <math.h>
#include "my_radar.h"

void take_off(plane_t *plane, assets_t *assets)
{
    float rotation = sfSprite_getRotation(plane->sprite->sprite);
    sfVector2f scale;
    bool direction;

    direction = rand() % 2;
    sfRectangleShape_setFillColor(plane->hitbox, sfWhite);
    sfRectangleShape_setOutlineColor(plane->hitbox, sfWhite);
    do {
        scale = sfSprite_getScale(plane->sprite->sprite);
        scale.x -= 0.1;
        scale.y -= 0.1;
        rotation += direction ? -1 : 1;
        sfSprite_setScale(plane->sprite->sprite, scale);
        sfSprite_setRotation(plane->sprite->sprite, rotation);
        sfRenderWindow_drawRectangleShape(assets->window, plane->hitbox, NULL);
        if (plane->sprite_toggle)
            sfRenderWindow_drawSprite(assets->window, plane->sprite->sprite, NULL);
        refresh_screen(assets);
    } while (scale.x > 0 && scale.y > 0);
}