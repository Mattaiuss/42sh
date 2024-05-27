/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** my_str_is_alpha.c
*/

#include "clib.h"

int str_is_alpha(char const *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (IS_ALPHA(str[i]) == 0)
            return 0;
    return 1;
}
