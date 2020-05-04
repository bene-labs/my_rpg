//
// Created by benedikt on 4/26/20.
//

#include "../include/rpg.h"
#include <stdio.h>

char *concat_strings(char *str1, char *str2)
{
    char *result = malloc(sizeof(char) * (my_strlen(str1) + \
my_strlen(str2)) + 1);
    int d = 0;

    if (str2 == NULL || str1 == NULL)
        return (str1);
    for (; str1[d] != '\0'; d++)
        result[d] = str1[d];
    for (int i = 0; str2[i] != '\0'; i++) {
        result[d] = str2[i];
        d++;
    }
    result[d] = '\0';
    return (result);
}

char *int_to_str(int nb)
{
    char *str = 0;
    int nb_size = 0;
    int is_negative = 0;

    if (nb < 0) {
        nb_size++;
        nb *= -1;
        is_negative = 1;
    }
    for (int i = nb; i > 0; i /= 10, nb_size++);
    if (nb_size == 0) {
        str = malloc(sizeof(char) + 1);
        str[0] = '0';
        str[1] = '\0';
        return (str);
    }
    str = malloc(sizeof(char) * nb_size + 1);
    str[nb_size] = '\0';
    for (int i = 0; i < nb_size; str[i] = '0', i++);
    for (int i = 0; i < nb; i++)
        add_points(str, nb_size - 1);
    if (is_negative) str[0] = '-';
    return (str);
}