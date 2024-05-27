/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** my_strnsubstract.c
*/

#include <string.h>
#include <stddef.h>

char *strnsub(char *str, const char *sub, size_t n)
{
    size_t len = strlen(sub);
    char *copy = str;

    if (len > 0){
        for (size_t i = 0; strstr(copy, sub) != NULL && i < n; ++i){
            copy = strstr(copy, sub);
            memmove(copy, &copy[len], 1 + strlen(&copy[len]));
        }
    }
    return str;
}
