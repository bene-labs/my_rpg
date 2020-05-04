//
// Created by benedikt on 4/30/20.
//

#include "../include/rpg.h"

int is_colision_between_two_sprites(sfSprite *first, sfSprite *second, double x_gap, double y_gap)
{
    sfVector2f pos_1 = sfSprite_getPosition(first);
    sfVector2f pos_2 = sfSprite_getPosition(second);

    if (pos_1.x + x_gap >= pos_2.x && pos_1.x <= pos_2.x + x_gap \
    && pos_1.y  + y_gap >= pos_2.y && pos_1.y <= pos_2.y + y_gap)
        return (1);
    return (0);
}