/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** sys_or_builtin
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>
#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"

int third_switch(info_t *infos, char **env, char **args, int id)
{
    int return_value = 0;
    table_t *l_env = infos->env_listed;

    switch (id) {
        case ALIAS:
            return my_alias(infos->alias, args, infos);
        case UNALIAS:
            return my_unalias(infos->alias, args, infos);
        case SET:
            return local_env_switch(infos, args[1], SET);
        case UNSET:
            return local_env_switch(infos, args[1], UNSET);
        default:
            return_value = execute_program(env, l_env, args);
            return return_value;
    }
}

int second_switch(info_t *infos, char **env, char **args, int id)
{
    table_t *l_env = infos->env_listed;

    switch (id) {
        case CD:
            return my_cd(args, l_env);
        case PWD:
            return print_pwd(l_env);
        case ENV:
            return my_env(l_env);
        case SETENV:
            return my_setenv(l_env, args, env);
        case UNSETENV:
            return my_unsetenv(l_env, args);
        case HISTORY:
            return my_history(infos->history, args);
        default:
            return third_switch(infos, env, args, id);
    }
}

void free_2d_array(char **array)
{
    for (unsigned int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

int free_and_exit(table_t *l_env, char **args, int r_value, info_t *infos)
{
    free_history(infos->history);
    delete_table(l_env);
    free_2d_array(args);
    free(infos->fd);
    for (alias_t *tmp = infos->alias; tmp != NULL; tmp = tmp->next) {
        free(tmp->alias);
        free(tmp->command);
    }
    free(infos);
    exit(0);
}

int sys_or_builtin(info_t *infos, char **env, char **args, int r_value)
{
    unsigned int id = djb2_hash(args[0]);
    table_t *l_env = infos->env_listed;

    if (args[0][0] == '\0')
        return r_value;
    if (is_alias(infos->alias, args, infos) == 0 && infos->exec_alias == true)
        return exec_alias(infos->alias, args, infos);
    if (strncmp((const char *)(args[0]), "!", 1) == 0 && args[1] == NULL){
        execute_history_command(infos->history, args, env, l_env);
        return 0;
    }
    switch (id) {
        case EXIT:
            return free_and_exit(l_env, args, r_value, infos);
        case ECHO:
            return my_echo(args, l_env, env, r_value);
        default:
            return second_switch(infos, env, args, id);
    }
    return r_value;
}
