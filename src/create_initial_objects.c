/*
** EPITECH PROJECT, 2020
** create_objects
** File description:
** see above
*/

#include "../include/rpg.h"

all_t *create_objects(void)
{
    all_t *objects = malloc(sizeof(all_t));
    objects->cur_room = malloc(sizeof(room_t));
    sfVector2f pos = {800, 500};

    objects->is_mouse_held = 0;
    objects->credits = 0;
    objects->cur_floor = 0;
    objects->cur_room->background_sprite = sfSprite_create();
    objects->die_texture_1 = sfTexture_createFromFile("resources/sprites/enemies/die_1.png", NULL);
    objects->die_texture_2 = sfTexture_createFromFile("resources/sprites/enemies/die_2.png", NULL);
    objects->die_rect = get_rect_arr(9, 1, 92, 100);
    sfSprite_setTexture(objects->cur_room->background_sprite, \
sfTexture_createFromFile("resources/sprites/Floor_1/main_bg.png", \
NULL), sfTrue); //temp
    objects->health_bar_background = sfTexture_createFromFile("resources/sprites/health_bar_background.png", NULL);
    objects->health_bar_foreground = sfTexture_createFromFile("resources/sprites/health_bar_foreground.png", NULL);
    create_room_objects(objects);
    objects->cur_room->is_bossfight = 0;
    create_player_objects(objects);
    create_enemy_templates(objects);
    create_objects_text(objects);
    create_npc_objects(objects);
    objects->drop_door_texture = sfTexture_createFromFile("resources/sprites/down.png", NULL);
    objects->trophy_texture = sfTexture_createFromFile("resources/sprites/trophy.png", NULL);
    objects->cur_room->trophy = sfSprite_create();
    objects->cur_room->trap_door = sfSprite_create();
    sfSprite_setTexture(objects->cur_room->trophy, objects->trophy_texture, sfTrue);
    sfSprite_setTexture(objects->cur_room->trap_door, objects->drop_door_texture, sfTrue);
    sfSprite_setPosition(objects->cur_room->trap_door, pos);
    pos.x += 200;
    sfSprite_setPosition(objects->cur_room->trophy, pos);
    objects->floor_is_won = 0;
    objects->stats.sprite = sfSprite_create();
    objects->stats.texture = sfTexture_createFromFile("resources/Status.png", NULL);
    sfSprite_setTexture(objects->stats.sprite, objects->stats.texture, sfTrue);
    sfVector2f stats = { 5, 1080 - 360};
    sfSprite_setPosition(objects->stats.sprite, stats);
    stats.x += 80;
    stats.y += 25;
    objects->stats.text = sfText_copy(objects->dialogue_box.speed.text);
    sfText_setCharacterSize(objects->stats.text, 28);
    sfText_setPosition(objects->stats.text, stats);
    objects->stats.str = my_strcpy("000.0\n\n00.00\n\n000.0\n\n000.0");
    sfText_setString(objects->stats.text, objects->stats.str);
    objects->stats.s_speed = 0;
    objects->stats.p_speed = 0;
    objects->stats.damage = 0;
    objects->stats.speed = 0;
    update_stats(&objects->player, &objects->stats);
    return (objects);
}

