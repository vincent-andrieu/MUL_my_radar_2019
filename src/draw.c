/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** draw entities
*/

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "my_radar.h"

void toggle_hitboxes(plane_t *planes)
{
    sfColor color;

    if (planes == NULL)
        return;
    color = sfRectangleShape_getOutlineColor(planes->hitbox);
    if (color.a == sfBlack.a)
        sfRectangleShape_setOutlineColor(planes->hitbox, sfTransparent);
    else
        sfRectangleShape_setOutlineColor(planes->hitbox, sfBlack);
    toggle_hitboxes(planes->next);
}

void toggle_sprites(plane_t *planes, tower_t *towers)
{
    if (planes == NULL && towers == NULL)
        return;
    if (planes != NULL)
        planes->sprite_toggle = !planes->sprite_toggle;
    if (towers != NULL)
        towers->sprite_toggle = !towers->sprite_toggle;
    toggle_sprites(planes == NULL ? NULL : planes->next,
                    towers == NULL ? NULL : towers->next);
}

void draw_towers(assets_t *assets, tower_t *towers)
{
    if (towers == NULL)
        return;
    if (towers->sprite_toggle)
        sfRenderWindow_drawSprite(assets->window, towers->sprite->sprite, NULL);
    sfRenderWindow_drawCircleShape(assets->window, towers->circle, NULL);
    draw_towers(assets, towers->next);
}

void draw_planes(sfRenderWindow *window, plane_t *planes)
{
    if (planes == NULL)
        return;
    if (planes->toggle) {
        if (planes->sprite_toggle)
            sfRenderWindow_drawSprite(window, planes->sprite->sprite, NULL);
        sfRenderWindow_drawRectangleShape(window, planes->hitbox, NULL);
    }
    draw_planes(window, planes->next);
}