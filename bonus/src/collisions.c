/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** check collision between them
*/

#include "my_radar.h"

static bool is_plane_collision(sfVector2f pos1, sfVector2f pos2)
{
    return (pos1.y >= pos2.y && pos1.y <= pos2.y + PLANE_SIZE)
            && ((pos1.x >= pos2.x && pos1.x <= pos2.x + PLANE_SIZE)
                || (pos1.x + PLANE_SIZE >= pos2.x
                    && pos1.x + PLANE_SIZE <= pos2.x + PLANE_SIZE));
}

bool is_circle_collision(sfVector2f pos1, sfVector2f pos2,
                                float radius1, float radius2)
{
    pos1.x += radius1 / 2;
    pos1.y += radius1 / 2;
    pos2.x += radius2 / 2;
    pos2.y += radius2 / 2;
    return (pos1.x - pos2.x) * (pos1.x - pos2.x)
    + (pos1.y - pos2.y) * (pos1.y - pos2.y)
    <= (radius1 + radius2) * (radius1 + radius2);
}

static plane_t *check_plane_collisions(plane_t *origin,
                                        plane_t *list, plane_t *plane)
{
    if (list == NULL || plane == NULL)
        return origin;
    if (list != plane && is_plane_collision((sfVector2f) {list->x, list->y},
                                        (sfVector2f) {plane->x, plane->y})) {
        origin = destroy_plane(origin, list);
        origin = destroy_plane(origin, plane);
        return origin;
    }
    return check_plane_collisions(origin, list->next, plane);
}

static bool is_plane_in_tower(plane_t *plane, tower_t *towers)
{
    if (plane == NULL || towers == NULL)
        return false;
    if (is_circle_collision((sfVector2f) {plane->x, plane->y},
                            (sfVector2f) {towers->x, towers->y},
                            PLANE_RADIUS, towers->radius))
        return true;
    return is_plane_in_tower(plane, towers->next);
}

plane_t *check_collisions(plane_t *planes_origin,
                    plane_t *planes, tower_t *towers)
{
    if (towers == NULL || planes == NULL)
        return planes_origin;
    if (!is_plane_in_tower(planes, towers))
        planes_origin = check_plane_collisions(planes_origin, planes_origin,
                                                planes);
    return check_collisions(planes_origin, planes->next, towers);
}