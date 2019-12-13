/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** my_screensaver .h file
*/

#include <stdbool.h>
#include <SFML/Graphics.h>
#include "graph.h"

#ifndef MY_RADAR_H_
#define MY_RADAR_H_

typedef struct entity_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f position;
} entity_t;

int my_radar(assets_t *assets);

#endif