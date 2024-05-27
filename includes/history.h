/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** history.h
*/

#pragma once

#define MAX_HISTORY_LEN 500

typedef struct execute_command_params_s {
    char **env;
    table_t *env_listed;
    char **arg;
    int status;
} execute_command_params_t;

typedef struct history_s {
    char **commands;
    int history_len;
    int max_history_len;
    int current_pos;
} history_t;

history_t *init_history(void);
void add_to_history(history_t *history, char *command);
int my_history(history_t *history, char **args);
void free_history(history_t *history);
int execute_history_command(history_t *history, char **command,
    char **env, table_t *env_listed);
