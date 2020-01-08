/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** move planes
*/

#include <math.h>
#include "my.h"
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

static void move_planes_action(plane_t *planes)
{
    float diff_x = planes->dest_x - planes->x;
    float diff_y = planes->dest_y - planes->y;
    float cosinus;

    cosinus = diff_x != 0 ? cos(atan(diff_y / diff_x)) : 0;
    planes->x += planes->speed * cosinus * (diff_x < 0 ? -1 : 1);
    planes->y += planes->speed * (1 - cosinus) * (diff_y < 0 ? -1 : 1);
    sfSprite_setPosition(planes->sprite->sprite, (sfVector2f) {planes->x,
                        planes->y});
    sfRectangleShape_setPosition(planes->hitbox,
                                (sfVector2f) {planes->x, planes->y});
}

void move_planes(plane_t *planes, int seconds)
{
    static int last_seconds = -1;

    if (planes == NULL || seconds <= last_seconds)
        return;
    if (planes->toggle)
        move_planes_action(planes);
    move_planes(planes->next, seconds);
    last_seconds = seconds;
}

static void initialize_planes_data(plane_t *plane)
{
    sfRectangleShape_setFillColor(plane->hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(plane->hitbox, sfBlack);
    sfRectangleShape_setSize(plane->hitbox,
                            (sfVector2f) {PLANE_SIZE, PLANE_SIZE});
    sfRectangleShape_setOutlineThickness(plane->hitbox, PLANE_OUTLINE_SIZE);
}

bool fill_plane_data(plane_t *plane, char *str)
{
    plane->toggle = false;
    plane->sprite_toggle = true;
    plane->speed = get_next_nbr(&str);
    plane->delay = get_next_nbr(&str);
    plane->fuel = get_next_nbr(&str);
    plane->x = get_next_nbr(&str);
    plane->y = get_next_nbr(&str);
    plane->dest_x = get_next_nbr(&str);
    plane->dest_y = get_next_nbr(&str);
    plane->sprite = create_sprite(PLANE_PATH, plane->x, plane->y);
    if (plane->sprite == NULL)
        return true;
    plane->hitbox = sfRectangleShape_create();
    initialize_planes_data(plane);
    return false;
}