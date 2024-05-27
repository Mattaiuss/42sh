/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** my_strsubstract.c
*/

#include <string.h>
#include <stddef.h>

char *strsub(char *str, const char *sub)
{
    size_t len = strlen(sub);
    char *copy = strstr(str, sub);

    if (len > 0){
        while ((strstr(copy, sub)) != NULL) {
            copy = strstr(copy, sub);
            memmove(copy, &copy[len], 1 + strlen(&copy[len]));
        }
    }
    return str;
}
