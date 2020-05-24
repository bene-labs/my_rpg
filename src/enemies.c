//
// Created by benedikt on 4/30/20.
//

#include "../include/rpg.h"

enemy_t *create_enemy(enemy_template_t *template, int type, sfVector2f position, all_t *objects, int is_prime)
{
    enemy_t  *enemy = malloc(sizeof(enemy_t));
    sfVector2f move = {0, 0};
    sfVector2f health_bar_gap = {0, -25};

    enemy->is_boss = 0;
    enemy->template = template[type];
    enemy->template.animation.clock = sfClock_create();
    enemy->projectile.clock = sfClock_create();
    enemy->projectile.speed = enemy->template.projectile_speed;
    enemy->projectile.damage = 1;
    enemy->backwards = -1;
    enemy->projectile.is_hostile = 1;
    enemy->sprite = sfSprite_create();
    enemy->projectile.sprites = malloc(sizeof(projectile_list_t));
    enemy->projectile.sprites->next = NULL;
    sfSprite_setTexture(enemy->sprite, enemy->template.texture, sfTrue);
    sfSprite_setTextureRect(enemy->sprite, enemy->template.rects[0]);
    sfSprite_setPosition(enemy->sprite, position);
    enemy->move = move;
    enemy->movement_clock = sfClock_create();
    enemy->shooting_clock = sfClock_create();
    enemy->type = type;
    enemy->is_alive = 1;
    enemy->health_bar.background_sprite = sfSprite_create();
    enemy->health_bar.foreground_sprite = sfSprite_create();
    sfSprite_setTexture(enemy->health_bar.foreground_sprite, objects->health_bar_foreground, sfTrue);
    sfSprite_setTexture(enemy->health_bar.background_sprite, objects->health_bar_background, sfTrue);
    sfSprite_setPosition(enemy->health_bar.background_sprite, position);
    sfSprite_setPosition(enemy->health_bar.foreground_sprite, position);
    sfSprite_move(enemy->health_bar.foreground_sprite, health_bar_gap);
    sfSprite_move(enemy->health_bar.background_sprite, health_bar_gap);
    enemy->health_bar.foreground_rect = sfSprite_getTextureRect(enemy->health_bar.foreground_sprite);
    if (is_prime) {
        sfSprite_setColor(enemy->sprite, sfRed);
        enemy->template.souls *= 3;
        switch (type) {
        case 0:
            enemy->template.movement_type = MOVE_FOLLOW;

            break;
        case 1:
            enemy->template.shots_per_second = 1.0;
            break;
        case 2:
            enemy->template.shots_per_second = 0.75;
            break;
        case 3:
             enemy->template.projectile_count_per_shot = 2;
            break;
        default:
            break;
        }
    }
    return (enemy);
}

void move_enemies_by_their_vector(enemy_list_t *enemies, player_t *player, room_t *cur_room, all_t *objects)
{
    sfVector2f backwards;

    for (enemy_list_t *temp = enemies->next; temp; temp = temp->next) {
        if (temp->enemy->template.speed <= 0 || temp->enemy->template.movement_type == MOVE_STATIC|| !temp->enemy->is_alive)
            continue;
        if (sfClock_getElapsedTime(temp->enemy->movement_clock).microseconds > SEC / temp->enemy->template.speed) {
            backwards = temp->enemy->move;
            //backwards.x *= 25;
            //backwards.y *= 25; => potenial 'knockback'
            backwards.x *= -1;
            backwards.y *= -1;
            sfSprite_move(temp->enemy->sprite, temp->enemy->move);
            sfSprite_move(temp->enemy->health_bar.foreground_sprite, temp->enemy->move);
            sfSprite_move(temp->enemy->health_bar.background_sprite, temp->enemy->move);
            sfClock_restart(temp->enemy->movement_clock);
            for (enemy_list_t *temp_2 = enemies->next; temp_2; temp_2 = temp_2->next) {
                if (temp_2 != temp && temp_2->enemy->template.movement_type != MOVE_STATIC && is_colision_between_two_sprites(temp->enemy->sprite, temp_2->enemy->sprite, 95.0, 95.0)) {
                    sfSprite_move(temp->enemy->sprite, backwards);
                    sfSprite_move(temp->enemy->health_bar.foreground_sprite, backwards);
                    sfSprite_move(temp->enemy->health_bar.background_sprite, backwards);
                    break;
                }
            }
            if (is_colision_between_two_sprites(temp->enemy->sprite, player->body, 95.0, 95.0)) {
                sfSprite_move(temp->enemy->sprite, backwards);
                sfSprite_move(temp->enemy->health_bar.foreground_sprite, backwards);
                sfSprite_move(temp->enemy->health_bar.background_sprite, backwards);
                if (sfClock_getElapsedTime(player->invincibillity_clock).microseconds > SEC / player->invincibillity_duaration) {
                    sfClock_restart(player->invincibillity_clock);
                    player->cur_hp--;
                    refresh_player_lives(player, objects);
                }
            }
            for (sprite_list_t *obstacles = cur_room->obstacles->next; temp->enemy->template.movement_type == MOVE_RANDOM && obstacles; obstacles = obstacles->next) {
                if (is_colision_between_two_sprites(temp->enemy->sprite, obstacles->sprite, 95.0, 95.0)) {
                    temp->enemy->backwards *= -1;
                    sfSprite_move(temp->enemy->sprite, backwards);
                    if (temp->enemy->type == 4) {
                        create_enemy_projectile(temp->enemy, temp->enemy->projectile.sprites, objects, 1);
                    }
                }
            }
        }
    }
}

