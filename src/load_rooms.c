/*
** EPITECH PROJECT, 2020
** load_rooms.c
** File description:
** loads rooms
*/

#include "../include/rpg.h"

void handle_room_clear(enemy_list_t *enemies, all_t *objects)
{
    if (DEBUG || map[curr_room_x][curr_room_y]->cleared)
        return;
    /*if (map[curr_room_x][curr_room_y]->is_boss_room && objects->cur_room->is_bossfight && !enemies->next->enemy->is_boss) {
        for (enemy_list_t *temp = enemies->next; temp; temp = temp->next) {
            temp->enemy->template.cur_hp = -20;
            refresh_enemy_health_bar(temp->enemy, objects, temp->enemy->template.cur_hp, temp->enemy->template.max_hp);
        }
    }*/
    if (enemies->next == NULL) {
        if (map[curr_room_x][curr_room_y]->is_boss_room && objects->cur_room->is_bossfight) {
            objects->floor_is_won = 1;
        }
        map[curr_room_x][curr_room_y]->cleared = 1;
        for (int i = 0; i < objects->player.soul_gain; i++) {
            add_points(objects->player.soul_string, 3);
        }
        objects->player.soul_count += objects->player.soul_gain;
        objects->player.soul_gain = 0;
        for (int i = 5; i < 8; i++)
            objects->player.soul_string[i] = '0';
        sfText_setString(objects->player.soul_text,
            objects->player.soul_string);
    }
}

int get_player_leave_direction(player_t *player, room_t *cur_room)
{
    sfVector2f pos_player = sfSprite_getPosition(player->body);
    sfVector2f pos_floor = sfSprite_getPosition(cur_room->background_sprite);

    if (pos_player.x < pos_floor.x - 10 || (pos_player.x == cur_room->door_locations[1].x && pos_player.y >= cur_room->door_locations[1].y - 5 && pos_player.y <= cur_room->door_locations[1].y + 5))
        return (LEFT);
    if (pos_player.x > pos_floor.x + (cur_room->width - 1) * 100 + 10 || (pos_player.x == cur_room->door_locations[2].x && pos_player.y >= cur_room->door_locations[2].y - 5 && pos_player.y <= cur_room->door_locations[2].y + 5))
        return (RIGHT);
    if (pos_player.y < pos_floor.y - 10 || (pos_player.x >= cur_room->door_locations[0].x - 5 && pos_player.x <= cur_room->door_locations[0].x + 5 && pos_player.y - 5 == cur_room->door_locations[0].y))
        return (UP);
    if (pos_player.y > pos_floor.y + (cur_room->height -1) * 100 + 10 || (pos_player.x >= cur_room->door_locations[3].x - 5 && pos_player.x <= cur_room->door_locations[3].x + 5 && pos_player.y == cur_room->door_locations[3].y))
        return (DOWN);
    return (0);
}

void remove_prev_room_objects(all_t *objects) //todo: actually clean up everything!
{
    objects->player.projectile.sprites->next = NULL;
}

int load_room(all_t *objects, int direction)
{
    sfVector2f start = {1920 / 2, 1080 / 2};

    if (!direction)
        return (-2);
    room_t *room = get_room_struct(direction);
    sfIntRect room_rect = { 0, 0, 0, 0};
    sfVector2f position = {0, 0};
    if (!room)
        return (-1);
    room_rect.width = room->width * 100 - 10;
    room_rect.height = room->height * 100 - 45;
    for (; position.x < 1920 && position.x != 1920 - \
(position.x + room->width * 100); position.x++);
    for (; position.y < 1030 && position.y != 1030 - \
    (position.y + room->height * 100); position.y++);
    if (room->width > 19 || room->height > 10)
        return (-1);
    remove_prev_room_objects(objects);
    sfSprite_setPosition(objects->player.body, start);
    sfSprite_setPosition(objects->player.head, start);
    objects->dialogue_box.is_active = 0;
    objects->dialogue_box.is_shop = 0;
    objects->player.soul_gain = 0;
    for (int i = 5; i < 8; i++)
        objects->player.soul_string[i] = '0';
    sfText_setString(objects->player.soul_text, objects->player.soul_string);
    objects->cur_room->width = room->width;
    objects->cur_room->height = room->height;
    objects->cur_room->arr = room->arr;
    objects->cur_room->room_shape = room_rect;
    if (!objects->floor_is_won)
        objects->cur_room->is_bossfight = 0;
    sfSprite_setTextureRect(objects->cur_room->background_sprite, room_rect);
    position.x += 5;
    sfSprite_setPosition(objects->cur_room->background_sprite, position);
    free(room);
    place_obstacles(objects->cur_room, &objects->room_template, direction, &objects->player, objects);
    if (!DEBUG)
        map[curr_room_x][curr_room_y]->visited = 1;
    return (0);
}