void create_npc_objects(all_t *objects)
{
    sfTexture *button = sfTexture_createFromFile("resources/sprites/npc/button_empty.png", NULL);
    sfVector2f mid = {1920 / 2, 1080 / 2};

    objects->cur_room->reaper.sprite = sfSprite_create();
    objects->cur_room->reaper.type = 1;
    objects->cur_room->reaper.texture = sfTexture_createFromFile("resources/sprites/reaper_simple.png", NULL);
    sfSprite_setTexture(objects->cur_room->reaper.sprite, objects->cur_room->reaper.texture, sfTrue);
    objects->cur_room->statue.sprite = sfSprite_create();
    objects->cur_room->statue.texture = sfTexture_createFromFile("resources/sprites/statue.png", NULL);
    objects->cur_room->statue.type = 2;
    sfSprite_setTexture(objects->cur_room->statue.sprite, objects->cur_room->statue.texture, sfTrue);
    sfSprite_setPosition(objects->cur_room->statue.sprite, mid);
    objects->box_back = sfTexture_createFromFile("resources/sprites/npc/table.png", NULL);
    objects->icon_box = sfTexture_createFromFile("resources/sprites/npc/s_window.png", NULL);
    objects->dialogue_box.icon_background_sprite = sfSprite_create();
    objects->dialogue_box.icon_box_sprite = sfSprite_create();
    sfSprite_setTexture(objects->dialogue_box.icon_background_sprite, objects->box_back, sfTrue);
    sfSprite_setTexture(objects->dialogue_box.icon_box_sprite, objects->icon_box, sfTrue);
    objects->dialogue_box.text = sfText_copy(objects->player.soul_text);
    sfText_setColor(objects->dialogue_box.text, sfWhite);
    sfText_setCharacterSize(objects->dialogue_box.text, 40);
    objects->dialogue_box.is_active = 0;
    objects->dialogue_box.is_shop = 0;
    objects->dialogue_box.icon = sfSprite_create();
    objects->close_texture = sfTexture_createFromFile("resources/sprites/npc/close.png", NULL);
    objects->empty_button_texture = sfTexture_createFromFile("resources/sprites/npc/button_empty.png", NULL);
    objects->dialogue_box.close.sprite = sfSprite_create();
    sfSprite_setTexture(objects->dialogue_box.close.sprite, objects->close_texture, sfTrue);
    objects->dialogue_box.close.is_hovered = 0;
    objects->dialogue_box.close.text = sfText_create();
    objects->dialogue_box.talk.sprite = sfSprite_create();
    objects->dialogue_box.talk.is_hovered = 0;
    objects->dialogue_box.talk.text = sfText_copy(objects->dialogue_box.text);
    objects->dialogue_box.talk.text_gap.x = 75;
    objects->dialogue_box.talk.text_gap.y = 50;
    objects->dialogue_box.talk.gap.x = 10;
    objects->dialogue_box.talk.gap.y = 405;
    sfText_setString(objects->dialogue_box.talk.text, "talk");
    sfSprite_setTexture(objects->dialogue_box.talk.sprite, button, sfTrue);
    objects->dialogue_box.shop.sprite = sfSprite_create();
    objects->dialogue_box.shop.is_hovered = 0;
    objects->dialogue_box.shop.text = sfText_copy(objects->dialogue_box.text);
    objects->dialogue_box.shop.text_gap.x = 75;
    objects->dialogue_box.shop.text_gap.y = 50;
    objects->dialogue_box.shop.gap.x = 550;
    objects->dialogue_box.shop.gap.y = 405;
    sfText_setString(objects->dialogue_box.shop.text, "trade");
    sfSprite_setTexture(objects->dialogue_box.shop.sprite, button, sfTrue);
    objects->dialogue_box.hp.sprite = sfSprite_create();
    objects->dialogue_box.hp.is_hovered = 0;
    objects->dialogue_box.hp.text = sfText_copy(objects->player.soul_text);
    sfText_setCharacterSize(objects->dialogue_box.hp.text, 30);
    objects->dialogue_box.hp.text_gap.x = 30;
    objects->dialogue_box.hp.text_gap.y = 30;
    objects->dialogue_box.hp.gap.x = 15;
    objects->dialogue_box.hp.gap.y = 205;
    objects->dialogue_box.hp.value = 10;
    //objects->dialogue_box.hp.str = "increase max hp\n(10 Souls)";
    sfText_setString(objects->dialogue_box.hp.text, "max hp up and\nheal (10 Souls)");
    sfSprite_setTexture(objects->dialogue_box.hp.sprite, button, sfTrue);
    objects->dialogue_box.speed.sprite = sfSprite_create();
    objects->dialogue_box.speed.is_hovered = 0;
    objects->dialogue_box.speed.text = sfText_copy(objects->player.soul_text);
    sfText_setCharacterSize(objects->dialogue_box.speed.text, 30);
    objects->dialogue_box.speed.text_gap.x = 30;

    objects->dialogue_box.speed.text_gap.y = 30;
    objects->dialogue_box.speed.gap.x = 275;
    objects->dialogue_box.speed.gap.y = 205;
    objects->dialogue_box.speed.value = 5;
    objects->dialogue_box.speed.nb_end = 20;
    objects->dialogue_box.speed.str = my_strcpy("movement speed\nup (00 Souls)");
    for (int i = 0; i < objects->dialogue_box.speed.value; i++)
        add_points(objects->dialogue_box.speed.str, 20);
    sfText_setString(objects->dialogue_box.speed.text, objects->dialogue_box.speed.str);
    sfSprite_setTexture(objects->dialogue_box.speed.sprite, button, sfTrue);
    objects->dialogue_box.fire_rate.sprite = sfSprite_create();
    objects->dialogue_box.fire_rate.is_hovered = 0;
    objects->dialogue_box.fire_rate.text = sfText_copy(objects->player.soul_text);
    sfText_setCharacterSize(objects->dialogue_box.fire_rate.text, 30);
    objects->dialogue_box.fire_rate.text_gap.x = 30;
    objects->dialogue_box.fire_rate.text_gap.y = 30;
    objects->dialogue_box.fire_rate.gap.x = 535;
    objects->dialogue_box.fire_rate.gap.y = 205;
    objects->dialogue_box.fire_rate.value = 7;
    objects->dialogue_box.fire_rate.nb_end = 16;
    objects->dialogue_box.fire_rate.str = my_strcpy("fire-rate up\n (00 Souls)");
    for (int i = 0; i < objects->dialogue_box.fire_rate.value; i++)
        add_points(objects->dialogue_box.fire_rate.str, 16);
    sfText_setString(objects->dialogue_box.fire_rate.text, objects->dialogue_box.fire_rate.str);
    sfSprite_setTexture(objects->dialogue_box.fire_rate.sprite, button, sfTrue);
    objects->dialogue_box.projectile_speed.sprite = sfSprite_create();
    objects->dialogue_box.projectile_speed.is_hovered = 0;
    objects->dialogue_box.projectile_speed.text = sfText_copy(objects->player.soul_text);
    sfText_setCharacterSize(objects->dialogue_box.projectile_speed.text, 30);
    objects->dialogue_box.projectile_speed.text_gap.x = 30;
    objects->dialogue_box.projectile_speed.text_gap.y = 30;
    objects->dialogue_box.projectile_speed.gap.x = 15;
    objects->dialogue_box.projectile_speed.gap.y = 405;
    objects->dialogue_box.projectile_speed.value = 6;
    objects->dialogue_box.projectile_speed.nb_end = 22;
    objects->dialogue_box.projectile_speed.str = my_strcpy("projectile speed\nup (00 Souls)");
    for (int i = 0; i < objects->dialogue_box.projectile_speed.value; i++)
        add_points(objects->dialogue_box.projectile_speed.str, 22);
    sfText_setString(objects->dialogue_box.projectile_speed.text, objects->dialogue_box.projectile_speed.str);
    sfSprite_setTexture(objects->dialogue_box.projectile_speed.sprite, button, sfTrue);
    objects->dialogue_box.damage.sprite = sfSprite_create();
    objects->dialogue_box.damage.is_hovered = 0;
    objects->dialogue_box.damage.text = sfText_copy(objects->player.soul_text);
    sfText_setCharacterSize(objects->dialogue_box.damage.text, 30);
    objects->dialogue_box.damage.text_gap.x = 30;
    objects->dialogue_box.damage.text_gap.y = 30;
    objects->dialogue_box.damage.gap.x = 275;
    objects->dialogue_box.damage.gap.y = 405;
    objects->dialogue_box.damage.value = 8;
    objects->dialogue_box.damage.nb_end = 12;
    objects->dialogue_box.damage.str = my_strcpy("damage up\n(00 Souls)");
    for (int i = 0; i < objects->dialogue_box.damage.value; i++)
        add_points(objects->dialogue_box.damage.str, 12);
    sfText_setString(objects->dialogue_box.damage.text, objects->dialogue_box.damage.str);
    sfSprite_setTexture(objects->dialogue_box.damage.sprite, button, sfTrue);
    objects->dialogue_box.back.sprite = sfSprite_create();
    objects->dialogue_box.back.is_hovered = 0;
    objects->dialogue_box.back.text = sfText_copy(objects->player.soul_text);
    sfText_setCharacterSize(objects->dialogue_box.back.text, 30);
    objects->dialogue_box.back.text_gap.x = 30;
    objects->dialogue_box.back.text_gap.y = 30;
    objects->dialogue_box.back.gap.x = 535;
    objects->dialogue_box.back.gap.y = 405;
    sfText_setString(objects->dialogue_box.back.text, "quit trading");
    sfSprite_setTexture(objects->dialogue_box.back.sprite, button, sfTrue);
}

