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

struct word_counter {
    int number_words;
    int is_word;
    int is_escape;
};

void nb_words2(char *string, char *delimiters,
    struct word_counter *counter, int i)
{
    if (counter->is_escape) {
        counter->is_escape = 0;
        return;
    }
    if (string[i] == '\\'){
        counter->is_escape = 1;
        return;
    }
    if (strchr(delimiters, string[i]) == NULL && !(counter->is_word)){
        ++(counter->number_words);
        counter->is_word = 1;
        return;
    }
    if (strchr(delimiters, string[i]) != NULL && counter->is_word)
        counter->is_word = 0;
}

int nb_words(char *string, char *delimiters)
{
    struct word_counter *counter = malloc(sizeof(struct word_counter));
    int number_words = 0;

    counter->number_words = 0;
    counter->is_word = 0;
    counter->is_escape = 0;
    if (string == NULL)
        return 0;
    for (int i = 0; string[i]; ++i)
        nb_words2(string, delimiters, counter, i);
    number_words = counter->number_words;
    free(counter);
    return number_words;
}

static void move_table_left(char *table, int i)
{
    int j = 0;

    if (table[i] != '\\')
        return;
    for (j = i; table[j]; ++j)
        table[j] = table[j + 1];
    table[j] = '\0';
}

static char **end_split_string_tok(char **args, int arg_index)
{
    for (int i = 0; args[i]; ++i)
        for (int j = 0; args[i][j]; ++j)
            move_table_left(args[i], j);
    args[arg_index] = NULL;
    return args;
}

static void process_token(char **args, int *arg_index,
    char *arg, int token_length)
{
    if (token_length < 0)
        return;
    args[*arg_index] = strndup(arg, token_length);
    ++(*arg_index);
}

char **split_string_tok_with_anti(char *arg, char *delimiters)
{
    int nb_args = nb_words(arg, delimiters);
    char **args = calloc(nb_args + 1, sizeof(char *));
    int arg_index = 0;
    int start_i = 0;
    int end_i = 0;
    int is_escape = 0;

    for (; arg[end_i] != '\0' && args != NULL; ++end_i){
        if (arg[end_i] == '\\' && !is_escape) {
            is_escape = 1;
            continue;
        }
        if (strchr(delimiters, arg[end_i]) != NULL && !is_escape){
            process_token(args, &arg_index, arg + start_i,
                end_i - start_i);
            start_i = end_i + 1;
        }
    }
    process_token(args, &arg_index, arg + start_i, end_i - start_i);
    return end_split_string_tok(args, arg_index);
}
