//
// Created by benedikt on 3/11/20.
//

#include "../include/rpg.h"

int check_button_interaction(button_t *button, sfRenderWindow *window, int height, int width)
{
    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window),
        sfSprite_getPosition(button->sprite), height, width)) {
        if (button->is_hovered == 0) {
            button->is_hovered = 1;
            sfSprite_setScale(button->sprite, up);
            sfText_setScale(button->text, up);
        } if (sfMouse_isButtonPressed(sfMouseLeft))
            return (1);
    } else if (button->is_hovered == 1) {
        button->is_hovered = 0;
        sfSprite_setScale(button->sprite, def);
        sfText_setScale(button->text, def);
    }
    return (0);
}

int is_collision_cursor_button(sfVector2i pos_cursor, sfVector2f pos_button, int height, int width)
{
    if (pos_cursor.y >= pos_button.y && \
        pos_cursor.y <= pos_button.y + height && \
        pos_cursor.x >= pos_button.x &&
        pos_cursor.x <= pos_button.x + width)
        return (1);
    return (0);
}

int is_sprite_inside_radius(sfSprite *sprite, double radius, int origin_x, int origin_y)
{
    if (sqrt(pow(((sfSprite_getPosition(sprite).x + 50) - (origin_x)), 2) +
        pow(((sfSprite_getPosition(sprite).y + 50) - (origin_y)), 2)) <=
        radius * 10) {
        //printf("Abstand: %fpx\t", sqrt(pow(((enemy.position.x + 50) - (spot.position.x + 50)), 2) +
        //    pow(((enemy.position.y + 50) - (spot.position.y + 50)), 2)));
        return (1);
    }
    return (0);
}

int is_mouse_inside_radius(sfVector2i mouse_pos, double radius, sfVector2f position)
{
    if (sqrt(pow(((mouse_pos.x + 50) - (position.x + 50)), 2) +
        pow(((mouse_pos.y + 50) - (position.y + 50)), 2)) <=
        radius * 10) {
        //printf("Abstand: %fpx\t", sqrt(pow(((enemy.position.x + 50) - (spot.position.x + 50)), 2) +
        //    pow(((enemy.position.y + 50) - (spot.position.y + 50)), 2)));
        return (1);
    }
    return (0);
}