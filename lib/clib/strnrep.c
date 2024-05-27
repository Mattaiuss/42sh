/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** my_strreeplace.c
*/

#include <string.h>
#include <stddef.h>

char *strnrep(char *str, const char *target, const char *replace, size_t n)
{
    size_t len = strlen(target);
    char *copy = strstr(str, target);

    if (len > 0){
        for (size_t i = 0; strstr(copy, target) != NULL && n < i; ++i) {
            copy = strstr(copy, target);
            memmove(copy, replace, strlen(replace));
        }
    }
    return str;
}
