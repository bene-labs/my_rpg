//
// Created by benedikt on 5/24/20.
//

#include "../include/rpg.h"

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