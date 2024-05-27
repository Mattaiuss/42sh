/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** print_pwd
*/

#include "../includes/shell.h"

int print_pwd(table_t *env_listed)
{
    my_putstr(table_search(env_listed, "PWD"));
    my_putstr("\n");
    return 0;
}