void create_objects_text(all_t *objects)
{
    sfVector2f mid = {650, 0};
    sfColor soul = {120, 219, 225, 232};

    objects->basic_font = sfFont_createFromFile("resources/Bebas-Regular.otf");
    objects->soul_texture = sfTexture_createFromFile("resources/sprites/Soul.png", NULL);
    objects->x_texture = sfTexture_createFromFile("resources/sprites/x.png", NULL);
    objects->soul_rect = get_rect_arr(4, 1, 56, 60);
    objects->player.soul_string = malloc(sizeof(char) * (8 + 1));
    for (int i = 0; i < 8; i++)
        objects->player.soul_string[i] = '0';
    //objects->player.soul_string[4] = '0';
    objects->player.soul_string[4]= '+';
    //objects->player.soul_string[9] = '0';
    objects->player.soul_string[8] = '\0';
    objects->player.soul_gain = 0;
    objects->player.soul_text = sfText_create();
    sfText_setFont(objects->player.soul_text, objects->basic_font);
    sfText_setPosition(objects->player.soul_text, mid);
    sfText_setColor(objects->player.soul_text, soul);
    sfText_setCharacterSize(objects->player.soul_text, 50);
    mid.x -= 50;
    mid.y += 12;
    objects->x_sprite = sfSprite_create();
    sfSprite_setTexture(objects->x_sprite, objects->x_texture, sfTrue);
    sfSprite_setPosition(objects->x_sprite, mid);
    mid.y -= 12;
    mid.x -= 50;
    objects->soul_sprite = sfSprite_create();
    sfSprite_setTexture(objects->soul_sprite, objects->soul_texture, sfTrue);
    sfSprite_setTextureRect(objects->soul_sprite, objects->soul_rect[0]);
    sfSprite_setPosition(objects->soul_sprite, mid);
    objects->player.soul_count = SOUL_START;
    for (int i = 0; i < SOUL_START; i++)
        add_points(objects->player.soul_string, 3);
    sfText_setString(objects->player.soul_text, objects->player.soul_string);
}

