/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** my_radar clock
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include <my_radar.h>

static char *my_float_get_str(float nbr)
{
    int inbr = (int) nbr;
    float fnbr = nbr - (float) inbr;
    char *temp = my_nbr_get_str(inbr);
    char *str = my_strndup(temp, my_strlen(temp) + 4);
    int i = 0;

    free(temp);
    for (; str[i] != '\0'; i++);
    str[i] = '.';
    str[i + 1] = '\0';
    temp = my_nbr_get_str((int) (fnbr * 100));
    my_strcat(str, temp);
    if (fnbr * 100 < 10) {
        for (; str[i] != '\0'; i++);
        str[i] = '0';
        str[i + 1] = '\0';
    }
    free(temp);
    return str;
}

void draw_clock(sfRenderWindow *window, sfClock *clock, sfText *txt)
{
    char *clock_str = my_float_get_str(sfTime_asSeconds(
                sfClock_getElapsedTime(clock)));

    sfText_setString(txt, clock_str);
    free(clock_str);
    sfRenderWindow_drawText(window, txt, NULL);
}

void initialize_font(sfText *txt, sfFont *font)
{
    sfText_setFont(txt, font);
    sfText_setPosition(txt, (sfVector2f) CLOCK_POS);
    sfText_setColor(txt, sfBlack);
}