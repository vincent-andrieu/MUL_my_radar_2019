/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** check planes
*/

#include "my_radar.h"

void check_out_from_map(plane_t *plane)
{
    if (plane == NULL)
        return;
    if (plane->x <= 0)
        plane->x = WINDOW_WIDTH - 1;
    else if (plane->x >= WINDOW_WIDTH)
        plane->x = 1;
    if (plane->y <= 0)
        plane->y = WINDOW_HEIGHT - 1;
    else if (plane->y >= WINDOW_HEIGHT)
        plane->y = 1;
}

plane_t *check_planes_at_dest(plane_t *origin, plane_t *planes,
                            sfVector2f const speed, assets_t *assets)
{
    if (is_circle_collision(
    (sfVector2f) {planes->x + speed.x, planes->y + speed.y}, (sfVector2f)
    {planes->dest_x, planes->dest_y}, PLANE_RADIUS, PLANE_DEST_RADIUS))
        return destroy_plane(origin, planes, LAND_ANIM, assets);
    return origin;
}