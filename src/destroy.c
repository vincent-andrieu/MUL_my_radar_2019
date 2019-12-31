/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** destroy functions
*/

#include <stdlib.h>
#include "my_radar.h"

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