room_t *get_room_struct(int direction)
{
    room_t *room = malloc(sizeof(room_t));
    int test_width = 0;

    room->arr = get_room_arr(direction);

    for (room->width = 0; room->arr[0][room->width] && room->arr[0][room->width] != '\n'; room->width++);
    for (room->height = 0; room->arr[room->height]; room->height++) {
        my_printf("%s\n", room->arr[room->height]);
        //for (test_width = 0; room->arr[room->height][test_width]; test_width++);
        /*if (test_width != room->width)
            return (NULL);*/
    }
    return (room);
}

char **get_room_arr(int direction)
{
    if (DEBUG) {
        size_t size;
        FILE *stream = fopen("test", "r");
        char **result = malloc(sizeof(char *) * 10);
        for (int i = 0;; i++) {
            result[i] = NULL;
            char *line = NULL;
            if (getline(&line, &size, stream) == -1)
                break;
            result[i] = line;
        }
        return (result);
    }
    set_next_coordinates(&curr_room_x, &curr_room_y, direction);
    if (map == 0)
        init_map();
    if (curr_room_x < 0)
        curr_room_x = 0;
    if (curr_room_y < 0)
        curr_room_y = 0;
    if (curr_room_x > MAP_WIDTH - 1)
        curr_room_x = MAP_WIDTH - 1;
    if (curr_room_y > MAP_HEIGHT - 1)
        curr_room_y = MAP_HEIGHT - 1;
    return map[curr_room_x][curr_room_y]->arr;
}


