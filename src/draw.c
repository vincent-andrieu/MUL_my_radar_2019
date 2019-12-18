/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** draw entities
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_radar.h"

static bool hitboxes = true;
static bool sprites = false;

void toggle_hitboxes(void)
{
    hitboxes = !hitboxes;
}

void toggle_sprites(void)
{
    sprites = !sprites;
}

void draw_towers(sfRenderWindow *window, tower_t *towers)
{
    if (towers == NULL)
        return;
    if (sprites)
        sfRenderWindow_drawSprite(window, towers->sprite->sprite, NULL);
    if (hitboxes)
        sfRenderWindow_drawSprite(window, towers->hitbox->sprite, NULL);
    draw_towers(window, towers->next);
}

void draw_planes(sfRenderWindow *window, plane_t *planes)
{
    if (planes == NULL)
        return;
    if (sprites)
        sfRenderWindow_drawSprite(window, planes->sprite->sprite, NULL);
    if (hitboxes)
        sfRenderWindow_drawSprite(window, planes->hitbox->sprite, NULL);
    draw_planes(window, planes->next);
}