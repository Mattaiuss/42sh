/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** my_str_is_lowercase.c
*/

#include "clib.h"

int str_is_lower(char const *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (IS_LOWER(str[i]) == 0)
            return 0;
    return 1;
}
