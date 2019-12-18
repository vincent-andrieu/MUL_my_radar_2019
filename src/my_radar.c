/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** my_radar
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <time.h>
#include "my.h"
#include "graph.h"
#include "my_radar.h"

sprite_t *create_sprite(char *filepath, float x, float y)
{
    sprite_t *sprite = malloc(sizeof(sprite_t));

    if (sprite == NULL)
        return NULL;
    sprite->position = (sfVector2f) {x, y};
    sprite->texture = sfTexture_createFromFile(filepath, NULL);
    sprite->sprite = sfSprite_create();
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    sfSprite_setPosition(sprite->sprite, sprite->position);
    return sprite;
}

int my_radar(assets_t *assets, char *map_path)
{
    entities_t *entities = read_map(map_path);
    sprite_t *map = create_sprite(BACKGROUND_PATH, 0, 0);
    sfClock *clock = sfClock_create();

    if (entities == NULL || map == NULL)
        return EXIT_ERROR;
    while (!does_kill_prog(assets->window)) {
        sfRenderWindow_drawSprite(assets->window, map->sprite, NULL);
        draw_towers(assets->window, entities->towers);
        draw_planes(assets->window, entities->planes);
        draw_clock(assets->window, clock);
        refresh_screen(assets);
    }
    sfClock_destroy(clock);
    return EXIT_SUCCESS;
}

/*sfIntRect_contains

start
destroy
restart
*/