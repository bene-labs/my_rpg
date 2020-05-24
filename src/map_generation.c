/*
** EPITECH PROJECT, 2020
** rpg.h
** File description:
** header
*/

#include "../include/rpg.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

void debug_print(void)
{
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < MAP_WIDTH; k++) {
                my_printf("%s", map[k][i]->arr[j]);
            }
            my_printf("\n");
        }
    }
}

void set_next_coordinates(int *delta_x, int *delta_y, int direction)
{
    switch (direction) {
    case LEFT:
        (*delta_x)--;
        break;
    case RIGHT:
        (*delta_x)++;
        break;
    case UP:
        (*delta_y)--;
        break;
    case DOWN:
        (*delta_y)++;
        break;
    default:
        break;
    }
}

void fill_map(int x, int y, int direction)
{
    int directions[4] = {LEFT, UP, DOWN, RIGHT};
    int forbidden = 0;
    int next_direction;
    int next_x = x;
    int next_y = y;
    int handled_directions = 1;
    time_t t;

    srand((unsigned) time(&t));
    if (direction != NONE) {
        while (directions[forbidden] != direction)
            forbidden++;
        forbidden = directions[3 - forbidden];
        map[x][y]->directions *= forbidden;
        handled_directions *= forbidden;
    }
    while (handled_directions != LEFT * RIGHT * UP * DOWN) {
        do    //debug_print();
            next_direction = directions[rand() % 4];
        while (handled_directions % next_direction == 0);
        next_x = x;
        next_y = y;
        set_next_coordinates(&next_x, &next_y, next_direction);
        handled_directions *= next_direction;
        if (next_x < 0 || next_y < 0 || next_x > MAP_WIDTH - 1 || \
next_y > MAP_HEIGHT - 1 || map[next_x][next_y]->directions != 1)
            continue;
        map[x][y]->directions *= next_direction;
        fill_map(next_x, next_y, next_direction);
    }
}

char **get_room_arr_from_file(char *file_path)
{
    FILE *fd = fopen(file_path, "r");
    int height = 0;
    char *curr_line = 0;
    size_t n = 0;
    char **res;

    while (getline(&curr_line, &n, fd) > 0)
        height++;
    res = malloc(sizeof(char *) * height + 1);
    fclose(fd);
    fd = fopen(file_path, "r");
    for (int i = 0; i < height; i++) {
        curr_line = 0;
        n = 0;
        if (0 >= getline(&curr_line, &n, fd))
            break;
        res[i] = curr_line;
        if (res[i][my_strlen(curr_line) - 1] != '#')
            res[i][my_strlen(curr_line) - 1] = 0;
    }
    res[height] = 0;
    fclose(fd);
    return res;
}

void load_rooms_into_map(void)
{
    char *file_path;
    int nb_rooms = 0;
    int fd;
    time_t t;

    srand((unsigned) time(&t));
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            while (1) {
                file_path = concat_strings("resources/rooms/",
                    int_to_str(map[i][j]->directions));
                file_path = concat_strings(file_path, "/");
                file_path = concat_strings(file_path, int_to_str(nb_rooms));
                if ((fd = open(file_path, O_RDONLY)) >= 0) {
                    nb_rooms++;
                    close(fd);
                } else {
                    free(file_path);
                    break;
                }
            }
            file_path = concat_strings("resources/rooms/",
                int_to_str(map[i][j]->directions));
            file_path = concat_strings(file_path, "/");
            if (i == MAP_WIDTH / 2 && j == MAP_HEIGHT / 2 || map[i][j]->is_boss_room || map[i][j]->is_marked) {
                nb_rooms = 1;
                map[i][j]->cleared = 1;
            }
            file_path = concat_strings(file_path, int_to_str(rand() % nb_rooms));
            map[i][j]->arr = get_room_arr_from_file(file_path);
            free(file_path);
            nb_rooms = 0;
        }
    }
}

void make_imperfect(void)
{
    time_t t;
    int additional_direction = NONE;
    int additional_direction_key = 0;
    int directions[4] = {LEFT, UP, DOWN, RIGHT};
    int next_x;
    int next_y;

    srand((unsigned) time(&t));
    for (int i = 1; i < MAP_WIDTH - 1; i++) {
        for (int j = 1; j < MAP_HEIGHT - 1; j++) {
            additional_direction_key = rand() % 4;
            additional_direction = directions[additional_direction_key];
            if (map[i][j]->directions % additional_direction != 0) {
                next_x = i;
                next_y = j;
                set_next_coordinates(&next_x, &next_y, additional_direction);
                map[i][j]->directions *= additional_direction;
                if (map[next_x][next_y]->directions % directions[3 - additional_direction_key] != 0)
                   map[next_x][next_y]->directions *= directions[3 - additional_direction_key];
            }
        }
    }
}

void init_map(void)
{
    time_t t;

    srand((unsigned) time(&t));
    map = malloc(sizeof(room_t **) * MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; i++) {
        map[i] = malloc(sizeof(room_t *) * MAP_HEIGHT);
        for (int j = 0; j < MAP_HEIGHT; j++) {
            map[i][j] = malloc(sizeof(room_t));
            map[i][j]->directions = 1;
            map[i][j]->arr = 0;
            map[i][j]->width = 0;
            map[i][j]->height = 0;
            map[i][j]->is_boss_room = 0;
            map[i][j]->cleared = 0;
            map[i][j]->is_marked = 0;
            if (i != MAP_WIDTH / 2 || j != MAP_HEIGHT / 2)
                map[i][j]->visited = 0;
            else
                map[i][j]->visited = 1;
        }
    }
    fill_map(curr_room_x, curr_room_y, NONE);
    map[rand() % (MAP_WIDTH - 2) + 1][rand() % (MAP_HEIGHT - 2) + 1]->is_marked = 1;
    while (map[MAP_WIDTH / 2][MAP_HEIGHT / 2]->is_marked) {
        map[MAP_WIDTH / 2][MAP_HEIGHT / 2]->is_marked = 0;
        map[rand() % (MAP_WIDTH - 2) + 1][rand() % (MAP_HEIGHT - 2) + 1]->is_marked = 1;
    }
    map[(rand() % 2) * (MAP_WIDTH - 1)][(rand() % 2) * (MAP_HEIGHT - 1)]->is_boss_room = 1;
    make_imperfect();
    load_rooms_into_map();
}