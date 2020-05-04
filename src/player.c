//
// Created by benedikt on 4/26/20.
//

#include "../include/rpg.h"

void animate_player(sfIntRect *rect, sfIntRect *shot_rect, animation_t *animation, player_t player)
{
    if (player.state == -1 || sfClock_getElapsedTime(animation->clock).microseconds < 40000000 / player.speed)
        return;
    sfClock_restart(animation->clock);
    if (!animation->is_reverse) {
        if (animation->frame > animation->max_frame)
            animation->frame = 0;
        sfSprite_setTextureRect(player.body, rect[animation->frame]);
        if (player.animate_head)
            sfSprite_setTextureRect(player.head, rect[animation->frame]);
        animation->frame++;
    } else {
        if (animation->frame < 0)
            animation->frame = animation->max_frame;
        sfSprite_setTextureRect(player.body, rect[animation->frame]);
        if (player.animate_head)
            sfSprite_setTextureRect(player.head, rect[animation->frame]);
        animation->frame--;
    }
}

void move_player(player_t *player, room_t *cur_room, all_t *objects)
{
    sfVector2f up = { 0, -1};
    sfVector2f left = {-1, 0};
    sfVector2f right = {1, 0};
    sfVector2f down = {0, 1};
    sfIntRect player_rect = sfSprite_getTextureRect(player->body);


    if (sfClock_getElapsedTime(player->walk_clock).microseconds <= 1000000 / player->speed)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        sfSprite_move(player->body, up);
        sfSprite_move(player->head, up);
        handle_obstacle(cur_room, player, down, 0, objects);
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        sfSprite_move(player->body, down);
        sfSprite_move(player->head, down);
        handle_obstacle(cur_room, player, up, 1, objects);
    }
    if (sfKeyboard_isKeyPressed(sfKeyA)) {
        sfSprite_move(player->body, left);
        sfSprite_move(player->head, left);
        handle_obstacle(cur_room, player, right, 0, objects);
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        sfSprite_move(player->body, right);
        sfSprite_move(player->head, right);
        handle_obstacle(cur_room, player, left, 1, objects);
    }
    sfClock_restart(player->walk_clock);
    /*switch (player->move) {
    case 'W':
        sfSprite_move(player->sprite, up);
        break;
    case 'S':
        sfSprite_move(player->sprite, down);
        break;
    case 'D':
        sfSprite_move(player->sprite, right);
        break;
    case 'A':
        sfSprite_move(player->sprite, left);
        break;
    default:
        break;
    }*/
}

