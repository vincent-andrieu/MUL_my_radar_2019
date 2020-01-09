/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** destroy functions
*/

#include <stdlib.h>
#include "my_radar.h"

plane_t *destroy_plane(plane_t *origin, plane_t *plane, bool is_take_off,
                        assets_t *assets)
{
    if (plane->prev != NULL)
        plane->prev->next = plane->next;
    if (plane->next != NULL)
        plane->next->prev = plane->prev;
    if (plane->prev == NULL)
        origin = plane->next;
    if (is_take_off)
        take_off(plane, assets);
    sfSprite_destroy(plane->sprite->sprite);
    sfRectangleShape_destroy(plane->hitbox);
    free(plane);
    return origin;
}

static void destroy_towers(tower_t *towers)
{
    if (towers == NULL)
        return;
    destroy_towers(towers->next);
    sfCircleShape_destroy(towers->circle);
    sfSprite_destroy(towers->sprite->sprite);
    free(towers);
}

void destroy_all(entities_t *entities, sfClock *clock,
                sfText *txt, sfFont *font)
{
    sfFont_destroy(font);
    sfText_destroy(txt);
    sfClock_destroy(clock);
    destroy_towers(entities->towers);
    free(entities);
}