/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** prints text and variable contents to stdout
*/

#include "../../include/my.h"

int my_printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            handle_modifiers(format, &i, args);
        else
            my_putchar(format[i]);
    }
    va_end(args);
    return (0);
}

flags* get_flag_arr(void)
{
    flags* flag_arr = malloc(sizeof(flags) * 11 + 1);
    flag_arr[0].flag = 'd';
    flag_arr[0].function = disp_intarg;
    flag_arr[1].flag = 'i';
    flag_arr[1].function = disp_intarg;
    flag_arr[2].flag = 'c';
    flag_arr[2].function = disp_chararg;
    flag_arr[3].flag = 'p';
    flag_arr[3].function = disp_adrarg;
    flag_arr[4].flag = 'x';
    flag_arr[4].function = disp_hexarg;
    flag_arr[5].flag = 'X';
    flag_arr[5].function = disp_up_hexarg;
    flag_arr[6].flag = 'o';
    flag_arr[6].function = disp_octarg;
    flag_arr[7].flag = 's';
    flag_arr[7].function = disp_strarg;
    flag_arr = get_flag_arr2(flag_arr);
    return (flag_arr);
}

flags* get_flag_arr2(flags* flag_arr)
{
    flag_arr[8].flag = 'u';
    flag_arr[8].function = disp_usintarg;
    flag_arr[9].flag = 'b';
    flag_arr[9].function = disp_binarg;
    flag_arr[10].flag = 'S';
    flag_arr[10].function = disp_spstrarg;
    return (flag_arr);
}

int handle_modifiers(const char *format, int *i, va_list args)
{
    char modifiers[4] = {'r', ' ', '0', '0'};

    i[0]++;
    for ( ; format[i[0]] == '0' || format[i[0]] == '+' || format[i[0]] == '#' \
|| format[i[0]] == '-' || format[i[0]] == 32; i[0]++) {
        if (format[i[0]] == '0' && modifiers[0] != 'l')
                modifiers[1] = '0';
        if (format[i[0]] == '+')
            modifiers[3] = '+';
        if (format[i[0]] == 32 && modifiers[3] != 1)
            modifiers[3] = ' ';
        if (format[i[0]] == '#')
            modifiers[2] = '1';
        if (format[i[0]] == '-')
            modifiers[0] = 'l';
    }
    return (handle_flags(format, i, args, modifiers));
}

int handle_flags(const char *format, int *i, va_list args, char *modifiers)
{
    int width = -1;
    flags *flag_arr = get_flag_arr();

    if (format[i[0]] > '0' && format[i[0]] <= '9')
        width = get_width(format, i);
    for (int a = 0; a < 11; a++) {
        if (flag_arr[a].flag == format[i[0]]) {
            flag_arr[a].function(args, width, modifiers);
            return (0);
        }
    }
    for (; format[i[0]] != '%'; i[0]--) {
    }
    my_putchar('%');
    return (0);
}