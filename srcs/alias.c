/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** alias
*/

#include "../includes/shell.h"
#include "../includes/tree.h"
#include "../includes/clib.h"
#include "../includes/linked_lists.h"

int already_exist(alias_t *alias, char *alias_name, char *command)
{
    alias_t *tmp = alias;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, alias_name) == 0) {
            tmp->command = strdup((command));
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void add_back_alias(alias_t **alias, char *alias_name, char *command,
    info_t *infos)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    alias_t *tmp = *alias;

    new_alias->alias = strdup((alias_name));
    new_alias->command = strdup((command));
    new_alias->next = NULL;
    if (*alias == NULL) {
        infos->alias = new_alias;
        return;
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new_alias;
}

void search_alias(alias_t *alias, char *alias_name)
{
    alias_t *tmp = alias;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, alias_name) == 0) {
            my_putstr(tmp->command);
            my_putstr("\n");
            return;
        }
        tmp = tmp->next;
    }
}

int my_alias(alias_t *alias, char **args, info_t *infos)
{
    char *tmp;

    if (args[1] == NULL) {
        print_alias(&alias);
        return 0;
    }
    if (args[2] == NULL) {
        search_alias(alias, args[1]);
        return 0;
    }
    for (int i = 3; args[i] != NULL; i ++) {
        args[2] = realloc(args[2], strlen(args[2]) + strlen(args[i]) + 2);
        args[2] = strcat(args[2], " ");
        args[2] = strcat(args[2], args[i]);
    }
    if (already_exist(alias, args[1], args[2]) == 1)
        return 0;
    add_back_alias(&alias, args[1], args[2], infos);
    return 0;
}