void handle_obstacle(room_t *cur_room, player_t *player, sfVector2f backwards, int is_switch, all_t *objects)
{
    sfVector2f position_player = sfSprite_getPosition(player->body);
    sfVector2f temp_p = position_player;
    double x_gap = 95.0;
    double y_gap = 95.0;

    for (sprite_list_t *temp = cur_room->obstacles->next; temp; temp = temp->next) {
        sfVector2f position_obstacle = sfSprite_getPosition(temp->sprite);
        /*sfVector2f room_pos = sfSprite_getPosition(cur_room->background_sprite);
        if (backwards.x == -1 && position_obstacle.x < room_pos.x + (cur_room->width - 1) * 100) {
            y_gap -= 1;
        }*/
        /*if (backwards.y == -1)
            y_gap - 5;*/
        /*if (position_player->x + x_gap >= position_obstacle.x && position_player->x <= position_obstacle.x + x_gap \
            && position_player->y  + y_gap >= position_obstacle.y && position_player->y <= position_obstacle.y + y_gap)*/
        if (is_colision_between_two_sprites(player->body, temp->sprite, x_gap, y_gap)){
            sfSprite_move(player->body, backwards);
            sfSprite_move(player->head, backwards);
            break;
        }
    }
    for (enemy_list_t *temp = cur_room->enemies->next; temp; temp = temp->next) {
        if (is_colision_between_two_sprites(player->body, temp->enemy->sprite, x_gap, y_gap)) {
            if (sfClock_getElapsedTime(player->invincibillity_clock).microseconds > SEC / player->invincibillity_duaration) {
                sfClock_restart(player->invincibillity_clock);
                player->cur_hp--;
                refresh_player_lives(player);
            }
            sfSprite_move(player->body, backwards);
            sfSprite_move(player->head, backwards);
            /*backwards.x *= -2;
            backwards.y += -2;
            sfSprite_move(temp->enemy->sprite, backwards);
            sfSprite_move(temp->enemy->health_bar.foreground_sprite, backwards);
            sfSprite_move(temp->enemy->healtvoid update_stats(player_t *player, stats_display_t *stats)h_bar.background_sprite, backwards);*/ //<= pushes enemies
            break;
        }
    }
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_marked && is_colision_between_two_sprites(player->body, cur_room->reaper.sprite, x_gap, y_gap)) {
        sfSprite_move(player->body, backwards);
        sfSprite_move(player->head, backwards);
    }
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_boss_room && is_colision_between_two_sprites(player->body, cur_room->statue.sprite, x_gap, y_gap) && !cur_room->is_bossfight) {
        sfSprite_move(player->body, backwards);
        sfSprite_move(player->head, backwards);
    }
    if (map[curr_room_x][curr_room_y]->is_boss_room && objects->floor_is_won) {
        if (is_colision_between_two_sprites(player->body, cur_room->trap_door, 95.0, 95.0)) {
            init_map();
            curr_room_x = MAP_WIDTH / 2;
            curr_room_y = MAP_HEIGHT / 2;
            load_room(objects, NONE);
            for (int i = 0; i < 7; i++) {
                objects->enemy_templates[i].max_hp *= 1.05;
                objects->enemy_templates[i].cur_hp *= 1.05;
                objects->enemy_templates[i].shots_per_second *= 1.05;
                objects->enemy_templates[i].projectile_speed *= 1.05;
            }
            objects->cur_floor++;
            objects->floor_is_won = 0;
        }
    }
    if (map[curr_room_x][curr_room_y]->is_boss_room && objects->floor_is_won) {
        if (is_colision_between_two_sprites(player->body, cur_room->trophy, 95.0, 95.0)) {
            objects->credits = 1;
        }
    }
}

void refresh_player_lives(player_t *player)
{
    int sprite = 0;
    int i = 0;
    int j = 0;

    for (j = 1; i < player->cur_hp && sprite < 10; i++, j++) {
        if (j > 2) {
            sprite++;
            j = 1;
        }
        sfSprite_setTextureRect(player->heart_sprites[sprite], player->health_rect[j]);
    }
    if (j < 2)
        i++;
    for (; i < player->max_hp && sprite < 10; i++) {
        if (i % 2 != 0)
            continue;
        sprite++;
        sfSprite_setTextureRect(player->heart_sprites[sprite],
            player->health_rect[0]);
    }
}

void update_stats(player_t *player, stats_display_t *stats)
{
    free(stats->str);
    stats->str = my_strcpy("000.0\n\n00.00\n\n000.0\n\n000.0");
    int pre = player->projectile.damage;
    int after = (player->projectile.damage - pre) * 10;
    for (int i = 0; i < pre && i < 999; i++) {
        add_points(stats->str, 2);
    }
    for (int i = 0; i < after && after < 9; i++) {
        add_points(stats->str, 4);
    }
    pre = (int) player->shot_speed;
    for (int i = 0; i < pre && i < 99; i++) {
        add_points(stats->str, 8);
    }
    after = (player->shot_speed - pre) * 100;
    for (int i = 0; i < after && i < 99; i++) {
        add_points(stats->str, 11);
    }
    pre = player->projectile.speed;
    for (int i = 0; i < pre && i < 999; i++) {
        add_points(stats->str, 16);
    }
    after = (player->projectile.speed - pre) * 10;
    for (int i = 0; i < after && i < 9; i++) {
        add_points(stats->str, 18);
    }
    pre = player->speed;
    for (int i = 0; i < pre && i < 999; i++) {
        add_points(stats->str, 23);
    }
    after = (player->speed - pre) * 10;
    for (int i = 0; i < after && after < 9; i++) {
        add_points(stats->str, 25);
    }
    sfText_setString(stats->text, stats->str);
}