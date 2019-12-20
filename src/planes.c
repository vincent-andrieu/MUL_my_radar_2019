/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** move planes and check collision between them
*/

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "my_radar.h"

static bool destroy_plane(plane_t *plane)
{
    bool is_exit = false;

    if (plane->prev != NULL)
        plane->prev->next = plane->next;
    if (plane->next != NULL)
        plane->next->prev = plane->prev;
    is_exit = plane->prev == NULL && plane->next == NULL;
    //sfSprite_destroy(plane->sprite->sprite);
    sfSprite_destroy(plane->hitbox->sprite);
    free(plane);
    return is_exit;
}

void move_planes(plane_t *planes, int seconds)
{
    static int last_seconds = 0;
    float diff_x;
    float diff_y;
    float cosinus;

    if (planes == NULL || seconds <= last_seconds)
        return;
    last_seconds = seconds;
    diff_x = planes->dest_x - planes->x;
    diff_y = planes->dest_y - planes->y;
    cosinus = diff_x != 0 ? cos(atan(diff_y / diff_x)) : 0;
    planes->x += planes->speed * cosinus * (diff_x < 0 ? -1 : 1);
    planes->y += planes->speed * (1 - cosinus) * (diff_y < 0 ? -1 : 1);
    //sfSprite_setPosition(planes->sprite->sprite, (sfVector2f) {planes->x, planes->y});
    sfSprite_setPosition(planes->hitbox->sprite, (sfVector2f) {planes->x, planes->y});
    move_planes(planes->next, seconds);
}

bool check_planes_delay(plane_t *planes, float seconds)
{
    if (planes == NULL)
        return false;
    check_planes_delay(planes->next, seconds);
    if (seconds >= planes->delay)
        return destroy_plane(planes);
    return false;
}