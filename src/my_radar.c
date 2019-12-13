/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** collision btw planes
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <time.h>
#include "my.h"
#include "graph.h"
#include "my_radar.h"

entity_t *create_sprite(char *filepath, float x, float y)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->position = (sfVector2f) {x, y};
    entity->texture = sfTexture_createFromFile(filepath, NULL);
    entity->sprite = sfSprite_create();
    sfSprite_setTexture(entity->sprite, entity->texture, sfTrue);
    sfSprite_setPosition(entity->sprite, entity->position);
    return entity;
}

static void draw_map(assets_t *assets)
{
    entity_t *map = create_sprite("resource/map.png", 0, 0);

    sfRenderWindow_drawSprite(assets->window, map->sprite, NULL);
    refresh_screen(assets);
}

int my_radar(assets_t *assets)
{
    draw_map(assets);
    
    return EXIT_SUCCESS;
}

//sfIntRect_contains