//
// Created by benedikt on 5/2/20.
//

#include "../include/rpg.h"

void prepare_dialogue_box(all_t *objects, char *str, sfVector2f position, dialogue_box_t *dialogueBox, npc_t *npc)
{
    sfText_setString(dialogueBox->text, str);
    sfVector2f og_position = position;

    dialogueBox->is_active = 1;
    sfSprite_setPosition(dialogueBox->icon_background_sprite, position);
    sfSprite_setPosition(dialogueBox->icon_box_sprite, position);
    position.x += 720;
    sfSprite_setPosition(dialogueBox->close.sprite, position);
    position.x -= 700;
    position.y += 5;
    sfSprite_setTexture(dialogueBox->icon, npc->texture, sfTrue);
    sfSprite_setPosition(dialogueBox->icon, position);
    position.x += 110;
    sfText_setPosition(dialogueBox->text, position);
    sfSprite_setPosition(dialogueBox->talk.sprite, og_position);
    sfSprite_move(dialogueBox->talk.sprite, dialogueBox->talk.gap);
    sfText_setPosition(dialogueBox->talk.text, sfSprite_getPosition(dialogueBox->talk.sprite));
    sfText_move(dialogueBox->talk.text, dialogueBox->talk.text_gap);
    if (npc->type == 1) {
        sfText_setString(dialogueBox->shop.text, "trade");
        sfText_setColor(dialogueBox->shop.text, sfWhite);
    }
    else if (npc->type == 2) {
        sfText_setString(dialogueBox->shop.text, "fight.");
        sfText_setColor(dialogueBox->shop.text, sfRed);
    }
    sfSprite_setPosition(dialogueBox->shop.sprite, og_position);
    sfSprite_move(dialogueBox->shop.sprite, dialogueBox->shop.gap);
    sfText_setPosition(dialogueBox->shop.text, sfSprite_getPosition(dialogueBox->shop.sprite));
    sfText_move(dialogueBox->shop.text, dialogueBox->shop.text_gap);
    sfSprite_setPosition(dialogueBox->hp.sprite, og_position);
    sfSprite_move(dialogueBox->hp.sprite, dialogueBox->hp.gap);
    sfText_setPosition(dialogueBox->hp.text, sfSprite_getPosition(dialogueBox->hp.sprite));
    sfText_move(dialogueBox->hp.text, dialogueBox->hp.text_gap);
    sfSprite_setPosition(dialogueBox->speed.sprite, og_position);
    sfSprite_move(dialogueBox->speed.sprite, dialogueBox->speed.gap);
    sfText_setPosition(dialogueBox->speed.text, sfSprite_getPosition(dialogueBox->speed.sprite));
    sfText_move(dialogueBox->speed.text, dialogueBox->speed.text_gap);
    sfSprite_setPosition(dialogueBox->fire_rate.sprite, og_position);
    sfSprite_move(dialogueBox->fire_rate.sprite, dialogueBox->fire_rate.gap);
    sfText_setPosition(dialogueBox->fire_rate.text, sfSprite_getPosition(dialogueBox->fire_rate.sprite));
    sfText_move(dialogueBox->fire_rate.text, dialogueBox->fire_rate.text_gap);
    sfSprite_setPosition(dialogueBox->projectile_speed.sprite, og_position);
    sfSprite_move(dialogueBox->projectile_speed.sprite, dialogueBox->projectile_speed.gap);
    sfText_setPosition(dialogueBox->projectile_speed.text, sfSprite_getPosition(dialogueBox->projectile_speed.sprite));
    sfText_move(dialogueBox->projectile_speed.text, dialogueBox->projectile_speed.text_gap);
    sfSprite_setPosition(dialogueBox->damage.sprite, og_position);
    sfSprite_move(dialogueBox->damage.sprite, dialogueBox->damage.gap);
    sfText_setPosition(dialogueBox->damage.text, sfSprite_getPosition(dialogueBox->damage.sprite));
    sfText_move(dialogueBox->damage.text, dialogueBox->damage.text_gap);
    sfSprite_setPosition(dialogueBox->back.sprite, og_position);
    sfSprite_move(dialogueBox->back.sprite, dialogueBox->back.gap);
    sfText_setPosition(dialogueBox->back.text, sfSprite_getPosition(dialogueBox->back.sprite));
    sfText_move(dialogueBox->back.text, dialogueBox->back.text_gap);
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