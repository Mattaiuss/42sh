/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** history.c
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"
#include "../includes/tree.h"
#include "../includes/history.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

history_t *init_history(void)
{
    history_t *history = malloc(sizeof(history_t));

    history->commands = malloc(sizeof(char *) * MAX_HISTORY_LEN);
    history->history_len = 0;
    history->max_history_len = MAX_HISTORY_LEN;
    history->current_pos = 0;
    return history;
}

void add_to_history(history_t *history, char *command)
{
    if (history->history_len == history->max_history_len) {
        free(history->commands[0]);
        for (int i = 0; i < history->history_len - 1; i++) {
            history->commands[i] = history->commands[i + 1];
        }
        history->commands[history->history_len - 1] = strdup(command);
    } else {
        history->commands[history->history_len] = strdup(command);
        history->history_len++;
    }
}

static int print_history(history_t *history)
{
    for (int i = 0; i < history->history_len; i++) {
        my_putnbr(i);
        my_putstr(": ");
        my_putstr(history->commands[i]);
        my_putstr("\n");
    }
    return 0;
}

static void print_len_history(history_t *history, int len)
{
    if (len > history->history_len) {
        len = history->history_len;
    }
    for (int i = history->history_len - len; i < history->history_len; i++) {
        my_putnbr(i);
        my_putstr(": ");
        my_putstr(history->commands[i]);
        my_putstr("\n");
    }
}

int my_history(history_t *history, char **args)
{
    if (args[0] != NULL && args[1] == NULL) {
        print_history(history);
        return 0;
    }
    if (args[1] != NULL && args[2] == NULL) {
        print_len_history(history, atoi(args[1]));
        return 0;
    }
    return 0;
}

void free_history(history_t *history)
{
    for (int i = 0; i < history->history_len; i++) {
        free(history->commands[i]);
    }
    free(history->commands);
    free(history);
}

static void execute_command_with_fork(execute_command_params_t *params)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        execute_command(params->env, params->env_listed,
        params->arg, params->status);
        exit(0);
    }
    if (pid < 0) {
        perror("fork failed");
    } else {
        waitpid(pid, &status, 0);
    }
}

static int handle_number_command(history_t *history, char *history_command,
    char **env, table_t *env_listed)
{
    char **arg = NULL;
    char *end;
    long int command_index = strtol(history_command, &end, 10);
    execute_command_params_t params;

    if (end != history_command && command_index < history->history_len) {
        arg = split_string_tok(history->commands[command_index], " \t");
        params = (execute_command_params_t){env, env_listed, arg, 0};
        execute_command_with_fork(&params);
        return 0;
    }
    return -1;
}

static int handle_string_command(history_t *history, char *history_command,
    char **env, table_t *env_listed)
{
    char **arg = NULL;
    execute_command_params_t params;

    for (int i = history->history_len - 1; i >= 0; i--) {
        if (strncmp(history->commands[i], history_command,
        strlen(history_command)) == 0) {
            arg = split_string_tok(history->commands[i], " \t");
            params = (execute_command_params_t){env, env_listed, arg, 0};
            execute_command_with_fork(&params);
            return 0;
        }
    }
    printf("No such command in history.\n");
    return 0;
}

int execute_history_command(history_t *history, char **command,
    char **env, table_t *env_listed)
{
    char *history_command = command[0] + 1;

    if (handle_number_command(history, history_command, env, env_listed) == 0){
        return 0;
    }
    return handle_string_command(history, history_command, env, env_listed);
}
