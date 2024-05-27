/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** alias_unset
*/

#include "../includes/shell.h"
#include "../includes/tree.h"

void del_alias(alias_t **alias, alias_t *prev, alias_t *tmp)
{
    if (prev == NULL) {
        *alias = tmp->next;
        free(tmp->alias);
        free(tmp->command);
        free(tmp);
        return;
    }
    prev->next = tmp->next;
    free(tmp->alias);
    free(tmp->command);
    free(tmp);
}

void delete_by_alias(info_t *infos, char *alias_name)
{
    alias_t *tmp = infos->alias;
    alias_t *prev = NULL;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, alias_name) == 0) {
            return del_alias(&infos->alias, prev, tmp);
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int my_unalias(alias_t *alias, char **args, info_t *infos)
{
    for (int i = 1; args[i] != NULL; i ++) {
        delete_by_alias(infos, args[i]);
    }
}
