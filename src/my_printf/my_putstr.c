/*
** EPITECH PROJECT, 2019
** my_putstr.c
** File description:
** displays a string char by char (->until \0)
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i += 1;
    }
    return (0);
}