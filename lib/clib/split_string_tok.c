/*
** EPITECH PROJECT, 2024
** Temporary-My_Rpg
** File description:
** str_to_word_array.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "clib.h"

int nb_words_first(char *string, char *delimiters)
{
    int number_words = 0;
    int is_word = 0;

    if (string == NULL)
        return 0;
    for (int i = 0; string[i]; ++i) {
        if (strchr(delimiters, string[i]) == NULL && !is_word) {
            ++number_words;
            is_word = 1;
            continue;
        }
        is_word = (strchr(delimiters, string[i]) != NULL) ? 0 : is_word;
    }
    return number_words;
}

char **split_string_tok_no_anti(char *arg, char *delimiters)
{
    int nb_args = nb_words_first(arg, delimiters);
    char **args = malloc(sizeof(char *) * (nb_args + 1));
    char *ptr = strtok(arg, delimiters);

    if (args == NULL)
        return NULL;
    if (ptr == NULL) {
        args[0] = strdup("");
        args[1] = NULL;
        return args;
    }
    for (int i = 0; ptr != NULL; ptr = strtok(NULL, delimiters)) {
        args[i] = strdup(ptr);
        ++i;
    }
    args[nb_args] = NULL;
    free(ptr);
    return args;
}

bool contains_antislash(char *arg)
{
    for (int i = 0; arg[i]; ++i)
        if (arg[i] == '\\')
            return true;
    return false;
}

char **split_string_tok(char *arg, char *delimiters)
{
    if (contains_antislash(arg))
        return split_string_tok_with_anti(arg, delimiters);
    else
        return split_string_tok_no_anti(arg, delimiters);
}