void create_room_objects(all_t *objects)
{
    objects->room_template.wall = sfTexture_createFromFile("resources/sprites/Floor_1/wall_sheet.png", NULL);
    objects->room_template.obstacle_rect = get_rect_arr(3, 3,100, 100);
    objects->room_template.obstacles = sfTexture_createFromFile("resources/sprites/Floor_1/tilesheet_hell.png", NULL);
    objects->room_template.empty = sfTexture_createFromFile("resources/sprites/empty_tile.png", NULL);
}

void create_player_objects(all_t *objects)
{
    int i = 0;
    sfVector2f hearth_pos = {10,10};

    objects->player.body = sfSprite_create();
    objects->player.head = sfSprite_create();
    sfSprite_setTexture(objects->player.body, \
    sfTexture_createFromFile("resources/sprites/player/player_1_body.png", NULL), sfTrue);
    objects->player.scale = sfSprite_getTextureRect(objects->player.body);
    sfSprite_setTexture(objects->player.head, \
sfTexture_createFromFile("resources/sprites/player/player_1_head.png", NULL), sfTrue);
    objects->player.og_color_b = sfSprite_getColor(objects->player.body);
    objects->player.og_color_h = sfSprite_getColor(objects->player.head);
    objects->player.walk_clock = sfClock_create();
    objects->player.shot_clock = sfClock_create();
    objects->player.health = sfTexture_createFromFile("resources/sprites/player/health.png", NULL);
    for (int j = 0; j < 10; j++) {
        objects->player.heart_sprites[j] = sfSprite_create();
        sfSprite_setTexture(objects->player.heart_sprites[j], objects->player.health, sfTrue);
        sfSprite_setPosition(objects->player.heart_sprites[j], hearth_pos);    sfVector2f pos = {800, 540};
        hearth_pos.x += 50.0;
    }
    objects->player.health_rect = get_rect_arr(3, 1, 50, 51);
    objects->player.shot_speed = S_SPEED;
    objects->player.speed = SPEED;
    objects->player.cur_hp = HP;
    objects->player.max_hp = HP;
    refresh_player_lives(&objects->player);
    objects->player.animation_rects= malloc(sizeof(sfIntRect *) * 8);
    for (int height = 0; i < 8; height += 100, i++) {
        objects->player.animation_rects[i] = malloc(sizeof(sfIntRect) * 3);
        for (int j = 0, width = 0; j < 3; width += 96, j++) {
            objects->player.animation_rects[i][j].left = width;
            objects->player.animation_rects[i][j].top = height;
            objects->player.animation_rects[i][j].width = 96;
            objects->player.animation_rects[i][j].height = 100;
        }
    }
    sfSprite_setTextureRect(objects->player.body, objects->player.animation_rects[0][0]);
    sfSprite_setTextureRect(objects->player.head, objects->player.animation_rects[0][0]);
    objects->player.animation.clock = sfClock_create();
    objects->player.animation.frame = 0;
    objects->player.animation.max_frame = 2;
    objects->player.animation.is_reverse = 0;
    objects->player.state = 0;
    objects->player.shoot_state = -1;
    objects->player.projectile.sprites = NULL;
    //objects->player.projectile.speed = 2.0;
    objects->player.projectile.speed = P_SPEED;
    objects->player.projectile.clock = sfClock_create();
    objects->player.projectile.rects = get_rect_arr(8, 1, 30, 30);
    sfVector2f example[4] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
    objects->player.projectile.vectors = malloc(sizeof(sfVector2f) * 4);
    for (int i = 0; i < 4; i++)
        objects->player.projectile.vectors[i] = example[i];
    objects->player.projectile.sprites = malloc(sizeof(projectile_list_t));
    objects->player.projectile.sprites->next = NULL;
    objects->player.projectile_texture = sfTexture_createFromFile("resources/sprites/player/bones.png", NULL);
    objects->player.projectile.animation.clock = sfClock_create();
    objects->player.projectile.animation.frame = 0;
    objects->player.projectile.animation.max_frame = 7;
    objects->player.projectile.animation.delay = 100000;
    objects->player.projectile.is_animated = 1;
    objects->player.projectile.is_hostile = 0;
    objects->player.projectile.damage = DAMAGE;
    objects->player.animate_head = 1;
    objects->player.invincibillity_clock = sfClock_create();
    objects->player.invincibillity_duaration = 0.5;
}