void animate_enemies(enemy_list_t *enemies, all_t *objects)
{
    int end = 0;


    for (enemy_list_t *temp = enemies; temp->next;) {
        if ((temp->next->enemy->type >= 3 && temp->next->enemy->is_alive)) {
            temp = temp->next;
            continue;
        }
        if (sfClock_getElapsedTime(temp->next->enemy->template.animation.clock).microseconds > temp->next->enemy->template.animation.delay) {
            if (temp->next->enemy->template.animation.frame >= temp->next->enemy->template.animation.max_frame) {
                if (temp->next->enemy->is_alive)
                    temp->next->enemy->template.animation.frame = 0;
                else {
                    if (temp->next->next == NULL)
                        end = 1;
                    objects->player.soul_gain += temp->next->enemy->template.souls;
                    for (int i = 0; i < temp->next->enemy->template.souls; i++) {
                        add_points(objects->player.soul_string, 7);
                    }
                    sfText_setString(objects->player.soul_text, objects->player.soul_string);
                    remove_enemy_from_list(enemies, temp->next->enemy);
                    if (end)
                        return;
                    continue;
                }
            }
            sfSprite_setTextureRect(temp->next->enemy->sprite, temp->next->enemy->template.rects[temp->next->enemy->template.animation.frame]);
            temp->next->enemy->template.animation.frame++;
            sfClock_restart(temp->next->enemy->template.animation.clock);
        }
        temp = temp->next;
    }
}

void handle_enemy_movement(all_t *objects)
{
    time_t last_tick;
    int tick_length = 3;
    int rand_loc_x = 0;
    int rand_loc_y = 0;
    enemy_list_t *enemies = objects->cur_room->enemies->next;
    sfVector2f player_pos = sfSprite_getPosition(objects->player.body);
    sfVector2f enemy_pos;
    float length = 0;
    time_t curr_time;
    time(&curr_time);

    if (curr_time - last_tick >= tick_length) {
        srand((unsigned) time(&last_tick));
        rand_loc_x = rand() % 1920;
        rand_loc_y = rand() % 1280;
    }
    for (; enemies != 0; enemies = enemies->next) {
        enemy_pos = sfSprite_getPosition(enemies->enemy->sprite);
        if (enemies->enemy->template.movement_type == MOVE_FOLLOW_X) enemy_pos.x += sfSprite_getGlobalBounds(enemies->enemy->sprite).width / 2 - 50;
        if (enemies->enemy->template.movement_type == MOVE_RANDOM) {
            enemies->enemy->move.x = rand_loc_x - player_pos.x;
            enemies->enemy->move.y = rand_loc_y - player_pos.y;
        } else {
            enemies->enemy->move.x = player_pos.x - enemy_pos.x;
            enemies->enemy->move.y = player_pos.y - enemy_pos.y;
        }
        if (enemies->enemy->template.movement_type == MOVE_FOLLOW_X)
            enemies->enemy->move.y = 0;
        if (enemies->enemy->backwards == 1) {
            enemies->enemy->move.x *= -1;
            enemies->enemy->move.y *= -1;
        }
        length = sqrt(powf(enemies->enemy->move.x, 2) + powf(enemies->enemy->move.y, 2));
        if (length != 0) {
            enemies->enemy->move.x /= length;
            enemies->enemy->move.y /= length;
        }
    }
}