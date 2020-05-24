//
// Created by benedikt on 5/24/20.
//

#include "../include/rpg.h"

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
                sfCircleShape_setOutlineColor(circle, sfWhite);
            else
                sfCircleShape_setFillColor(circle, sfTransparent);
            if (j == curr_room_x && i == curr_room_y)
                sfCircleShape_setFillColor(circle, sfGreen);
            if (!map[j][i]->visited)
                sfCircleShape_setOutlineColor(circle, sfTransparent);
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