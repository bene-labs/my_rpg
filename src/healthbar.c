//
// Created by benedikt on 4/30/20.
//

#include "../include/rpg.h"

void refresh_enemy_health_bar(enemy_t *enemy, all_t *objects, double cur_hp, double max_hp)
{
    if (cur_hp <= 0) {
            enemy->health_bar.foreground_rect.width = 0;
            sfSprite_setTextureRect(enemy->health_bar.foreground_sprite,
                enemy->health_bar.foreground_rect);
            enemy->is_alive = 0;
            enemy->template.animation.frame = 0;
            sfSprite_setTexture(enemy->sprite, enemy->template.die, sfTrue);
        if (enemy->type == 1) {
            sfSprite_setTextureRect(enemy->sprite, enemy->template.rects[0]);
        } else {
            enemy->template.animation.max_frame = 9;
            sfSprite_setTextureRect(enemy->sprite, objects->die_rect[0]);
            enemy->template.rects = objects->die_rect;
        }
        return;
        //enemy->is_alive = 0;
        /*if (enemy->walk.is_mirrored == 1) {
            if (enemy->is_ally == 0)
                sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][3], sfTrue);
            else
                sfSprite_setTexture(enemy->sprite, objects->map.building_plots.ally_textures[enemy->type][3], sfTrue);
            sfSprite_setTextureRect(enemy->sprite, enemy->walk.mirrored_rect[0]);
        } else {
            if (enemy->is_ally == 0)
                sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][2], sfTrue);
            else
                sfSprite_setTexture(enemy->sprite, objects->map.building_plots.ally_textures[enemy->type][2], sfTrue);
            sfSprite_setTextureRect(enemy->sprite, enemy->walk.rect[0]);
        }
        enemy->frame = 0;*/
    } else {
        enemy->health_bar.percentage = cur_hp / max_hp * 100;
        enemy->health_bar.foreground_rect.width = (int) enemy->health_bar.percentage;
    }
    sfSprite_setTextureRect(enemy->health_bar.foreground_sprite,
        enemy->health_bar.foreground_rect);
}