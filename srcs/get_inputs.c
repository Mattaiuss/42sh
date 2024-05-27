/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** get_inputs.c
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"
#include "../includes/tree.h"
#include "../includes/history.h"

void print_subhome(table_t *env_listed)
{
    char *home = strdup(table_search(env_listed, "HOME"));
    char *pwd = strdup(table_search(env_listed, "PWD"));

    pwd = strnrep(pwd, home, "~", 1);
    my_putstr("\033[1;34m");
    my_putstr(pwd);
    free(home);
    free(pwd);
}

void write_prompt(table_t *env_listed)
{
    my_putstr("\033[1;32m");
    my_putstr(table_search(env_listed, "USER"));
    my_putstr("\033[1;37m:");
    print_subhome(env_listed);
    my_putstr("\033[1;37m$> \033[0;37m");
}

char *get_inputs(info_t *infos, tree_t *tree)
{
    char *buffer = NULL;
    size_t bytesread = 0;
    int read = 0;

    if (isatty(0))
        write_prompt(infos->env_listed);
    read = getline(&buffer, &bytesread, stdin);
    if (read == -1){
        free(buffer);
        free(infos);
        free(tree);
        exit(0);
    }
    *strchr(buffer, '\n') = '\0';
    if (strlen(buffer) == 0){
        free(buffer);
        return get_inputs(infos, tree);
    }
    add_to_history(infos->history, buffer);
    return buffer;
}
