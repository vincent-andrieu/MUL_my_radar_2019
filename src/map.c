/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** initialize the map
*/

#include <fcntl.h>
#include <unistd.h>
#include "my.h"
#include "my_radar.h"

float get_next_nbr(char **str)
{
    float result;
    int i = 0;

    for (; (*str)[i] >= '0' && (*str)[i] <= '9'; i++);
    (*str)[i] = '\0';
    result = (float) my_getnbr(*str);
    *str += i + 1;
    return result;
}

static tower_t *add_tower(char *str, tower_t *towers)
{
    tower_t *new = malloc(sizeof(tower_t));

    if (new == NULL)
        return NULL;
    new->x = get_next_nbr(&str);
    new->y = get_next_nbr(&str);
    new->radius = get_next_nbr(&str);
    new->circle = sfCircleShape_create();
    new->sprite = create_sprite(TOWER_PATH, new->x + new->radius - 10,
                                            new->y + new->radius - 10);
    if (new->sprite == NULL)
        return NULL;
    new->sprite_toggle = true;
    sfCircleShape_setPosition(new->circle, (sfVector2f) {new->x, new->y});
    sfCircleShape_setOutlineColor(new->circle, sfBlack);
    sfCircleShape_setFillColor(new->circle, sfTransparent);
    sfCircleShape_setOutlineThickness(new->circle, TOWER_OUTLINE_SIZE);
    sfCircleShape_setRadius(new->circle, new->radius);
    new->next = towers;
    return new;
}

static plane_t *add_plane(char *str, plane_t *planes)
{
    plane_t *new = malloc(sizeof(plane_t));

    if (new == NULL)
        return NULL;
    if (fill_plane_data(new, str))
        return NULL;
    new->next = planes;
    new->prev = NULL;
    if (new->next != NULL)
        new->next->prev = new;
    return new;
}

static entities_t *get_map(int fd)
{
    char *str = get_next_line(fd);
    entities_t *entities = malloc(sizeof(entities_t));

    if (entities == NULL)
        return NULL;
    entities->towers = NULL;
    entities->planes = NULL;
    while (str) {
        if (str[0] == CHAR_PLANE)
            entities->planes = add_plane(str + 2, entities->planes);
        else if (str[0] == CHAR_TOWER)
            entities->towers = add_tower(str + 2, entities->towers);
        else
            return NULL;
        free(str);
        str = get_next_line(fd);
    }
    return entities;
}

entities_t *read_map(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    entities_t *map = fd <= 0 ? NULL : get_map(fd);

    if (fd <= 0) {
        my_put_error_str(MSG_SCRIPT_ERROR);
        return NULL;
    }
    if (map == NULL)
        my_put_error_str(MSG_SCRIPT_ERROR);
    close(fd);
    return map;
}