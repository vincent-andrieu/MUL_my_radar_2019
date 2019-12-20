/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** my_screensaver .h file
*/

#include <stdbool.h>
#include <stdbool.h>
#include "graph.h"

#ifndef MY_RADAR_H_
#define MY_RADAR_H_

#define MSG_INVALID_ARG_NBR "Invalid arguments number\n"
#define EXIT_INVALID_ARG_NBR 84
#define MSG_SCRIPT_ERROR "Script error\n"
#define EXIT_ERROR 84
#define BACKGROUND_PATH "resource/background.png"
#define TOWER_PATH "resource/tower.png"
#define TOWER_HITBOX_PATH "resource/circle.png"
#define PLANE_PATH "resource/plane.png"
#define PLANE_HITBOX_PATH "resource/square.png"
#define CHAR_TOWER 'T'
#define CHAR_PLANE 'P'
#define CLOCK_POS {WINDOW_WIDTH - 90, 15}
#define FONT_PATH "resource/LemonMilk.otf"

typedef struct sprite_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f position;
} sprite_t;

typedef struct tower_s
{
    sprite_t *sprite;
    float x;
    float y;
    float radius;
    struct tower_s *next;
} tower_t;

typedef struct plane_s
{
    sprite_t *sprite;
    sprite_t *hitbox;
    float x;
    float y;
    float dest_x;
    float dest_y;
    float speed;
    float delay;
    struct plane_s *next;
    struct plane_s *prev;
} plane_t;

typedef struct entities_s
{
    tower_t *towers;
    plane_t *planes;
} entities_t;

bool does_kill_prog(assets_t *assets);
int my_radar(assets_t *assets, char *map_path);
int usage(int exit_value, char *binary_name);
sprite_t *create_sprite(char *filepath, float x, float y);
entities_t *read_map(char *filepath);
void initialize_font(sfText *txt, sfFont *font);
void toggle_hitboxes(assets_t *assets);
void toggle_sprites(void);
void draw_towers(assets_t *assets, tower_t *towers);
void draw_planes(sfRenderWindow *window, plane_t *planes);
void draw_clock(sfRenderWindow *window, sfClock *clock, sfText *txt);
void move_planes(plane_t *planes, int seconds);
bool check_planes_delay(plane_t *planes, float seconds);
void destroy_all(entities_t *entities, sfClock *clock,
                sfText *txt, sfFont *font);

#endif