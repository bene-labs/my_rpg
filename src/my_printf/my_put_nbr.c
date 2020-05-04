/*
** EPITECH PROJECT, 2019
** my_put_nbr.c
** File description:
** display numbers (within int limit)
*/

#include "../../include/my.h"

int my_put_nbr(int nb)
{
    int modulo;

    if (nb < 0) {
        my_putchar('-');
        nb = nb * (- 1);
    }
    if (nb <= 9 && nb >= 0)
        my_putchar(nb + '0');
    if (nb > 9)
    {
        modulo = nb % 10;
        my_put_nbr(nb / 10);
        my_putchar(modulo + '0');
    }
    return (0);
}

int my_put_nbr_long(long nb)
{
    long modulo;

    if (nb < 0) {
        my_putchar('-');
        nb = nb * (- 1);
    }
    if (nb <= 9 && nb >= 0)
        my_putchar(nb + '0');
    if (nb > 9)
    {
        modulo = nb % 10;
        my_put_nbr(nb / 10);
        my_putchar(modulo + '0');
    }
    return (0);
}