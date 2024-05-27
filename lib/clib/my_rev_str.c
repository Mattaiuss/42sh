/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** reverse_string
*/

#include <stdlib.h>
#include <string.h>

char *my_revstr(char const *str)
{
    int i = 0;
    char *copy = strdup(str);
    int len = strlen(str) - 1;

    for (i = 0; i <= len / 2; ++i) {
        copy[i] = copy[len - i];
        copy[len - i] = str[i];
    }
    return copy;
}
