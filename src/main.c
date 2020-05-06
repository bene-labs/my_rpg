/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** main
*/

#include "../include/rpg.h"

time_t last_tick;
int tick_length = 3;
int rand_loc_x = 0;
int rand_loc_y = 0;

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
        my_printf("Error: couldn't load room.\n");
        return (84);

    }
    handle_game_loop(window, objects);
    return 0;
}

void handle_enemy_movement(all_t *objects)
{
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

void menu(sfRenderWindow *window)
{
    sfEvent event;
    sfVector2f text_pos = {1900 / 2, 1080 / 2};
    sfText *text = sfText_create();
    sfText_setOutlineColor(text, sfWhite);
    // sfText_setOutlineThickness(text, 4);
    // sfText_setStyle(text, sf);
    sfText_setFont(text, sfFont_createFromFile("resources/ARCADECLASSIC.otf"));
    sfText_setCharacterSize(text, 40);
    sfText_setFillColor(text, sfWhite);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, "Press   SPACE   to   go   to   HELL");
    text_pos.x -= sfText_getGlobalBounds(text).width / 2;
    sfText_setPosition(text, text_pos);

    do {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_display(window);
        while (sfRenderWindow_pollEvent(window, &event));
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return;
        }
    } while (!sfKeyboard_isKeyPressed(sfKeySpace) && sfRenderWindow_isOpen(window));
    sfText_destroy(text);
}

void credits(sfRenderWindow *window)
{
    sfEvent event;
    sfVector2f text_pos = {1900 / 2, 1080 + 100 - 50};
    sfText *text = sfText_create();
    sfText_setOutlineColor(text, sfWhite);
    sfText_setFont(text, sfFont_createFromFile("resources/ARCADECLASSIC.otf"));
    sfText_setCharacterSize(text, 40);
    sfText_setFillColor(text, sfWhite);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, "Benedikt   Mertes   -   engine   /   gameplay");
    text_pos.x -= sfText_getGlobalBounds(text).width / 2;
    sfText_setPosition(text, text_pos);

    sfVector2f text_1_pos = {1900 / 2, 1080 + 200 - 50 + 100};
    sfText *text_1 = sfText_create();
    sfText_setOutlineColor(text_1, sfWhite);
    sfText_setFont(text_1, sfFont_createFromFile("resources/ARCADECLASSIC.otf"));
    sfText_setCharacterSize(text_1, 40);
    sfText_setFillColor(text_1, sfWhite);
    sfText_setColor(text_1, sfWhite);
    sfText_setString(text_1, "Emile   Hanau   -   procedural   map   generation   /   enemy   movement");
    text_1_pos.x -= sfText_getGlobalBounds(text_1).width / 2;
    sfText_setPosition(text_1, text_1_pos);

    sfVector2f text_2_pos = {1900 / 2, 1080 + 300 - 50 + 200};
    sfText *text_2 = sfText_create();
    sfText_setOutlineColor(text_2, sfWhite);
    sfText_setFont(text_2, sfFont_createFromFile("resources/ARCADECLASSIC.otf"));
    sfText_setCharacterSize(text_2, 40);
    sfText_setFillColor(text_2, sfWhite);
    sfText_setColor(text_2, sfWhite);
    sfText_setString(text_2, "Florian   Hagen   -   visual   arts");
    text_2_pos.x -= sfText_getGlobalBounds(text_2).width / 2;
    sfText_setPosition(text_2, text_2_pos);

    sfVector2f text_3_pos = {1900 / 2, 1080 + 400 - 50 + 300};
    sfText *text_3 = sfText_create();
    sfText_setOutlineColor(text_3, sfWhite);
    sfText_setFont(text_3, sfFont_createFromFile("resources/ARCADECLASSIC.otf"));
    sfText_setCharacterSize(text_3, 40);
    sfText_setFillColor(text_3, sfWhite);
    sfText_setColor(text_3, sfWhite);
    sfText_setString(text_3, "Hasan   Guezel   -   room   design   /   gameplay   balancing");
    text_3_pos.x -= sfText_getGlobalBounds(text_3).width / 2;
    sfText_setPosition(text_3, text_3_pos);

    sfVector2f text_4_pos = {1900 / 2, 1080 + 500 - 50 + 400};
    sfText *text_4 = sfText_create();
    sfText_setOutlineColor(text_4, sfWhite);
    sfText_setFont(text_4, sfFont_createFromFile("resources/ARCADECLASSIC.otf"));
    sfText_setCharacterSize(text_4, 40);
    sfText_setFillColor(text_4, sfWhite);
    sfText_setColor(text_4, sfWhite);
    sfText_setString(text_4, "Lucas   Hoffer   /   room   design");
    text_4_pos.x -= sfText_getGlobalBounds(text_4).width / 2;
    sfText_setPosition(text_4, text_4_pos);

    sfClock *my_clock = sfClock_create();
    sfClock_restart(my_clock);
    do {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_drawText(window, text_1, NULL);
        sfRenderWindow_drawText(window, text_2, NULL);
        sfRenderWindow_drawText(window, text_3, NULL);
        sfRenderWindow_drawText(window, text_4, NULL);
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfClock_destroy(my_clock);
                sfText_destroy(text);
                sfText_destroy(text_1);
                sfText_destroy(text_2);
                sfText_destroy(text_3);
                sfText_destroy(text_4);
                sfRenderWindow_close(window);
                return;
            }
        }
        text_pos.y -= 0.1;
        text_1_pos.y -= 0.1;
        text_2_pos.y -= 0.1;
        text_3_pos.y -= 0.1;
        text_4_pos.y -= 0.1;
        sfText_setPosition(text, text_pos);
        sfText_setPosition(text_1, text_1_pos);
        sfText_setPosition(text_2, text_2_pos);
        sfText_setPosition(text_3, text_3_pos);
        sfText_setPosition(text_4, text_4_pos);
        sfRenderWindow_display(window);
        while (sfTime_asMilliseconds(sfClock_getElapsedTime(my_clock)) < 1000 / 60) {
            while (sfRenderWindow_pollEvent(window, &event)) {
                if (event.type == sfEvtClosed) {
                    sfClock_destroy(my_clock);
                    sfText_destroy(text);
                    sfText_destroy(text_1);
                    sfText_destroy(text_2);
                    sfText_destroy(text_3);
                    sfText_destroy(text_4);
                    sfRenderWindow_close(window);
                    return;
                }
            }
        }
    } while(text_4_pos.y > -30);
    sfClock_destroy(my_clock);
    sfText_destroy(text);
    sfText_destroy(text_1);
    sfText_destroy(text_2);
    sfText_destroy(text_3);
    sfText_destroy(text_4);
}

