/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** headerfile
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct flag
{
    void     (*function) (va_list, int, char *);
    char    flag;
} flags;
flags* get_flag_arr();
flags* get_flag_arr2(flags *);
int handle_modifiers(const char *, int *, va_list);
int disp_stdarg(char *, ...);
int sum_stdarg(int, int, ...);
int sum_intarg(int, va_list);
int sum_chararg(int, va_list);
void my_putchar(char);
int my_getnbr(char const *);
int my_put_nbr(int);
int my_put_nbr_base(unsigned int, char *);
int my_putstr(char const *);
void disp_adrarg(va_list, int, char *);
void disp_adrpadd(int, int, char *);
void disp_spstrarg(va_list, int, char *);
void disp_spstrchar(char);
int get_diff_spstr(char *, int);
void disp_strarg(va_list, int, char *);
void disp_chararg(va_list, int, char *);
void disp_intarg(va_list, int, char *);
void disp_intpadd(int, int, char *);
void disp_usintarg(va_list, int, char *);
void disp_usintpadd(va_list, int, char *);
void disp_octarg(va_list, int, char *);
void disp_octpadd(unsigned int, int, char *);
void disp_hexarg(va_list, int, char *);
void disp_hexpadd(unsigned int, int, char *);
void disp_up_hexarg(va_list, int, char *);
void disp_up_hexpadd(unsigned int, int, char *);
void disp_binarg(va_list, int, char *);
void disp_binpadd(unsigned int, int, char *);
int get_width(const char *, int *);
int handle_flags(const char *, int *, va_list, char *);
int my_printf(const char *, ...);
int my_strlen(char *);
int getnbr_result(char const *, int, int, int);
int my_strcmp(char const *, char const *);