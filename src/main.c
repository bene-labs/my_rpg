/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** main
*/

#include "../include/rpg.h"

int main()
{
    curr_room_x = MAP_WIDTH / 2;
    curr_room_y = MAP_HEIGHT / 2;
    map = 0;
    sfVideoMode mode = {1920, 1080, 64};
    sfRenderWindow *window = sfRenderWindow_create(mode, "-My_rpg-", \
sfClose, NULL);
    all_t *objects = create_objects();

    if (load_room(objects, NONE) == -1) {
        my_printf("Error: couldn't load start room.\n");
        return (84);
    }
    handle_game_loop(window, objects);
    return 0;
}

void handle_game_loop(sfRenderWindow *window, all_t *objects)
{
    sfEvent event;
    time_t last_tick;
    int rand_loc_x = 0;
    int rand_loc_y = 0;

    menu(window);
    sfMusic *background_music = sfMusic_createFromFile("resources/background_music_normal.ogg");
    sfMusic_setLoop(background_music, sfTrue);
    sfMusic_setVolume(background_music, 3);
    sfMusic_play(background_music);
    srand((unsigned) time(&last_tick));
    rand_loc_x = rand() % 1920;
    rand_loc_y = rand() % 1280;
    while (sfRenderWindow_isOpen(window)) {
        load_room(objects, get_player_leave_direction(&objects->player, objects->cur_room));
        handle_room_clear(objects->cur_room->enemies, objects);
        sfRenderWindow_clear(window, sfBlack);
        move_enemies_by_their_vector(objects->cur_room->enemies, &objects->player, objects->cur_room, objects);
        move_player(&objects->player, objects->cur_room, objects);
        if (objects->credits) {
            credits(window);
            menu(window);
            objects->credits = 0;
            init_map();
            curr_room_x = MAP_WIDTH / 2;
            curr_room_y = MAP_HEIGHT / 2;
            load_room(objects, NONE);
            for (int i = 0; i < objects->cur_floor; i++) {
                for (int i = 0; i < 7; i++) {
                    objects->enemy_templates[i].max_hp /= 1.05;
                    objects->enemy_templates[i].cur_hp /= 1.05;
                    objects->enemy_templates[i].shots_per_second /= 1.05;
                    objects->enemy_templates[i].projectile_speed /= 1.05;
                }
            }
            objects->cur_floor = 0;
            objects->player.soul_count = 0;
            for (int i = 0; i < 4; i++)
                objects->player.soul_string[i] = '0';
            sfText_setString(objects->player.soul_text, objects->player.soul_string);
            objects->floor_is_won = 0;
            objects->player.cur_hp = HP;
            objects->player.max_hp = HP;
            objects->player.damage = DAMAGE;
            objects->player.shot_speed = S_SPEED;
            objects->player.speed = SPEED;
            objects->player.projectile.speed = P_SPEED;
        }
        animate_player(objects->player.animation_rects[objects->player.state], objects->player.animation_rects[objects->player.shoot_state], &objects->player.animation, objects->player);
        shoot_projectile(&objects->player, &objects->player.projectile, objects->player.projectile.sprites);
        move_projectile(&objects->player.projectile, objects->cur_room, objects);
        animate_projectile(&objects->player.projectile, &objects->player.projectile.animation);
        animate_enemies(objects->cur_room->enemies, objects);
        for (enemy_list_t *temp = objects->cur_room->enemies->next; temp; temp = temp->next) {
            if (temp->enemy->is_alive)
                create_enemy_projectile(temp->enemy, temp->enemy->projectile.sprites, objects, 0);
            move_projectile(&temp->enemy->projectile, objects->cur_room, objects);
        }
        draw_sprites(window, objects);
        if (!DEBUG)
            draw_minimap(window);
        sfRenderWindow_display(window);
        handle_enemy_movement(objects);
        while (sfRenderWindow_pollEvent(window, &event))
            handle_events(window, objects, event);
    }
    sfMusic_stop(background_music);
    sfMusic_destroy(background_music);
}

void handle_events(sfRenderWindow *window, all_t *objects, sfEvent event)
{
    sfVector2f player = sfSprite_getPosition(objects->player.head);

    if (event.type == sfEvtClosed) {
        sfRenderWindow_close(window);
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyW))
        objects->player.state = 3;
    else if (sfKeyboard_isKeyPressed(sfKeyS))
        objects->player.state = 0;
    else if (sfKeyboard_isKeyPressed(sfKeyA))
        objects->player.state = 1;
    else if (sfKeyboard_isKeyPressed(sfKeyD))
        objects->player.state = 2;
    else
        objects->player.state = -1;

    if (DEBUG == 2)
        debug_map(objects);
    else if (!DEBUG) {
        handle_shop(objects, window);
        handle_boss_summoner_dialogue(objects, window);
    }
    if (sfMouse_isButtonPressed(sfMouseLeft))
        objects->is_mouse_held = 1;
    else
        objects->is_mouse_held = 0;
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        objects->player.shoot_state = 3;
    else if (sfKeyboard_isKeyPressed(sfKeyDown))
        objects->player.shoot_state = 0;
    else if (sfKeyboard_isKeyPressed(sfKeyLeft))
        objects->player.shoot_state = 1;
    else if (sfKeyboard_isKeyPressed(sfKeyRight))
        objects->player.shoot_state = 2;
    else {
        objects->player.shoot_state = -1;
        objects->player.animate_head = 1;
        return;
    }
    objects->player.animate_head = 0;
    sfSprite_setTextureRect(objects->player.head, objects->player.animation_rects[objects->player.shoot_state + 4][0]);
}


