/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** env.c
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"

char *concat_env(char *key, char *value)
{
    unsigned int len1 = 0;
    unsigned int len2 = 0;
    char *new_env = NULL;

    if (key != NULL)
        len1 = strlen(key);
    if (value != NULL)
        len2 = strlen(value);
    new_env = malloc(sizeof(char) * (len1 + len2 + 2));
    if (new_env == NULL)
        return NULL;
    for (unsigned int i = 0; i < len1; ++i)
        new_env[i] = key[i];
    new_env[len1] = '=';
    for (unsigned int i = 0; i < len2; ++i)
        new_env[len1 + 1 + i] = value[i];
    new_env[len1 + 1 + len2] = '\0';
    return new_env;
}
