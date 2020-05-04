//
// Created by benedikt on 4/27/20.
//

#include "../include/rpg.h"

void create_enemy_projectile(enemy_t *enemy, projectile_list_t *sprites, all_t *objects, int by_force)
{
    sfVector2f gap = {50, 50};
    projectile_list_t *head = sprites;

    if (enemy->is_boss)
        gap.x += 83;
    if (by_force || sfClock_getElapsedTime(enemy->shooting_clock).microseconds > SEC / enemy->template.shots_per_second) {
        if (enemy->is_boss)
            enemy->template.next_shot = get_random_int_within_range(0, enemy->template.projectile_formations -1);
        if (enemy->type == 3)
            sfSprite_setTextureRect(enemy->sprite, enemy->template.rects[enemy->template.next_shot]);
        for (; sprites->next; sprites = sprites->next);
        for (int i = 0; i < enemy->template.projectile_count_per_shot || (enemy->is_boss && i < enemy->template.projectile_count_per_shot_arr[enemy->template.next_shot]); i++) {
            sprites->next = malloc(sizeof(projectile_list_t));
            sprites->next->sprite = sfSprite_create();
            sfSprite_setTexture(sprites->next->sprite,
                objects->enemy_projectile_texture, sfTrue);
            sfSprite_setPosition(sprites->next->sprite,
                sfSprite_getPosition(enemy->sprite));
            sfSprite_move(sprites->next->sprite, gap);
            sprites->next->move = enemy->template.projectile_directions_per_shot[enemy->template.next_shot][i];
            sprites->next->next = NULL;
            sprites = sprites->next;
        }
        sfClock_restart(enemy->shooting_clock);
        if (enemy->is_boss) {
            enemy->template.shots_per_second = ((double) get_random_int_within_range(0, 150) + 50) / 100;
            //printf("%f\n", enemy->template.shots_per_second);
        }
        if (enemy->template.next_shot < enemy->template.projectile_formations - 1)
            enemy->template.next_shot++;
        else {
            enemy->template.next_shot = 0;
        }
    }
    sprites = head;
}

void shoot_projectile(player_t *player, projectile_t *projectile, projectile_list_t *sprites)
{
    sfVector2f gap = {25, 30};

    if (player->shoot_state != -1 && sfClock_getElapsedTime(player->shot_clock).microseconds > SEC / player->shot_speed) {
        sfClock_restart(player->shot_clock);
        for (; sprites->next; sprites = sprites->next);
        sprites->next = malloc(sizeof(projectile_list_t ));
        sprites->next->sprite = sfSprite_create();
        sfSprite_setTexture(sprites->next->sprite, player->projectile_texture, sfTrue);
        sfSprite_setPosition(sprites->next->sprite, sfSprite_getPosition(player->head));
        sfSprite_move(sprites->next->sprite, gap);
        sfSprite_setTextureRect(sprites->next->sprite, projectile->rects[projectile->animation.frame]);
        sprites->next->move = projectile->vectors[player->shoot_state];
        sprites->next->next = NULL;
    }
}

void move_projectile(projectile_t *projectile, room_t *cur_room, all_t *objects)
{
    projectile_list_t  *save;
    sfVector2f pos_floor = sfSprite_getPosition(cur_room->background_sprite);
    int was_deleted = 0;

    if (sfClock_getElapsedTime(projectile->clock).microseconds <= SEC / projectile->speed)
        return;
    for (projectile_list_t *temp = projectile->sprites; temp->next; ) {
        was_deleted = 0;
        sfSprite_move(temp->next->sprite, temp->next->move);
        sprite_list_t *temp_2 = cur_room->obstacles->next;
        enemy_list_t *temp_3 = cur_room->enemies->next;
        for (; temp_2; temp_2 = temp_2->next) {
            sfVector2f position_obstacle = sfSprite_getPosition(temp_2->sprite);
            sfVector2f projectile_pos = sfSprite_getPosition(temp->next->sprite);
            if (projectile_pos.x + 15 >= position_obstacle.x &&
                projectile_pos.x <= position_obstacle.x + 100\
 && projectile_pos.y >= position_obstacle.y &&
                projectile_pos.y <= position_obstacle.y + 100 \
 || projectile_pos.x < pos_floor.x || projectile_pos.x > pos_floor.x + (cur_room->width - 1) * 100 || \
 projectile_pos.y < pos_floor.y || projectile_pos.y > pos_floor.y + (cur_room->height -1) * 100) {
                save = temp->next->next;
                free(temp->next);
                temp->next = save;
                was_deleted = 1;
                break;
            }
        }
        if (was_deleted)
            continue;
        for (; !projectile->is_hostile && temp_3; temp_3 = temp_3->next) {
            if (!temp_3->enemy->is_alive)
                continue;
            sfVector2f position_obstacle = sfSprite_getPosition(temp_3->enemy->sprite);
            sfVector2f projectile_pos = sfSprite_getPosition(temp->next->sprite);
            if (projectile_pos.x + 15 >= position_obstacle.x &&
                projectile_pos.x <= position_obstacle.x + 100\
 && projectile_pos.y >= position_obstacle.y &&
                projectile_pos.y <= position_obstacle.y + 100 || \
                (temp_3->enemy->is_boss && projectile_pos.x + 15 >= position_obstacle.x &&
                projectile_pos.x <= position_obstacle.x + 266\
 && projectile_pos.y >= position_obstacle.y &&
                projectile_pos.y <= position_obstacle.y + 140)) {
                temp_3->enemy->template.cur_hp -= projectile->damage;
                refresh_enemy_health_bar(temp_3->enemy, objects, temp_3->enemy->template.cur_hp, temp_3->enemy->template.max_hp);
                save = temp->next->next;
                free(temp->next);
                temp->next = save;
                was_deleted = 1;
                break;
            }
        }
        if (was_deleted)
            continue;
        sfVector2f position_obstacle = sfSprite_getPosition(objects->player.body);
        sfVector2f projectile_pos = sfSprite_getPosition(temp->next->sprite);
        if (projectile->is_hostile && projectile_pos.x + 15 >= position_obstacle.x &&
            projectile_pos.x + 15 <= position_obstacle.x + 85\
 && projectile_pos.y >= position_obstacle.y &&
            projectile_pos.y <= position_obstacle.y + 90) {
            if (sfClock_getElapsedTime(objects->player.invincibillity_clock).microseconds > SEC / objects->player.invincibillity_duaration) {
                sfClock_restart(objects->player.invincibillity_clock);
                objects->player.cur_hp--;
                if (objects->player.cur_hp <= 0)
                    objects->credits = 1;
                refresh_player_lives(&objects->player);
            }
            //sfSprite_setColor(objects->player.body, sfRed);
            //sfSprite_setColor(objects->player.head, sfRed);
            save = temp->next->next;
            free(temp->next);
            temp->next = save;
            was_deleted = 1;
            break;
        }
        if (!was_deleted)
            temp = temp->next;
    }
    sfClock_restart(projectile->clock);
}

void animate_projectile(projectile_t *projectile, animation_t *animation)
{
   /* if (!projectile->is_animated)
        return;*/
    if (sfClock_getElapsedTime(animation->clock).microseconds > animation->delay) {
        sfClock_restart(animation->clock);
        if (animation->frame > animation->max_frame)
            animation->frame = 0;
        for (projectile_list_t *temp = projectile->sprites->next; temp; temp = temp->next) {
            sfSprite_setTextureRect(temp->sprite,
                projectile->rects[animation->frame]);
        }
        animation->frame++;
    }
}