/*
** EPITECH PROJECT, 2020
** structure.h
** File description:
** header for struct
*/

#ifndef MUL_MY_RPG_2019_RPG_STRUCTURE_H
#define MUL_MY_RPG_2019_RPG_STRUCTURE_H

#define MOVE_STATIC (0)
#define MOVE_FOLLOW (1)
#define MOVE_RANDOM (2)
#define MOVE_FOLLOW_X (3)

typedef struct sprite_list {
    sfSprite *sprite;
    sfIntRect rect;
    struct sprite_list *next;
} sprite_list_t;

typedef struct animation {
    //sfTexture *texture;
    //sfTexture *mirrored;
    //sfIntRect *rect;
    //sfIntRect *mirrored_rect;
    sfClock *clock;
    int delay;
    int frame;
    int max_frame;
    int is_mirrored;
    int type;
    int is_reverse;
} animation_t;

typedef struct health_bar {
    sfVector2f position;
    sfSprite *background_sprite;
    sfSprite *foreground_sprite;
    sfIntRect foreground_rect;
    double percentage;
} health_bar_t;

typedef struct projectile_list {
    sfSprite *sprite;
    sfVector2f move;
    struct projectile_list *next;
} projectile_list_t;

typedef struct projectile {
    sfVector2f *vectors;
    sfClock *clock;
    double damage;
    double speed;
    projectile_list_t *sprites;
    int is_animated;
    animation_t animation;
    sfIntRect *rects;
    int is_hostile;
} projectile_t;

typedef struct player {
    int state;
    int shoot_state;
    sfIntRect scale;
    animation_t animation;
    sfIntRect **animation_rects;
    sfTexture *texture;
    sfClock *walk_clock;
    sfClock *shot_clock;
    double shot_speed;
    double speed;
    double damage;
    sfSprite *head;
    sfSprite *body;
    sfVector2f move;
    projectile_t projectile;
    sfTexture *projectile_texture;
    int animate_head;
    int max_hp;
    int cur_hp;
    //health_bar_t health_bar;
    sfTexture *health;
    sfIntRect *health_rect;
    sfSprite *heart_sprites[10];
    sfColor og_color_h;
    sfColor og_color_b;
    sfClock * invincibillity_clock;
    double invincibillity_duaration;
    sfText *soul_text;
    int soul_count;
    char *soul_string;
    int soul_gain;
} player_t;

typedef struct enemy_template {
    sfVector2f **projectile_directions_per_shot;
    sfTexture *texture;
    sfIntRect *rects;
    sfIntRect *die_rect;
    sfTexture *die;
    int movement_type;
    double speed;
    double shots_per_second;
    double projectile_speed;
    int projectile_count_per_shot;
    int projectile_count_per_shot_arr[4];
    double max_hp;
    double cur_hp;
    animation_t animation;
    int projectile_formations;
    int next_shot;
    int souls;
} enemy_template_t;

typedef struct enemy {
    projectile_t projectile;
    sfVector2f move;
    int backwards;
    sfSprite *sprite;
    enemy_template_t template;
    sfClock *movement_clock;
    sfClock  *shooting_clock;
    int type;
    health_bar_t health_bar;
    sfColor og_color;
    int is_alive;
    int is_boss;
} enemy_t;

typedef struct enemy_list {
    enemy_t *enemy;
    struct enemy_list *next;
} enemy_list_t;

typedef struct obstacles_template {
    sfTexture *empty;
    sfTexture *wall;
    sfIntRect *obstacle_rect;
    sfTexture **room_backgrounds;
    sfTexture *obstacles;
    sfIntRect *obstacle_rects;
} obstacles_template_t;

typedef struct button
{
    sfIntRect *rects;
    sfText *text;
    char *str;
    sfColor def_color;
    int is_hovered;
    sfSprite *sprite;
    int value;
    int is_confirm;
    int type;
    int is_locked;
    sfVector2f position;
    sfVector2f text_gap;
    sfVector2f gap;
    int nb_end;
} button_t;

typedef struct dialogue_box {
    sfText *text;
    sfSprite *icon_box_sprite;
    sfSprite *icon_background_sprite;
    sfSprite *icon;
    int is_active;
    button_t close;
    button_t talk;
    button_t shop;
    button_t hp;
    button_t speed;
    button_t fire_rate;
    button_t projectile_speed;
    button_t damage;
    button_t back;
    //button_t heal;
    int is_shop;
} dialogue_box_t;

typedef struct npc {
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect icon_rect;
    int type;
    //sfIntRect **rects;
    //animation_t animation;
    dialogue_box_t dialogueBox;
} npc_t;

typedef struct room {
    int visited;
    int is_boss_room;
    int is_marked;
    int directions;
    int width;
    int height;
    int cleared;
    char **arr;
    sfSprite *background_sprite;
    sfIntRect room_shape;
    sprite_list_t *obstacles;
    sprite_list_t *empty_tiles;
    sprite_list_t *souls;
    sfVector2f door_locations[4];
    enemy_list_t *enemies;
    npc_t reaper;
    npc_t statue;
    int is_bossfight;
    sfSprite *trap_door;
    sfSprite *trophy;
} room_t;

typedef struct stats_display {
    sfTexture *texture;
    sfSprite *sprite;
    sfText *text;
    char *str;
    double speed;
    double damage;
    double p_speed;
    double s_speed;
} stats_display_t;

typedef struct all {
    obstacles_template_t room_template;
    room_t *cur_room;
    player_t player;
    sfTexture *enemy_projectile_texture;
    enemy_template_t enemy_templates[7];
    sfTexture *health_bar_foreground;
    sfTexture *health_bar_background;
    sfTexture *soul_texture;
    sfTexture  *x_texture;
    sfSprite  *x_sprite;
    sfFont *basic_font;
    sfIntRect *soul_rect;
    sfSprite *soul_sprite;
    dialogue_box_t  dialogue_box;
    sfTexture *box_back;
    sfTexture *icon_box;
    int is_mouse_held;
    sfTexture *empty_button_texture;
    sfTexture *close_texture;
    sfTexture *die_texture_1;
    sfTexture  *die_texture_2;
    sfIntRect *die_rect;
    sfTexture *drop_door_texture;
    sfTexture *trophy_texture;
    int floor_is_won;
    int credits;
    int cur_floor;
    stats_display_t stats;
} all_t;

#endif //MUL_MY_RPG_2019_RPG_STRUCTURE_H