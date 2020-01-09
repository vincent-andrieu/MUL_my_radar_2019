/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** move planes
*/

#include <math.h>
#include "my.h"
#include "my_radar.h"

static void check_out_from_map(plane_t *plane)
{
    if (plane->x + PLANE_SIZE <= 0)
        plane->x = WINDOW_WIDTH - 1;
    else if (plane->x >= WINDOW_WIDTH)
        plane->x = -PLANE_SIZE + 1;
    if (plane->y + PLANE_SIZE <= 0)
        plane->y = WINDOW_HEIGHT - 1;
    else if (plane->y >= WINDOW_HEIGHT)
        plane->y = -PLANE_SIZE + 1;
}

static void move_planes_action(plane_t *planes,
                                float seconds, float last_seconds)
{
    float diff_x = planes->dest_x - planes->x;
    float diff_y = planes->dest_y - planes->y;
    float cosinus;

    cosinus = diff_x != 0 ? cos(atan(diff_y / diff_x)) : 0;
    planes->x += (seconds - last_seconds)
                * (planes->speed * cosinus * (diff_x < 0 ? -1 : 1));
    planes->y += (seconds - last_seconds)
                * (planes->speed * (1 - cosinus) * (diff_y < 0 ? -1 : 1));
    sfSprite_setPosition(planes->sprite->sprite, (sfVector2f) {planes->x,
                        planes->y});
    sfRectangleShape_setPosition(planes->hitbox,
                                (sfVector2f) {planes->x, planes->y});
}

void move_planes(plane_t *planes, float seconds)
{
    static float last_seconds = 0;

    if (planes == NULL)
        return;
    if (planes->toggle)
        move_planes_action(planes, seconds, last_seconds);
    check_out_from_map(planes);
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