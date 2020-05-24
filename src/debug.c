//
// Created by benedikt on 5/24/20.
//

#include "../include/rpg.h"

void debug_map(all_t *objects)
{
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