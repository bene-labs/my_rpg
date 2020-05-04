/*
** EPITECH PROJECT, 2020
** rpg.h
** File description:
** header
*/

#ifndef MUL_MY_RPG_2019_RPG_H
#define MUL_MY_RPG_2019_RPG_H
#define DEBUG (0)
#define SOUL_START (0)
#define LEFT (2)
#define RIGHT (3)
#define UP (5)
#define DOWN (7)
#define NONE (11)
#define MAP_WIDTH (7)
#define MAP_HEIGHT (7)
#define S_SPEED (2.5)
#define P_SPEED (444.44)
#define SPEED (666.6)
#define DAMAGE (6.66)
#define HP (8)
#define SEC (1000000)

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Config.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include "rpg_structure.h"
#include "my.h"

room_t ***map;
int curr_room_x;
int curr_room_y;
void set_next_coordinates(int *delta_x, int *delta_y, int direction);
void change_room(all_t *objects, int direction);
void init_map(void);
all_t *create_objects(void);
void create_player_objects(all_t *objects);
void handle_game_loop(sfRenderWindow *window, all_t *objects);
void handle_events(sfRenderWindow *window, all_t *objects, sfEvent event);
void draw_sprites(sfRenderWindow *window, all_t *objects);
int load_room(all_t *objects, int direction);
room_t *get_room_struct(int direction);
char **get_room_arr(int dir);
char *concat_strings(char *str1, char *str2);
void add_points(char *score, int i);
void remove_points(char *score, int i);
char *int_to_str(int nb);
void move_player(player_t *player, room_t *cur_room, all_t *objects);
sfIntRect *get_rect_arr(int columns, int rows, int width, int height);
sfIntRect *get_rect_arr_mirrored(int columns, int rows, int width, int height);
void animate_player(sfIntRect *rect, sfIntRect *shot_rect, animation_t *animation, player_t player);
void move_projectile(projectile_t *projectile, room_t *cur_room, all_t *objects);
void shoot_projectile(player_t *player, projectile_t *projectile, projectile_list_t *sprites);
void animate_projectile(projectile_t *projectile, animation_t *animation);
void create_room_objects(all_t *objects);
void place_obstacles(room_t *room, obstacles_template_t *template, int direction, player_t *player, all_t *objects);
void handle_obstacle(room_t *cur_room, player_t *player, sfVector2f backwards, int is_switch, all_t *objects);
void place_given_obstacle(room_t *room, sfVector2f position, sfIntRect rect, sfTexture *texture);
int get_player_leave_direction(player_t *player, room_t *cur_room);
enemy_list_t *create_enemy_list(void);
void append_to_list(enemy_list_t *list, enemy_t *enemy);
void remove_enemy_from_list(enemy_list_t *list, enemy_t *to_remove);
void create_enemy_templates(all_t *objects);
enemy_t *create_enemy(enemy_template_t *template, int type, sfVector2f position, all_t *objects, int is_prime);
void move_enemies_by_their_vector(enemy_list_t *enemies, player_t *player, room_t *cur_room, all_t *objects);
int is_colision_between_two_sprites(sfSprite *first, sfSprite *second, double x_gap, double y_gap);
void animate_enemies(enemy_list_t *enemies, all_t *objects);
void create_enemy_projectile(enemy_t *enemy, projectile_list_t *sprites,
    all_t *objects, int by_force
);
void draw_minimap(sfRenderWindow *window);
void refresh_enemy_health_bar(enemy_t *enemy, all_t *objects, double cur_hp, double max_hp);
void refresh_player_lives(player_t *player);
void remove_prev_room_objects(all_t *objects);
void handle_room_clear(enemy_list_t *enemies, all_t *objects);
void create_objects_text(all_t *objects);
void create_npc_objects(all_t *objects);
void prepare_dialogue_box(all_t *objects, char *str, sfVector2f position, dialogue_box_t *dialogueBox, npc_t *npc);
int is_collision_cursor_button(sfVector2i pos_cursor, sfVector2f pos_button, int height, int width);
int check_button_interaction(button_t *button, sfRenderWindow *window, int height, int width);
int get_random_int_within_range(int min, int max);
int set_seed_if_file_is_valid(FILE *file);
int search_for_seed(void);
char *my_strcpy(char const *str);
void handle_shop_purchase(dialogue_box_t *dialogue_box, player_t *player, button_t *button, all_t *objects);
int is_sprite_inside_radius(sfSprite *sprite, double radius, int origin_x, int origin_y);
void init_boss_fight(all_t *objects, room_t *room);
void credits(sfRenderWindow *window);
void update_stats(player_t *player, stats_display_t *stats);
#endif //MUL_MY_RPG_2019_RPG_H