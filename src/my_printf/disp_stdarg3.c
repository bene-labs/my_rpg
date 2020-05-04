/*
** EPITECH PROJECT, 2019
** disp_stdarg.c
** File description:
** displays the ... arguments according to flags and modifiers
*/

#include "../../include/my.h"

void disp_up_hexarg(va_list args, int width, char *modifiers)
{
    unsigned int nb;

    nb = va_arg(args, unsigned int);
    if ((modifiers[2] == '1' && modifiers[0] == 'l') || (modifiers[2] == '1' \
&& width < 0)) {
        write(1, "0X", 2);
        width--;
    }
    if (width > 0) {
        disp_up_hexpadd(nb, width, modifiers);
        return;
    }
    my_put_nbr_base(nb, "0123456789ABCDEF");
}

void disp_up_hexpadd(unsigned int nb, int width, char *modifiers)
{
    unsigned int test_nb;
    int diff = width;

    test_nb = nb;
    while (test_nb > 0) {
        test_nb /= 15;
        diff--;
    }
    if (modifiers[0] == 'l')
        my_put_nbr_base(nb, "0123456789ABCDEF");
    if (modifiers[2] == '1' && modifiers[0] == 'r')
        diff--;
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[2] == '1' && modifiers[0] == 'r')
        write(1, "0X", 2);
    if (modifiers[0] == 'r')
        my_put_nbr_base(nb, "0123456789ABCDEF");
}

void disp_binarg(va_list args, int width, char *modifiers)
{
    unsigned int nb;

    nb = va_arg(args, unsigned int);
    if (width > 0) {
        disp_binpadd(nb, width, modifiers);
        return;
    }
    my_put_nbr_base(nb, "01");
}

void disp_binpadd(unsigned int nb, int diff, char * modifiers)
{
    int test_nb;

    test_nb = (int) nb;
    while (test_nb > 0) {
        test_nb /= 2;
        diff--;
    }
    if (modifiers[0] == 'l')
        my_put_nbr_base(nb, "01");
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[0] == 'r')
        my_put_nbr_base(nb, "01");
}

int get_width(const char *format, int *i)
{
    int len = 0;
    char *nb;
    int b = i[0];
    int width = 0;

    for (; format[len] != '\0'; len++);
    nb = malloc(sizeof(char) * (len - 1) + 1);
    for (int a = 0; format[b] >= '0' && format[b] <= '9'; a++) {
        nb[a] = format[b];
        b++;
        i[0]++;
    }
    width = my_getnbr(nb);
    return (width);
}