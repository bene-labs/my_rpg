//
// Created by benedikt on 5/3/20.
//

#include "../include/rpg.h"

void init_boss_fight(all_t *objects, room_t *room)
{
    sfVector2f position = sfSprite_getPosition(room->background_sprite);
    position.x += room->width / 2 * 100;
    position.y += 110;
    room->enemies = create_enemy_list();
    append_to_list(room->enemies, create_enemy(objects->enemy_templates, 6, position, objects, 0));
    room->enemies->next->enemy->is_boss = 1;
    position.y += 200;
    position.x -= 200;
    append_to_list(room->enemies, create_enemy(objects->enemy_templates, 4, position, objects, 0));
    position.x += 400;
    append_to_list(room->enemies, create_enemy(objects->enemy_templates, 5, position, objects, 0));
    room->is_bossfight = 1;
    objects->dialogue_box.is_active = 0;
    objects->cur_room->enemies->next->enemy->backwards = -1;
    map[curr_room_x][curr_room_y]->cleared = 0;
}