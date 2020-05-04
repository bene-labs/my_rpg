/*
** EPITECH PROJECT, 2019
** my_put_nbr.c
** File description:
** display numbers (within int limit)
*/

#include "../../include/my.h"

int my_put_nbr_base(unsigned int nb, char *base)
{
    unsigned int modulo;
    int len = my_strlen(base);

    if (nb < (unsigned int) len)
        my_putchar(base[nb]);
    if (nb >= (unsigned int) len)
    {
        modulo = nb % len;
        my_put_nbr_base(nb / len, base);
        my_putchar(base[modulo]);
    }
    return (0);
}