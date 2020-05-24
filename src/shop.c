//
// Created by benedikt on 5/24/20.
//

#include "../include/rpg.h"

void handle_shop(all_t *objects, sfRenderWindow *window)
{
    if (map[curr_room_x][curr_room_y]->is_marked) { //if player is inside shop room
        sfVector2f pos = {600, 200};
        if (!objects->dialogue_box.is_active && sfMouse_isButtonPressed(sfMouseLeft) && !objects->is_mouse_held && is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), sfSprite_getPosition(objects->cur_room->reaper.sprite), 100, 100) \
|| (is_sprite_inside_radius(objects->player.body, 20.0, sfSprite_getPosition(objects->cur_room->reaper.sprite).x +50, sfSprite_getPosition(objects->cur_room->reaper.sprite).y + 50) && sfKeyboard_isKeyPressed(sfKeyE))) {
            prepare_dialogue_box(objects, "Greetings lost soul.\nYou got something for me?", pos, &objects->dialogue_box, &objects->cur_room->reaper);
        } else {
            if ((check_button_interaction(&objects->dialogue_box.close, window,
                60, 60) && !objects->is_mouse_held) || sfKeyboard_isKeyPressed(sfKeyEscape))
                objects->dialogue_box.is_active = 0;
            if (!objects->dialogue_box.is_shop) {
                if (check_button_interaction(&objects->dialogue_box.talk,
                    window, 231, 152))
                    prepare_dialogue_box(objects,
                        "Hi there!\nHow about we make a deal?\nYou give me your soul(s)\n and I bless you with power.", pos,
                        &objects->dialogue_box,
                        &objects->cur_room->reaper);
                if (check_button_interaction(&objects->dialogue_box.shop,
                    window, 231, 152))
                    objects->dialogue_box.is_shop = 1;
            } else {
                handle_shopkeeper_purchase_buttons(objects, window, pos);
                if (check_button_interaction(&objects->dialogue_box.back, window,231, 152))
                    objects->dialogue_box.is_shop = 0;
            }
        }
    }
}

void handle_shopkeeper_purchase_buttons(all_t *objects, sfRenderWindow *window, sfVector2f pos)
{
    if (check_button_interaction(&objects->dialogue_box.hp, window,231, 152) && objects->player.max_hp < 20) {
        if (objects->player.soul_count >=
            objects->dialogue_box.hp.value) {
            objects->player.max_hp += 2;
            if (objects->player.max_hp >= 20)
                sfText_setString(objects->dialogue_box.hp.text, "out of stock!\nsorry :(");
            objects->player.cur_hp = objects->player.max_hp;
            refresh_player_lives(&objects->player, objects);
            objects->player.soul_count -= objects->dialogue_box.hp.value;
            for (int i = 0; i < objects->dialogue_box.hp.value; i++)
                remove_points(objects->player.soul_string, 3);
            sfText_setString(objects->player.soul_text, objects->player.soul_string);
            prepare_dialogue_box(objects, "Thx 4 purchase\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
        } else
            prepare_dialogue_box(objects, "your pocket looks as empty\n as my eye sockets\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
    }
    if (check_button_interaction(&objects->dialogue_box.speed, window,231, 152)) {
        if (objects->player.soul_count >=
            objects->dialogue_box.speed.value) {
            objects->player.speed += objects->player.speed * 0.10;
            handle_shop_purchase(&objects->dialogue_box, &objects->player, &objects->dialogue_box.speed, objects);
        } else
            prepare_dialogue_box(objects, "U broke?\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);

    }
    if (check_button_interaction(&objects->dialogue_box.projectile_speed, window,231, 152)) {
        if (objects->player.soul_count >= objects->dialogue_box.projectile_speed.value) {
            objects->player.projectile.speed += objects->player.projectile.speed * 0.15;
            handle_shop_purchase(&objects->dialogue_box, &objects->player, &objects->dialogue_box.projectile_speed, objects);
        } else
            prepare_dialogue_box(objects, "U still broke?\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
    }
    if (check_button_interaction(&objects->dialogue_box.fire_rate, window,231, 152)) {
        if (objects->player.soul_count >= objects->dialogue_box.fire_rate.value) {
            objects->player.shot_speed += objects->player.shot_speed * 0.08;
            handle_shop_purchase(&objects->dialogue_box, &objects->player, &objects->dialogue_box.fire_rate, objects);
        } else
            prepare_dialogue_box(objects, "Go get more souls.\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
    }
    if (check_button_interaction(&objects->dialogue_box.damage, window, 231, 152)) {
        if (objects->player.soul_count >= objects->dialogue_box.damage.value) {
            objects->player.projectile.damage += objects->player.projectile.damage * 0.075;
            handle_shop_purchase(&objects->dialogue_box, &objects->player, &objects->dialogue_box.damage, objects);
        } else
            prepare_dialogue_box(objects, "No souls, no deal\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
    }
}

void handle_shop_purchase(dialogue_box_t *dialogue_box, player_t *player, button_t *button, all_t *objects)
{
    sfVector2f pos = {600, 200};

    player->soul_count -= button->value;
    for (int i = 0; i < 2; i++)
        add_points(button->str, button->nb_end);
    sfText_setString(button->text, button->str);
    for (int i = 0; i < button->value; i++)
        remove_points(player->soul_string, 3);
    sfText_setString(player->soul_text, player->soul_string);
    button->value += 2;
    prepare_dialogue_box(objects, "Thx 4 purchase\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
    update_stats(player, &objects->stats);
}