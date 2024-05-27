/*
** EPITECH PROJECT, 2024
** my_puterror
** File description:
** display sentence in error output
*/

#include "../../includes/clib.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int my_puterror(char const *str)
{
    if (str == NULL)
        return 84;
    write(2, str, strlen(str));
    return 0;
}
