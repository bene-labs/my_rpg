/*
** EPITECH PROJECT, 2019
** sum_stdarg.c
** File description:
** returns sum of last nb char or int
*/

#include <stdarg.h>
#include "../../include/my.h"

int sum_stdarg(int i, int nb, ...)
{
    va_list args;

    va_start(args, nb);
    if (i == 0)
        return (sum_intarg(nb, args));
    else if (i == 1)
        return (sum_chararg(nb, args));
    return (0);
}

int sum_intarg(int nb, va_list args)
{
    int arg_nb;
    int result = 0;

    for (int a = 0; a < nb; a++) {
        arg_nb = va_arg(args, int);
        result += arg_nb;
    }
    va_end(args);
    return (result);
}

int sum_chararg(int nb, va_list args)
{
    int arg_nb;
    int result = 0;
    char *temp;

    for (int a = 0; a < nb; a++) {
        temp = va_arg(args, char *);
        for (int b = 0; temp[b] != '\0'; b++)
            result++;
    }
    va_end(args);
    return (result);
}