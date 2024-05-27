/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** alias_disp
*/

#include "../includes/shell.h"
#include "../includes/tree.h"

int is_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            return 0;
    }
    return 1;
}

void print_alias(alias_t **alias)
{
    alias_t *tmp = *alias;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, "ls") == 0) {
            tmp = tmp->next;
            continue;
        }
        my_putstr(tmp->alias);
        my_putstr("\t");
        if (is_space(tmp->command) == 0)
            my_putchar('(');
        my_putstr(tmp->command);
        if (is_space(tmp->command) == 0)
            my_putchar(')');
        my_putstr("\n");
        tmp = tmp->next;
    }
}