void place_obstacles(room_t *room, obstacles_template_t *template, int direction, player_t *player, all_t *objects)
{
    sfVector2f position = sfSprite_getPosition(room->background_sprite);
    position.x -= 5;
    sfVector2f mid = {1920 / 2, 1080 / 2};
    //position.x += 95, position.y += 100;
    //sfVector2f wall_position = position;
    sfVector2f og_position = position;
    room->enemies = create_enemy_list();

    for (int i = 0; i < 4; i++) {
        room->door_locations[i].x = -1000;
        room->door_locations[i].y = -1000;
    }
    //wall_position.x -= 100;
    //wall_position.y -= 100;
    room->obstacles = malloc(sizeof(sprite_list_t));
    room->empty_tiles = malloc(sizeof(sprite_list_t));
    /*room->obstacles->sprite = sfSprite_create();
    sfSprite_setTexture(room->obstacles->sprite, template->wall, sfTrue);
    sfSprite_setTextureRect(room->obstacles->sprite, template->obstacle_rect[0]);
    sfSprite_setPosition(room->obstacles->sprite, wall_position);
    room->obstacles->rect = sfSprite_getTextureRect(room->obstacles->sprite);*/
    sprite_list_t *head = room->obstacles;
    sprite_list_t *head_2 = room->empty_tiles;

    //place_given_obstacle(room, wall_position, template->obstacle_rect[0], template->wall);
    /*for (int i = 1; i < room->width; i++) {
        wall_position.x += 100;
        if (room->arr[0][i] != '-')
            place_given_obstacle(room, wall_position,  template->obstacle_rect[1], template->wall);
        else if (direction == DOWN) {
            sfSprite_setPosition(player->body, wall_position);
            sfSprite_setPosition(player->head, wall_position);
        }
    }*/
    //place_given_obstacle(room, wall_position,  template->obstatic int is_pressed = 0;
    for (int i = 0; i < room->height; i++) {
        position.x = og_position.x;
        //wall_position = position;
        //wall_position.x -= 100;
        /*if (room->arr[i][0] != '|')
            place_given_obstacle(room, position,  template->obstacle_rect[3], template->wall);*/
        for (int j = 0; j < room->width; j++) {
            if ((direction == RIGHT && room->arr[i][j] == '~') || (direction == LEFT &&  room->arr[i][j] == '=') || (direction == DOWN &&  room->arr[i][j] == '!') || (direction == UP &&  room->arr[i][j] == '?')) {
                sfSprite_setPosition(player->body, position);
                sfSprite_setPosition(player->head, position);
            }
            if (room->arr[i][j] >= '0' && room->arr[i][j] <= '8')
                place_given_obstacle(room, position, template->obstacle_rect[room->arr[i][j] - '0'], template->obstacles);
            switch (room->arr[i][j]) {
            case '/':
                place_given_obstacle(room, position,  template->obstacle_rect[0], template->wall);
                break;
            case '-':
                place_given_obstacle(room, position,  template->obstacle_rect[1], template->wall);
                break;
            case '\\':
                place_given_obstacle(room, position,  template->obstacle_rect[2], template->wall);
                break;
            case '[':
                place_given_obstacle(room, position,  template->obstacle_rect[3], template->wall);
                break;
            case ']':
                place_given_obstacle(room, position,  template->obstacle_rect[5], template->wall);
                break;
            case '(':
                place_given_obstacle(room, position,  template->obstacle_rect[6], template->wall);
                break;
            case '_':
                place_given_obstacle(room, position,  template->obstacle_rect[7], template->wall);
                break;
            case ')':
                place_given_obstacle(room, position,  template->obstacle_rect[8], template->wall);
                break;
            default:
                break;
            }
            if (room->arr[i][j] == '.') {
                room->empty_tiles->next = malloc(sizeof(sprite_list_t));
                room->empty_tiles = room->empty_tiles->next;
                room->empty_tiles->sprite = sfSprite_create();
                sfSprite_setTexture(room->empty_tiles->sprite, template->empty, sfTrue);
                sfSprite_setPosition(room->empty_tiles->sprite, position);
            }
            switch (room->arr[i][j]) {
            case '!':
                room->door_locations[0] = position;
                room->door_locations[0].y -= 25;
                break;
            case '~':
                room->door_locations[1] = position;
                room->door_locations[1].x -= 25;
                break;
            case '=':
                room->door_locations[2] = position;
                room->door_locations[2].x += 125;
                break;
            case '?':
                room->door_locations[3] = position;
                room->door_locations[3].y += 25;
                break;
            default:
                break;
            }
            if (room->arr[i][j] >= 'a' && room->arr[i][j] <= 'f' && (DEBUG || !map[curr_room_x][curr_room_y]->cleared)) {
                append_to_list(room->enemies, create_enemy(objects->enemy_templates, room->arr[i][j] - 'a', position, objects, 0));
            }
            if (room->arr[i][j] >= 'A' && room->arr[i][j] <= 'D' && (DEBUG || !map[curr_room_x][curr_room_y]->cleared)) {
                append_to_list(room->enemies,
                    create_enemy(objects->enemy_templates,
                        room->arr[i][j] - 'A', position, objects, 1));
            }
            //    place_given_obstacle(room->empty_tiles, position, template->obstacle_rect[0], template->empty);
            position.x += 100;
        }
        position.y += 100;
    }
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_marked) {
        sfSprite_setPosition(objects->cur_room->reaper.sprite, mid);
    }
    /*position = position;
    position.x = og_position.x;
    position.x -= 100;
    place_given_obstacle(room, position, template->obstacle_rect[6], template->wall);
    for (int i = 1; i < room->width; i++) {
        position.x += 100;
        if (room->arr[room->height - 1][i] != '-')
            place_given_obstacle(room, position,  template->obstacle_rect[7], template->wall);
        else if (direction == UP) {
            sfSprite_setPosition(player->body, position);
            sfSprite_setPosition(player->head, position);
        }
    }
    place_given_obstacle(room, position,  template->obstacle_rect[8], template->wall);*/
    room->obstacles->next = NULL;
    room->obstacles = head;
    room->empty_tiles->next = NULL;
    room->empty_tiles = head_2;
}

void place_given_obstacle(room_t *room, sfVector2f position, sfIntRect rect, sfTexture *texture)
{
    room->obstacles->next = malloc(sizeof(sprite_list_t));
    room->obstacles = room->obstacles->next;
    room->obstacles->sprite = sfSprite_create();
    sfSprite_setTexture(room->obstacles->sprite, texture, sfTrue);
    sfSprite_setTextureRect(room->obstacles->sprite, rect);
    sfSprite_setPosition(room->obstacles->sprite, position);
    //room->obstacles->rect = sfSprite_getTextureRect(room->obstacles->sprite);
}