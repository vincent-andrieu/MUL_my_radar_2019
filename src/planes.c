/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** move planes
*/

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "my_radar.h"
#include "my.h"

static void take_off(plane_t *plane)
{
    sfVector2f scale;

    do {
        scale = sfSprite_getScale(plane->sprite->sprite);
        scale.x--;
        scale.y--;
        sfSprite_setScale(plane->sprite->sprite, scale);
    } while (scale.x > 1 && scale.y > 1);
}

plane_t *destroy_plane(plane_t *origin, plane_t *plane, bool is_take_off)
{
    if (plane->prev != NULL)
        plane->prev->next = plane->next;
    if (plane->next != NULL)
        plane->next->prev = plane->prev;
    if (plane->prev == NULL)
        origin = plane->next;
    if (is_take_off)
        take_off(plane);
    //sfSprite_destroy(plane->sprite->sprite);
    sfRectangleShape_destroy(plane->hitbox);
    sfCircleShape_destroy(plane->circle);
    free(plane);
    return origin;
}

void move_planes(plane_t *planes, int seconds)
{
    static int last_seconds = -1;
    float diff_x;
    float diff_y;
    float cosinus;

    if (planes == NULL || seconds <= last_seconds)
        return;
    diff_x = planes->dest_x - planes->x;
    diff_y = planes->dest_y - planes->y;
    cosinus = diff_x != 0 ? cos(atan(diff_y / diff_x)) : 0;
    planes->x += planes->speed * cosinus * (diff_x < 0 ? -1 : 1);
    planes->y += planes->speed * (1 - cosinus) * (diff_y < 0 ? -1 : 1);
    //sfSprite_setPosition(planes->sprite->sprite, (sfVector2f) {planes->x,
                        //planes->y});
    sfRectangleShape_setPosition(planes->hitbox,
                                (sfVector2f) {planes->x, planes->y});
    move_planes(planes->next, seconds);
    last_seconds = seconds;
}

plane_t *check_planes_delay(plane_t *origin, plane_t *planes, float seconds)
{
    if (planes == NULL)
        return origin;
    origin = check_planes_delay(origin, planes->next, seconds);
    if (seconds >= planes->delay)
        return destroy_plane(origin, planes, false);
    return origin;
}

bool fill_plane_data(plane_t *plane, char *str)
{
    plane->speed = get_next_nbr(&str);
    plane->delay = get_next_nbr(&str);
    plane->x = get_next_nbr(&str);
    plane->y = get_next_nbr(&str);
    plane->dest_x = get_next_nbr(&str);
    plane->dest_y = get_next_nbr(&str);
    plane->sprite = NULL;//create_sprite(PLANE_PATH, plane->x, plane->y);
    /*if (plane->sprite == NULL)
        return true;*/
    plane->hitbox = sfRectangleShape_create();
    plane->circle = sfCircleShape_create();
    sfRectangleShape_setFillColor(plane->hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(plane->hitbox, sfBlack);
    sfRectangleShape_setSize(plane->hitbox,
                            (sfVector2f) {PLANE_SIZE, PLANE_SIZE});
    sfRectangleShape_setOutlineThickness(plane->hitbox, PLANE_OUTLINE_SIZE);
    sfCircleShape_setFillColor(plane->circle, sfTransparent);
    sfCircleShape_setOutlineColor(plane->circle, sfBlack);
    sfCircleShape_setRadius(plane->circle, PLANE_RADIUS);
    return false;
}