/*
** EPITECH PROJECT, 2019
** score.c
** File description:
** additional functions to handle score
*/

#include "../include/rpg.h"

void add_points(char *score, int i)
{
    int a;

    if (score[i] == ' ')
        score[i] = '0';
    if (score[i] < '9' && score[i] >= '0')
        score[i]++;
    else if (score[i] == '9') {
        score[i] = '0';
        for (a = 1; score[i - a] == '9'; a++) {
            score[i - a] = '0';
        }
        score[i - a]++;
    }
}

void remove_points(char *score, int i)
{
    int a;

    if (score[i] > '0' && score[i] <= '9' )
        score[i]--;
    else {
        score[i] = '9';
        for (a = 1; score[i - a] == '0'; a++) {
            score[i - a] = '9';
        }
        score[i - a]--;
    }
}