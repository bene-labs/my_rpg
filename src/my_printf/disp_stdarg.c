/*
** EPITECH PROJECT, 2019
** disp_stdarg.c
** File description:
** displays the ... arguments according to flags and modifiers
*/

#include "../../include/my.h"

void disp_chararg(va_list args, int width, char *modifiers)
{
    char c;
    int diff = 0;

    c = va_arg(args, int);
    if (width > 0)
        diff = width - 1;
    if (modifiers[0] == 'l')
        my_putchar(c);
    for (int i = diff; i > 0; i--)
        write(1, " ", 1);
    if (modifiers[0] == 'r')
        my_putchar(c);
}

void disp_intarg(va_list args, int width, char *modifiers)
{
    int nb;

    nb = va_arg(args, int);
    if ((nb >= 0 && modifiers[3] != '0' && modifiers[0] == 'l') \
|| (nb >= 0 && modifiers[3] != '0' && modifiers[1] == '0') \
|| (nb >= 0 && modifiers[3] != '0' && width <= 0)) {
        my_putchar(modifiers[3]);
        width--;
    }
    if (nb < 0)
        width--;
    if (width > 0) {
        disp_intpadd(nb, width, modifiers);
        return;
    }
    my_put_nbr(nb);
}

void disp_intpadd(int nb,  int diff, char *modifiers)
{
    int test_nb = nb;

    if (nb < 0)
        test_nb = nb * -1;
    for (; test_nb > 0 && diff > 0; diff--)
        test_nb /= 10;
    if (modifiers[0] == 'l')
        my_put_nbr(nb);
    else if (modifiers[1] == '0' && nb >= 0) {
        my_putchar(modifiers[3]);
        diff--;
    }
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[3] != '0' && nb >= 0 && modifiers[1] != '0' \
&& modifiers[0] == 'r')
        my_putchar(modifiers[3]);
    if (modifiers[0] == 'r')
        my_put_nbr(nb);
}

void disp_strarg(va_list args, int width, char *modifiers)
{
    char *str;
    int diff = 0;

    str = va_arg(args, char *);
    if (width > 0) {
        diff = width - my_strlen(str);
    }
    if (modifiers[0] == 'l')
        my_putstr(str);
    for (; diff > 0; diff--)
        write(1, " ", 1);
    if (modifiers[0] == 'r')
        my_putstr(str);
}

void disp_usintarg(va_list args, int width, char *modifiers)
{
    unsigned int nb;
    if (width > 0) {
        disp_usintpadd(args, width, modifiers);
        return;
    }
    nb = va_arg(args, unsigned int);
    my_put_nbr_base(nb, "0123456789");
}