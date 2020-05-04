/*
** EPITECH PROJECT, 2019
** disp_stdarg.c
** File description:
** displays the ... arguments according to flags and modifiers
*/

#include "../../include/my.h"

void disp_adrarg(va_list args, int width, char *modifiers)
{
    unsigned int adress;

    adress = va_arg(args, unsigned int);
    if ((modifiers[3] != '0' && modifiers[0] == 'l') \
|| (modifiers[3] != '0' && modifiers[1] == '0') \
|| (modifiers[3] != '0' && width <= 0)) {
        my_putchar(modifiers[3]);
        width--;
    }
    if (modifiers[0] == 'l' && width > 0) {
        write(1, "0x", 2);
        my_put_nbr_base(adress, "0123456789abcdef");
    }
    if (width > 0) {
        disp_adrpadd(adress, width, modifiers);
        return;
    }
    write(1, "0x", 2);
    my_put_nbr_base(adress, "0123456789abcdef");
}

void disp_adrpadd(int nb, int width, char *modifiers)
{
    int test_nb = nb;
    int diff = width;

    while (test_nb > 0 && diff > 0) {
        test_nb /= 10;
        diff--;
    }
    if (modifiers[1] == '0' && nb >= 0) {
        my_putchar(modifiers[3]);
        diff--;
    }
    for (; diff > 0; diff--)
        my_putchar(modifiers[1]);
    if (modifiers[3] != '0' && nb >= 0 && modifiers[1] != '0' \
&& modifiers[0] == 'r')
        my_putchar(modifiers[3]);
    if (modifiers[0] == 'r') {
        write(1, "0x", 2);
        my_put_nbr_base(nb, "0123456789abcdef");
    }
}

void disp_spstrarg(va_list args, int width, char *modifiers)
{
    char *str;

    str = va_arg(args, char *);
    width -= my_strlen(str);
    if (width > 0)
        width = get_diff_spstr(str, width);
    if (modifiers[0] == 'l' || width <= 0) {
        for (int i = 0; str[i] != '\0'; i++)
            disp_spstrchar(str[i]);
    }
    for (; width > 0; width--)
        write(1, " ", 1);
    if (modifiers[0] == 'r') {
        for (int i = 0; str[i] != '\0'; i++)
            disp_spstrchar(str[i]);
    }
}

int get_diff_spstr(char *str, int diff)
{
    int nb;
    int digits = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        nb = (int) str[i];
        while ((str[i] < 32 && nb > 0) || (str[i] >= 127 && nb > 0)) {
            nb /= 8;
            diff--;
            digits++;
        }
        if (str[i] < 8)
            diff--;
        if (str[i] < 64)
            diff--;
        if (str[i] < 32 && digits == 0 && nb == 0)
            diff--;
    }
    return (diff);
}

void disp_spstrchar(char str)
{
    unsigned int nb;

    if (str < 32 || str >= 127) {
        nb = (unsigned int) str;
        my_putstr("\\");
        if (nb < 8)
            write(1, "0", 1);
        if (nb < 64)
            write(1, "0", 1);
        my_put_nbr_base(nb, "01234567");
    } else
        my_putchar(str);
}