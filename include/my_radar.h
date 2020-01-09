/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** my_screensaver .h file
*/

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "graph.h"

#ifndef MY_RADAR_H_
#define MY_RADAR_H_

#define MSG_INVALID_ARG_NBR "Invalid arguments number\n"
#define EXIT_INVALID_ARG_NBR 84
#define MSG_SCRIPT_ERROR "Script error\n"
#define EXIT_ERROR 84
#define CLOCK_POS {WINDOW_WIDTH - 90, 15}
#define FONT_PATH "resource/LemonMilk.otf"
#define BACKGROUND_PATH "resource/background.png"
#define TOWER_PATH "resource/tower.png"
#define PLANE_PATH "resource/plane.png"
#define CHAR_TOWER 'T'
#define TOWER_OUTLINE_SIZE 2.0
#define CHAR_PLANE 'P'
#define PLANE_SIZE 20
#define PLANE_RADIUS sqrt(PLANE_SIZE * PLANE_SIZE - 70)
#define PLANE_OUTLINE_SIZE 2.0
#define CRASH_FUEL_ANIM false
#define CRASH_SPEED_ANIM 0.1

typedef struct sprite_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f position;
} sprite_t;

typedef struct tower_s
{
    sprite_t *sprite;
    bool sprite_toggle;
    sfCircleShape *circle;
    float x;
    float y;
    float radius;
    struct tower_s *next;
} tower_t;

typedef struct plane_s
{
    bool toggle;
    sprite_t *sprite;
    bool sprite_toggle;
    sfRectangleShape *hitbox;
    float x;
    float y;
    float dest_x;
    float dest_y;
    float speed;
    float delay;
    float fuel;
    struct plane_s *next;
    struct plane_s *prev;
} plane_t;

typedef struct entities_s
{
    tower_t *towers;
    plane_t *planes;
} entities_t;

bool does_kill_prog(assets_t *assets, entities_t *entities);
int my_radar(assets_t *assets, char *map_path);
int usage(int exit_value, char *binary_name);
sprite_t *create_sprite(char *filepath, float x, float y);
entities_t *read_map(char *filepath);
void initialize_font(sfText *txt, sfFont *font);
void toggle_hitboxes(plane_t *planes);
void toggle_sprites(plane_t *planes, tower_t *towers);
void draw_towers(assets_t *assets, tower_t *towers);
void draw_planes(sfRenderWindow *window, plane_t *planes);
void draw_clock(sfRenderWindow *window, sfClock *clock, sfText *txt);
void move_planes(plane_t *planes, int seconds);
plane_t *check_planes_times(plane_t *planes, float seconds, assets_t *assets);
void destroy_all(entities_t *entities, sfClock *clock,
                sfText *txt, sfFont *font);
float get_next_nbr(char **str);
bool fill_plane_data(plane_t *planes, char *str);
plane_t *destroy_plane(plane_t *origin, plane_t *plane, bool is_take_off,
                        assets_t *assets);
plane_t *check_collisions(plane_t *planes_origin, plane_t *planes,
                        tower_t *towers);
void take_off(plane_t *plane, assets_t *assets);

#endif