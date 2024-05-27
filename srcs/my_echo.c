/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_echo.c
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

int my_echo(char **args, table_t *env_listed, char **env, int r_value)
{
    if (!args[1])
        return my_putstr("\n");
    if (args[1][0] == '$' && (args[1][1] == '?')) {
        my_putnbr(r_value);
        return my_putstr("\n");
    }
    if (args[1][0] == '$' && args[1][1] != '\0') {
        if (table_search(env_listed, args[1] + 1) == NULL){
            my_puterror(args[1] + 1);
            my_puterror(": Undefined variable.\n");
            return 1;
        }
        my_putstr(table_search(env_listed, args[1] + 1));
        return my_putchar('\n');
    }
    execute_program(env, env_listed, args);
    return 0;
}