void create_enemy_templates(all_t *objects)
{
    sfVector2f directions[8] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    sfVector2f still = {0, 0};

    objects->enemy_templates[0].texture = sfTexture_createFromFile("resources/sprites/enemies/ghostSheet.png", NULL);
    objects->enemy_templates[0].projectile_directions_per_shot = malloc(sizeof(sfVector2f *));
    objects->enemy_templates[0].projectile_directions_per_shot[0] = malloc(sizeof(sfVector2f) * 9);
    for (int i = 0; i < 9; i++)
        objects->enemy_templates[0].projectile_directions_per_shot[0][i] = directions[i];
    objects->enemy_templates[0].rects = get_rect_arr(3, 4 ,100, 100);
    objects->enemy_templates[0].projectile_speed = 400.0;
    objects->enemy_templates[0].speed = 35;
    objects->enemy_templates[0].movement_type = MOVE_STATIC;
    objects->enemy_templates[0].shots_per_second = 0.5;
    objects->enemy_templates[0].animation.frame = 0;
    objects->enemy_templates[0].animation.max_frame = 12;
    objects->enemy_templates[0].animation.delay = SEC / 6;
    //objects->enemy_templates[0].animation.clock = sfClock_create();
    objects->enemy_templates[0].projectile_formations = 1;
    objects->enemy_templates[0].next_shot = 0;
    objects->enemy_templates[0].souls = 2;
    objects->enemy_projectile_texture = sfTexture_createFromFile("resources/sprites/enemies/projectile.png", NULL);
    objects->enemy_templates[0].projectile_count_per_shot = 8;
    objects->enemy_templates[0].max_hp = 120.0;
    objects->enemy_templates[0].cur_hp = 120.0;
    objects->enemy_templates[0].die = objects->die_texture_1;
    objects->enemy_templates[1].texture = sfTexture_createFromFile("resources/sprites/enemies/ghost_idle.png", NULL);
    objects->enemy_templates[1].projectile_directions_per_shot = malloc(sizeof(sfVector2f *));
    objects->enemy_templates[1].projectile_directions_per_shot[0] = malloc(sizeof(sfVector2f) * 1);
    objects->enemy_templates[1].projectile_directions_per_shot[0][0] = still;
    objects->enemy_templates[1].rects = get_rect_arr(5, 1 ,100, 100);
    objects->enemy_templates[1].projectile_speed = 500.0;
    objects->enemy_templates[1].speed = 66.6;
    objects->enemy_templates[1].movement_type = MOVE_FOLLOW;
    objects->enemy_templates[1].shots_per_second = 0.0;
    objects->enemy_templates[1].animation.frame = 0;
    objects->enemy_templates[1].animation.max_frame = 5;
    objects->enemy_templates[1].animation.delay = SEC / 6;
    //objects->enemy_templates[1].animation.clock = sfClock_create();
    objects->enemy_templates[1].projectile_count_per_shot = 1;
    objects->enemy_templates[1].projectile_formations = 1;
    objects->enemy_templates[1].next_shot = 0;
    objects->enemy_templates[1].max_hp = 66.6;
    objects->enemy_templates[1].cur_hp = 66.6;
    objects->enemy_templates[1].souls = 1;
    objects->enemy_templates[1].die = sfTexture_createFromFile("resources/sprites/enemies/ghost_die.png", NULL);
    objects->enemy_templates[2].texture = sfTexture_createFromFile("resources/sprites/enemies/spike.png", NULL);
    objects->enemy_templates[2].projectile_directions_per_shot = malloc(sizeof(sfVector2f) * 2);
    objects->enemy_templates[2].projectile_directions_per_shot[0] = malloc(sizeof(sfVector2f) * 4);
    objects->enemy_templates[2].projectile_directions_per_shot[1] = malloc(sizeof(sfVector2f) * 4);
    sfVector2f template[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    sfVector2f template_2[4] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
    for (int i = 0; i < 4; i++) {
        objects->enemy_templates[2].projectile_directions_per_shot[0][i] = template[i];
        objects->enemy_templates[2].projectile_directions_per_shot[1][i] = template_2[i];
    }
    objects->enemy_templates[2].rects = get_rect_arr(5, 1 ,100, 100);
    objects->enemy_templates[2].projectile_speed = 333.3;
    objects->enemy_templates[2].speed = 0;
    objects->enemy_templates[2].movement_type = MOVE_STATIC;
    objects->enemy_templates[2].shots_per_second = 0.0;
    objects->enemy_templates[2].animation.frame = 0;
    objects->enemy_templates[2].animation.max_frame = 1;
    objects->enemy_templates[2].animation.delay = SEC / 6;
    //objects->enemy_templates[2].animation.clock = sfClock_create();
    objects->enemy_templates[2].projectile_count_per_shot = 4;
    objects->enemy_templates[2].projectile_formations = 2;
    objects->enemy_templates[2].next_shot = 0;
    objects->enemy_templates[2].max_hp = 167.8;
    objects->enemy_templates[2].souls = 1;
    objects->enemy_templates[2].cur_hp = 167.8;
    objects->enemy_templates[2].die = objects->die_texture_2;
    objects->enemy_templates[3].texture = sfTexture_createFromFile("resources/sprites/enemies/eye.png", NULL);
    objects->enemy_templates[3].projectile_directions_per_shot = malloc(sizeof(sfVector2f *) * 8);
    for (int i = 0; i < 8; i++) {
        objects->enemy_templates[3].projectile_directions_per_shot[i] = malloc(sizeof(sfVector2f) * 2);
        objects->enemy_templates[3].projectile_directions_per_shot[i][0] = directions[i];
        sfVector2f temp = directions[i];
        temp.x *= -1;
        temp.y *= -1;
        objects->enemy_templates[3].projectile_directions_per_shot[i][1] = temp;
    }
    objects->enemy_templates[3].rects = get_rect_arr(4, 2 ,100, 90);
    objects->enemy_templates[3].projectile_speed = 666.6;
    objects->enemy_templates[3].speed = 0;
    objects->enemy_templates[3].movement_type = MOVE_STATIC;
    objects->enemy_templates[3].shots_per_second = 3.0;
    objects->enemy_templates[3].animation.frame = 0;
    objects->enemy_templates[3].animation.max_frame = 12;
    objects->enemy_templates[3].animation.delay = SEC / 6;
    objects->enemy_templates[3].animation.clock = sfClock_create();
    objects->enemy_templates[3].projectile_formations = 8;
    objects->enemy_templates[3].next_shot = 0;
    objects->enemy_templates[3].projectile_count_per_shot = 1;
    objects->enemy_templates[3].max_hp = 120.0;
    objects->enemy_templates[3].cur_hp = 120.0;
    objects->enemy_templates[3].souls = 3;
    objects->enemy_templates[3].die = objects->die_texture_2;
    objects->enemy_templates[4].texture = sfTexture_createFromFile("resources/sprites/enemies/right_hand.png", NULL);
    objects->enemy_templates[4].projectile_directions_per_shot = malloc(sizeof(sfVector2f *));
    objects->enemy_templates[4].projectile_directions_per_shot[0] = malloc(sizeof(sfVector2f) * 9);
    for (int i = 0; i < 9; i++)
        objects->enemy_templates[4].projectile_directions_per_shot[0][i] = directions[i];
    objects->enemy_templates[4].rects = get_rect_arr(1, 1 ,115, 100);
    objects->enemy_templates[4].projectile_speed = 444.4;
    objects->enemy_templates[4].speed = 67.8;
    objects->enemy_templates[4].movement_type = MOVE_RANDOM;
    objects->enemy_templates[4].shots_per_second = 0.0;
    objects->enemy_templates[4].animation.frame = 0;
    objects->enemy_templates[4].animation.max_frame = 0;
    objects->enemy_templates[4].animation.delay = SEC / 6;
    objects->enemy_templates[4].animation.clock = sfClock_create();
    objects->enemy_templates[4].projectile_formations = 1;
    objects->enemy_templates[4].next_shot = 0;
    objects->enemy_templates[4].projectile_count_per_shot = 8;
    objects->enemy_templates[4].max_hp = 178.0;
    objects->enemy_templates[4].cur_hp = 178.0;
    objects->enemy_templates[4].souls = 4;
    objects->enemy_templates[4].die = objects->die_texture_2;
    objects->enemy_templates[5].texture = sfTexture_createFromFile("resources/sprites/enemies/left_hand.png", NULL);
    /*objects->enemy_templates[5].projectile_directions_per_shot = malloc(sizeof(sfVector2f *));
    objects->enemy_templates[5].projectile_directions_per_shot[0] = malloc(sizeof(sfVector2f) * 9);
    for (int i = 0; i < 9; i++)
        objects->enemy_templates[5].projectile_directions_per_shot[0][i] = directions[i];*/
    objects->enemy_templates[5].rects = get_rect_arr(1, 1 ,115, 100);
    objects->enemy_templates[5].projectile_speed = 0.0;
    objects->enemy_templates[5].speed = 120.8;
    objects->enemy_templates[5].movement_type = MOVE_RANDOM;
    objects->enemy_templates[5].shots_per_second = 0.0;
    objects->enemy_templates[5].animation.frame = 0;
    objects->enemy_templates[5].animation.max_frame = 0;
    objects->enemy_templates[5].animation.delay = SEC / 6;
    objects->enemy_templates[5].animation.clock = sfClock_create();
    objects->enemy_templates[5].projectile_formations = 0;
    objects->enemy_templates[5].next_shot = 0;
    objects->enemy_templates[5].projectile_count_per_shot = 0;
    objects->enemy_templates[5].max_hp = 244.4;
    objects->enemy_templates[5].cur_hp = 224.4;
    objects->enemy_templates[5].souls = 3;
    objects->enemy_templates[5].die = objects->die_texture_2;
    objects->enemy_templates[6].texture = sfTexture_createFromFile("resources/sprites/enemies/satan_sheet.png", NULL);
    sfVector2f attack_2[5] = {{-1, 1}, {-0.65, 1}, {0, 1}, {0.65, 1}, {1, 1}};
    sfVector2f attack_3[18] = {{-1, 1}, {-1, 0.9}, {-1, 0.8}, {-1, 0.7}, {-1, 0.6}, {-1, 0.5}, \
{0, 1}, {0, 0.9}, {0, 0.8}, {0, 0.7}, {0, 0.6}, {0, 0.5}, \
{1, 1}, {1, 0.9}, {1, 0.8}, {1, 0.7}, {1, 0.6}, {1, 0.5} };
    sfVector2f attack_4[9] = {{-1, 1}, {-0.75, 1}, {-0.5, 1}, {-0.25, 1}, {0, 1}, {0.25, 1}, {0.5, 1}, {0.75, 1}, {1, 1}};
    objects->enemy_templates[6].projectile_directions_per_shot = malloc(sizeof(sfVector2f *) * 4);
    objects->enemy_templates[6].projectile_directions_per_shot[0] = malloc(sizeof(sfVector2f) * 9);
    for (int i = 0; i < 9; i++)
        objects->enemy_templates[6].projectile_directions_per_shot[0][i] = directions[i];
    objects->enemy_templates[6].projectile_directions_per_shot[1] = malloc(sizeof(sfVector2f) * 5);
    for (int i = 0; i < 5; i++) {
        objects->enemy_templates[6].projectile_directions_per_shot[1][i] = attack_2[i];
    }
    objects->enemy_templates[6].projectile_directions_per_shot[2] = malloc(sizeof(sfVector2f) * 18);
    objects->enemy_templates[6].projectile_directions_per_shot[3] = malloc(sizeof(sfVector2f) * 9);
    for (int i = 0; i < 18; i++)
        objects->enemy_templates[6].projectile_directions_per_shot[2][i] = attack_3[i];
    for (int i = 0; i < 9; i++)
        objects->enemy_templates[6].projectile_directions_per_shot[3][i] = attack_4[i];
    objects->enemy_templates[6].rects = get_rect_arr(4, 1 ,266, 140);
    objects->enemy_templates[6].projectile_speed = 333.6;
    objects->enemy_templates[6].speed = 96.6;
    objects->enemy_templates[6].movement_type = MOVE_FOLLOW_X;
    objects->enemy_templates[6].shots_per_second = 0.89;
    objects->enemy_templates[6].animation.frame = 0;
    objects->enemy_templates[6].animation.max_frame = 0;
    objects->enemy_templates[6].animation.delay = SEC / 6;
    objects->enemy_templates[6].animation.clock = sfClock_create();
    objects->enemy_templates[6].projectile_formations = 4;
    objects->enemy_templates[6].next_shot = 0;
    objects->enemy_templates[6].projectile_count_per_shot = 1.5;
    objects->enemy_templates[6].max_hp = 666.6;
    objects->enemy_templates[6].cur_hp = 666.6;
    objects->enemy_templates[6].souls = 13;
    objects->enemy_templates[6].die = objects->die_texture_1;
    int temp[4] = {9, 5, 18, 9};
    for (int i = 0; i < 4; i++)
        objects->enemy_templates[6].projectile_count_per_shot_arr[i] = temp[i];
}

sfIntRect *get_rect_arr(int columns, int rows, int width, int height)
{
    sfIntRect *rect = malloc(sizeof(sfIntRect) * columns * rows);
    int d = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++, d++) {
            rect[d].height = height;
            rect[d].width = width;
            rect[d].top = y * height;
            rect[d].left = x * width;
        }
    }
    return (rect);
}

sfIntRect *get_rect_arr_mirrored(int columns, int rows, int width, int height)
{
    sfIntRect *rect = malloc(sizeof(sfIntRect) * columns * rows);
    int d = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = columns - 1; x >= 0; x--, d++) {
            rect[d].height = height;
            rect[d].width = width;
            rect[d].top = y * height;
            rect[d].left = x * width;
        }
    }
    return (rect);
}