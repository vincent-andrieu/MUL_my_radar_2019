/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** manage planes time
*/

#include "my_radar.h"

static void spawn_planes(plane_t *planes, float seconds)
{
    if (planes == NULL)
        return;
    if (seconds >= planes->delay && !planes->toggle)
        planes->toggle = true;
    spawn_planes(planes->next, seconds);
}

static plane_t *check_planes_fuel(plane_t *origin, plane_t *planes,
                                    float seconds)
{
    if (planes == NULL)
        return origin;
    origin = check_planes_fuel(origin, planes->next, seconds);
    if (seconds >= planes->delay + planes->fuel)
        return destroy_plane(origin, planes);
    return origin;
}

plane_t *check_planes_times(plane_t *planes, float seconds)
{
    spawn_planes(planes, seconds);
    return check_planes_fuel(planes, planes, seconds);
}