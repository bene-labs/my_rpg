/*
** EPITECH PROJECT, 2019
** disp_stdarg.c
** File description:
** displays the ... arguments according to flags and modifiers
*/

#include "../../include/my.h"

void disp_usintpadd(va_list args, int width, char *modifiers)
{
    unsigned int nb;
    unsigned int test_nb;
    int diff = width;

    nb = va_arg(args, unsigned int);
    test_nb = nb;
    while (test_nb > 0) {
        test_nb /= 10;
        diff--;
    }
    if (modifiers[0] == 'l')
        my_put_nbr_base(nb, "0123456789");
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[0] == 'r')
        my_put_nbr_base(nb, "0123456789");
}

void disp_octarg(va_list args, int width, char *modifiers)
{
    unsigned int nb;

    nb = va_arg(args, unsigned int);
    if ((modifiers[2] == '1' && modifiers[0] == 'l') || (modifiers[2] == '1' \
&& width < 0)) {
        write(1, "0", 1);
        width--;
    }
    if (width > 0) {
        disp_octpadd(nb, width, modifiers);
        return;
    }
    my_put_nbr_base(nb, "01234567");
}

void disp_octpadd(unsigned int nb, int width, char *modifiers)
{
    unsigned int test_nb;
    int diff = width;

    test_nb = nb;
    while (test_nb > 0) {
        test_nb /= 8;
        diff--;
    }
    if (modifiers[0] == 'l')
        my_put_nbr_base(nb, "01234567");
    if (modifiers[2] == '1' && modifiers[0] == 'r')
        diff--;
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[2] == '1' && modifiers[0] == 'r')
        write(1, "0", 1);
    if (modifiers[0] == 'r')
        my_put_nbr_base(nb, "01234567");
}

void disp_hexarg(va_list args, int width, char *modifiers)
{
    unsigned int nb;

    nb = va_arg(args, unsigned int);
    if ((modifiers[2] == '1' && modifiers[0] == 'l') || (modifiers[2] == '1' \
&& width < 0)) {
        write(1, "0x", 2);
        width--;
    }
    if (width > 0) {
        disp_hexpadd(nb, width, modifiers);
        return;
    }
    my_put_nbr_base(nb, "0123456789abcdef");
}

void disp_hexpadd(unsigned int nb, int width, char *modifiers)
{
    unsigned int test_nb;
    int diff = width;

    test_nb = nb;
    while (test_nb > 0) {
        test_nb /= 15;
        diff--;
    }
    if (modifiers[0] == 'l')
        my_put_nbr_base(nb, "0123456789abcdef");
    if (modifiers[2] == '1' && modifiers[0] == 'r')
        diff--;
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[2] == '1' && modifiers[0] == 'r')
        write(1, "0x", 2);
    if (modifiers[0] == 'r')
        my_put_nbr_base(nb, "0123456789abcdef");
}