void draw_sprites(sfRenderWindow *window, all_t *objects)
{
    sfRenderWindow_drawSprite(window, objects->cur_room->background_sprite, NULL);
    sfRenderWindow_drawSprite(window, objects->player.body, NULL);
    sfRenderWindow_drawSprite(window, objects->player.head, NULL);
    for (projectile_list_t *temp = objects->player.projectile.sprites->next; temp; temp = temp->next) {
        sfRenderWindow_drawSprite(window, temp->sprite, NULL);
    }
    for (sprite_list_t *temp = objects->cur_room->obstacles->next; temp; temp = temp->next)
        sfRenderWindow_drawSprite(window, temp->sprite, NULL);
    for (sprite_list_t *temp = objects->cur_room->empty_tiles->next; temp; temp = temp->next)
        sfRenderWindow_drawSprite(window, temp->sprite, NULL);
    for (enemy_list_t *temp = objects->cur_room->enemies->next; temp; temp = temp->next) {
        sfRenderWindow_drawSprite(window, temp->enemy->health_bar.background_sprite, NULL);
        sfRenderWindow_drawSprite(window, temp->enemy->health_bar.foreground_sprite, NULL);
        sfRenderWindow_drawSprite(window, temp->enemy->sprite, NULL);
        for (projectile_list_t *temp_2 = temp->enemy->projectile.sprites->next; temp_2; temp_2 = temp_2->next)
            sfRenderWindow_drawSprite(window, temp_2->sprite, NULL);
    }
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_marked)
        sfRenderWindow_drawSprite(window, objects->cur_room->reaper.sprite, NULL);
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_boss_room && !objects->cur_room->is_bossfight)
        sfRenderWindow_drawSprite(window, objects->cur_room->statue.sprite, NULL);
    for (int i = 0; i < objects->player.max_hp / 2; i++)
        sfRenderWindow_drawSprite(window, objects->player.heart_sprites[i], NULL);
    sfRenderWindow_drawSprite(window, objects->x_sprite, NULL);
    sfRenderWindow_drawSprite(window, objects->soul_sprite, NULL);
    sfRenderWindow_drawText(window, objects->player.soul_text, NULL);
    if (objects->dialogue_box.is_active) {
        sfRenderWindow_drawSprite(window, objects->dialogue_box.icon_background_sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->dialogue_box.icon_box_sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->dialogue_box.icon, NULL);
        sfRenderWindow_drawText(window, objects->dialogue_box.text, NULL);
        sfRenderWindow_drawSprite(window, objects->dialogue_box.close.sprite, NULL);
        if (!objects->dialogue_box.is_shop) {
            sfRenderWindow_drawSprite(window, objects->dialogue_box.talk.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.talk.text, NULL);
            sfRenderWindow_drawSprite(window, objects->dialogue_box.shop.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.shop.text, NULL);
        } else {
            sfRenderWindow_drawSprite(window, objects->dialogue_box.hp.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.hp.text, NULL);
            sfRenderWindow_drawSprite(window, objects->dialogue_box.speed.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.speed.text, NULL);
            sfRenderWindow_drawSprite(window, objects->dialogue_box.fire_rate.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.fire_rate.text, NULL);
            sfRenderWindow_drawSprite(window, objects->dialogue_box.projectile_speed.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.projectile_speed.text, NULL);
            sfRenderWindow_drawSprite(window, objects->dialogue_box.damage.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.damage.text, NULL);
            sfRenderWindow_drawSprite(window, objects->dialogue_box.back.sprite, NULL);
            sfRenderWindow_drawText(window, objects->dialogue_box.back.text, NULL);
        }
    }
    if (objects->floor_is_won && map[curr_room_x][curr_room_y]->is_boss_room) {
            sfRenderWindow_drawSprite(window, objects->cur_room->trophy, NULL);
            sfRenderWindow_drawSprite(window, objects->cur_room->trap_door, NULL);
    }
    sfRenderWindow_drawSprite(window, objects->stats.sprite, NULL);
    sfRenderWindow_drawText(window, objects->stats.text, NULL);
}