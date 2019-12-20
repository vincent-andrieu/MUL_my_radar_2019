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

static bool hitboxes = true;
static bool sprites = false;

static void clear_screen(assets_t *assets)
{
    for (unsigned int i = 0;
    i < assets->framebuffer->width * assets->framebuffer->height * 4; i++)
        assets->framebuffer->pixels[i] = 0;
}

void toggle_hitboxes(assets_t *assets)
{
    hitboxes = !hitboxes;
    clear_screen(assets);
}

void toggle_sprites(void)
{
    sprites = !sprites;
}

void draw_towers(assets_t *assets, tower_t *towers)
{
    if (towers == NULL)
        return;
    if (sprites)
        sfRenderWindow_drawSprite(assets->window, towers->sprite->sprite, NULL);
    if (hitboxes)
        for (float angle = 0; angle < 360; angle += 0.1) {
            my_draw_rect(assets->framebuffer, (sfVector2f) {
            towers->radius * cos(angle * M_PI / 180) + towers->x,
            towers->radius * sin(angle * M_PI / 180) + towers->y
            }, (sfVector2f) {2, 2}, sfBlack);
        }
    draw_towers(assets, towers->next);
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