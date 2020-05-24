//
// Created by benedikt on 5/3/20.
//

#include "../include/rpg.h"

void handle_boss_summoner_dialogue(all_t *objects, sfRenderWindow *window)
{
    if (map[curr_room_x][curr_room_y]->is_boss_room && !objects->cur_room->is_bossfight) {
        sfVector2f pos = {600, 200};
        if (!objects->dialogue_box.is_active &&
            sfMouse_isButtonPressed(sfMouseLeft) && !objects->is_mouse_held &&
            is_collision_cursor_button(sfMouse_getPositionRenderWindow(window),
                sfSprite_getPosition(objects->cur_room->statue.sprite), 100,
                100) \
 || (is_sprite_inside_radius(objects->player.body, 20.0,
            sfSprite_getPosition(objects->cur_room->statue.sprite).x + 50,
            sfSprite_getPosition(objects->cur_room->statue.sprite).y + 50) &&
            sfKeyboard_isKeyPressed(sfKeyE))) {
            prepare_dialogue_box(objects, "Foolish Mortal!\nYou wish to challenge my master?\nYou must be insane.",
                pos, &objects->dialogue_box, &objects->cur_room->statue);
        } else {
            if ((check_button_interaction(&objects->dialogue_box.close, window,
                60, 60) && !objects->is_mouse_held) ||
                sfKeyboard_isKeyPressed(sfKeyEscape))
                objects->dialogue_box.is_active = 0;
        }
        if (check_button_interaction(&objects->dialogue_box.shop, window,
            231, 152) && !objects->is_mouse_held)
            init_boss_fight(objects, objects->cur_room);
    }
}

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