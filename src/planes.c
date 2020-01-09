/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** move planes
*/

#include <math.h>
#include "my.h"
#include "my_radar.h"

static void move_planes_action(plane_t *planes, sfVector2f const speed)
{
    planes->x += speed.x;
    planes->y += speed.y;
    sfSprite_setPosition(planes->sprite->sprite,
                        (sfVector2f) {planes->x, planes->y});
    sfRectangleShape_setPosition(planes->hitbox,
                                (sfVector2f) {planes->x, planes->y});
}

static sfVector2f get_plane_speed(plane_t *plane, float const speed_diff)
{
    sfVector2f const coord_diff = {plane->dest_x - plane->x,
                                plane->dest_y - plane->y};
    float const cosinus = coord_diff.x != 0
                        ? cos(atan(coord_diff.y / coord_diff.x)) : 0;

    return (sfVector2f const) {
        speed_diff * (plane->speed * cosinus * (coord_diff.x < 0 ? -1 : 1)),
        speed_diff * (plane->speed * (1 - cosinus) * (coord_diff.y < 0 ? -1 : 1))
    };
}

plane_t *move_planes(plane_t *origin, plane_t *planes,
                    float seconds)
{
    static float last_seconds = 0;
    sfVector2f const speed = planes != NULL && planes->toggle
        ? get_plane_speed(planes, seconds - last_seconds) : (sfVector2f) {0, 0};

    if (planes == NULL)
        return origin;
    if (planes->toggle)
        move_planes_action(planes, speed);
    check_out_from_map(planes);
    if (planes->next != NULL)
        origin = move_planes(origin, planes->next, seconds);
    origin = check_planes_at_dest(origin, planes, speed);
    last_seconds = seconds;
    return origin;
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