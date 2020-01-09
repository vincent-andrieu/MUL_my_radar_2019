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

static void draw_all(assets_t *assets, entities_t *entities,
                    sfClock *clock, sfText *txt)
{
    draw_towers(assets, entities->towers);
    draw_planes(assets->window, entities->planes);
    draw_clock(assets->window, clock, txt);
}

static int game(assets_t *assets, entities_t *entities,
                sfClock *clock, sfText *txt)
{
    sprite_t *map = create_sprite(BACKGROUND_PATH, 0, 0);
    float seconds;

    if (map == NULL)
        return EXIT_ERROR;
    while (!does_kill_prog(assets, entities)) {
        seconds = sfTime_asSeconds(sfClock_getElapsedTime(clock));
        entities->planes = check_planes_times(entities->planes, seconds,
                                            assets);
        entities->planes = move_planes(entities->planes, entities->planes,
                                        seconds, assets);
        entities->planes = check_collisions(entities->planes, entities->planes,
                                            entities->towers);
        if (entities->planes ==  NULL)
            break;
        sfRenderWindow_drawSprite(assets->window, map->sprite, NULL);
        draw_all(assets, entities, clock, txt);
        refresh_screen(assets);
    }
    sfSprite_destroy(map->sprite);
    return EXIT_SUCCESS;
}

int my_radar(assets_t *assets, char *map_path)
{
    entities_t *entities = read_map(map_path);
    sfClock *clock = sfClock_create();
    sfText *txt = sfText_create();
    sfFont *font = sfFont_createFromFile(FONT_PATH);
    int exit_value = EXIT_SUCCESS;

    if (entities == NULL)
        return EXIT_ERROR;
    initialize_font(txt, font);
    exit_value = game(assets, entities, clock, txt);
    destroy_all(entities, clock, txt, font);
    return exit_value;
}