void handle_game_loop(sfRenderWindow *window, all_t *objects)
{
    sfEvent event;

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

void draw_minimap(sfRenderWindow *window)
{
    int distance_room_minimap = 30;
    sfVector2f circle_pos = {1620, 70};
    sfVector2f line_pos = {0,0};
    sfVector2f line_dim_left_right = {5, 1};
    sfVector2f line_dim_up_down = {1, 5};
    sfRectangleShape *line_left_right = sfRectangleShape_create();
    sfRectangleShape_setSize(line_left_right, line_dim_left_right);
    sfRectangleShape *line_up_down = sfRectangleShape_create();
    sfRectangleShape_setSize(line_up_down, line_dim_up_down);
    sfRectangleShape_setOutlineThickness(line_left_right, 1);
    sfRectangleShape_setOutlineThickness(line_up_down, 1);
    sfRectangleShape_setOutlineColor(line_left_right, sfWhite);
    sfRectangleShape_setOutlineColor(line_up_down, sfWhite);
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape_setRadius(circle, 10);
    sfCircleShape_setOutlineThickness(circle, 2);
    sfCircleShape_setPosition(circle, circle_pos);
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            sfCircleShape_setOutlineColor(circle, sfWhite);
            sfCircleShape_setFillColor(circle, sfTransparent);
            if (map[j][i]->visited)
                sfCircleShape_setOutlineColor(circle, sfWhite); // sfCircleShape_setFillColor(circle, sfWhite);
            else
                sfCircleShape_setFillColor(circle, sfTransparent);
            if (j == curr_room_x && i == curr_room_y)
                sfCircleShape_setFillColor(circle, sfGreen);
            if (!map[j][i]->visited)
                sfCircleShape_setOutlineColor(circle, sfTransparent);
            /*if ((j - 1 >= 0 && map[j - 1][i]->visited && map[j][i]->directions % LEFT == 0) || (j + 1 <= MAP_HEIGHT - 1 && map[j + 1][i]->visited && map[j][i]->directions % RIGHT == 0) \
            || (i - 1 >= 0 && map[j][i - 1]->visited && map[j][i]->directions % UP == 0) || (i + 1 <= MAP_WIDTH - 1 && map[j][i + 1]->visited && map[j][i]->directions % DOWN == 0))
                0 == 0; //sfCircleShape_setOutlineColor(circle, sfWhite);*/
            if (map[j][i]->is_boss_room) sfCircleShape_setFillColor(circle, sfRed);
            if (map[j][i]->is_marked) sfCircleShape_setFillColor(circle, sfYellow);
            sfRenderWindow_drawCircleShape(window, circle, NULL);
            if (map[j][i]->visited && map[j][i]->directions % LEFT == 0) {
                line_pos.x = circle_pos.x - 7;
                line_pos.y = circle_pos.y + 10;
                sfRectangleShape_setPosition(line_left_right, line_pos);
                sfRenderWindow_drawRectangleShape(window, line_left_right, NULL);
            }
            if (map[j][i]->visited && map[j][i]->directions % RIGHT == 0) {
                line_pos.x = circle_pos.x + 23;
                line_pos.y = circle_pos.y + 10;
                sfRectangleShape_setPosition(line_left_right, line_pos);
                sfRenderWindow_drawRectangleShape(window, line_left_right, NULL);
            }
            if (map[j][i]->visited && map[j][i]->directions % UP == 0) {
                line_pos.x = circle_pos.x + 10;
                line_pos.y = circle_pos.y - 7;
                sfRectangleShape_setPosition(line_up_down, line_pos);
                sfRenderWindow_drawRectangleShape(window, line_up_down, NULL);
            }
            if (map[j][i]->visited && map[j][i]->directions % DOWN == 0) {
                line_pos.x = circle_pos.x + 10;
                line_pos.y = circle_pos.y + 23;
                sfRectangleShape_setPosition(line_up_down, line_pos);
                sfRenderWindow_drawRectangleShape(window, line_up_down, NULL);
            }

            circle_pos.x += distance_room_minimap;
            sfCircleShape_setPosition(circle, circle_pos);
        }
        circle_pos.y += distance_room_minimap;
        circle_pos.x = 1620;
        sfCircleShape_setPosition(circle, circle_pos);
    }
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

    if (DEBUG == 2) {
        if ((sfKeyboard_isKeyPressed(sfKeyX))) {
            init_map();
            curr_room_x = MAP_WIDTH / 2;
            curr_room_y = MAP_HEIGHT / 2;
            load_room(objects, NONE);
        }
        if (sfKeyboard_isKeyPressed(sfKeyNumpad8) ||
            sfKeyboard_isKeyPressed(sfKeyI)) {
            load_room(objects, UP);
        } else if (sfKeyboard_isKeyPressed(sfKeyNumpad2) ||
            sfKeyboard_isKeyPressed(sfKeyK)) {
            load_room(objects, DOWN);
        } else if (sfKeyboard_isKeyPressed(sfKeyNumpad4) ||
            sfKeyboard_isKeyPressed(sfKeyJ)) {
            load_room(objects, LEFT);
        } else if (sfKeyboard_isKeyPressed(sfKeyNumpad6) ||
            sfKeyboard_isKeyPressed(sfKeyL)) {
            load_room(objects, RIGHT);
        }
    }
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_marked) {
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
                        "Hi there!\nHow about we make a deal?\nYou give me your soul(s)\n and i bless you with power.", pos,
                        &objects->dialogue_box,
                        &objects->cur_room->reaper);
                if (check_button_interaction(&objects->dialogue_box.shop,
                    window, 231, 152))
                    objects->dialogue_box.is_shop = 1;
            } else {
                if (check_button_interaction(&objects->dialogue_box.hp, window,
                    231, 152) && objects->player.max_hp < 20) {
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
                        prepare_dialogue_box(objects, "U still broke?\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);

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
                        prepare_dialogue_box(objects, "U still broke?\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
                }
                if (check_button_interaction(&objects->dialogue_box.damage, window, 231, 152)) {
                    if (objects->player.soul_count >= objects->dialogue_box.damage.value) {
                        objects->player.damage += objects->player.damage * 0.075;
                        handle_shop_purchase(&objects->dialogue_box, &objects->player, &objects->dialogue_box.damage, objects);
                    } else
                        prepare_dialogue_box(objects, "U still broke?\n", pos, &objects->dialogue_box, &objects->cur_room->reaper);
                }
                if (check_button_interaction(&objects->dialogue_box.back, window,231, 152))
                    objects->dialogue_box.is_shop = 0;
            }
        }
    }
    if (!DEBUG && map[curr_room_x][curr_room_y]->is_boss_room && !objects->cur_room->is_bossfight) {
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