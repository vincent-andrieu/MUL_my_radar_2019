/*
** EPITECH PROJECT, 2019
** CSFML
** File description:
** display an image in a window
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <fcntl.h>
#include <time.h>
#include "my.h"
#include "graph.h"
#include "my_radar.h"

int does_kill_prog(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed || (event.type == sfEvtKeyReleased
        && event.key.code == sfKeyEscape)) {
            sfRenderWindow_close(window);
            return 0;
        }
    }
    return 1;
}

static void clear_screen(assets_t *assets)
{
    for (unsigned int i = 0;
    i < assets->framebuffer->width * assets->framebuffer->height * 4; i++)
        assets->framebuffer->pixels[i] = 0;
}

static void show_window(assets_t *assets)
{
    sfEvent event;

    srand(time(NULL));
    printf("%d\n", bootstrap(assets));
    while (sfRenderWindow_pollEvent(assets->window, &event))
        if (event.type == sfEvtClosed
        || event.key.code == sfKeyEscape)
            sfRenderWindow_close(assets->window);
    clear_screen(assets);
    sfTexture_updateFromPixels(assets->texture, assets->framebuffer->pixels,
                                WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
    sfRenderWindow_clear(assets->window, sfBlack);
    sfRenderWindow_drawSprite(assets->window, assets->sprite, NULL);
    sfRenderWindow_display(assets->window);
}

int prepare_window(void)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    assets_t *assets = malloc(sizeof(assets_t));
    assets->window = sfRenderWindow_create(mode, "MyScreensaver",
                                            sfResize | sfClose, NULL);
    assets->texture = sfTexture_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    assets->sprite = sfSprite_create();
    assets->framebuffer = framebuffer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (assets->window == NULL || assets->texture == NULL)
        return EXIT_FAILURE;
    sfSprite_setTexture(assets->sprite, assets->texture, sfTrue);
    sfRenderWindow_setFramerateLimit(assets->window, 30);
    while (sfRenderWindow_isOpen(assets->window))
        show_window(assets);
    framebuffer_destroy(assets->framebuffer);
    sfSprite_destroy(assets->sprite);
    sfTexture_destroy(assets->texture);
    sfRenderWindow_destroy(assets->window);
    free(assets);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    return prepare_window();
}