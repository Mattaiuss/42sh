/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** clib.h, includes for default c library
*/

#pragma once
#include <float.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define IS_LOWER(c) (c >= 'a' && c <= 'z')
#define IS_UPPER(c) (c >= 'A' && c <= 'Z')
#define IS_ALPHA(c) (IS_LOWER(c) || IS_UPPER(c))
#define IS_NUM(c) (c >= '0' && c <= '9')
#define IS_ALPHANUM(c) (IS_ALPHA(c) || IS_NUM(c))
#define IS_PRINTABLE(c) (c >= ' ' && c <= '~')

int str_is_alpha(char const *str);
int str_is_num(char const *str);
int str_is_alphanum(char const *str);
int str_is_lower(char const *str);
int str_is_upper(char const *str);
int str_is_printable(char const *str);
int my_nbrlen(int nb);
int my_putchar(char const c);
int my_puterror(char const *str);
int my_putnbr(int nb);
int my_putstr(char const *str);
char *my_revstr(char const *str);
char *strsub(char *str, const char *sub);
char *strnsub(char *str, const char *sub, size_t n);
char *strrep(char *str, const char *target, const char *replace);
char *strnrep(char *str, const char *target, const char *replace, size_t n);
char **split_string_tok(char *arg, char *delimiters);
char **split_string_tok_with_anti(char *arg, char *delimiters);
