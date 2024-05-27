/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** my_strreeplace.c
*/

#include <string.h>
#include <stddef.h>

char *strrep(char *str, const char *target, const char *replace)
{
    size_t len = strlen(target);
    char *copy = strstr(str, target);

    if (len > 0){
        while ((strstr(copy, target)) != NULL) {
            copy = strstr(copy, target);
            memmove(copy, replace, strlen(replace));
        }
    }
    return str;
}
