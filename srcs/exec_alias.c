/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-thibault.lafont
** File description:
** exec_alias
*/

#include "../includes/shell.h"
#include "../includes/tree.h"

int is_alias(alias_t *alias, char **args, info_t *infos)
{
    alias_t *tmp = alias;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, args[0]) == 0) {
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

void cat_command(char **command, char **args)
{
    int len = strlen(*command);

    for (int i = 1; args[i]; i++) {
        len += 1;
        len += strlen(args[i]) + 1;
    }
    *command = realloc(*command, len + 1);
    for (int i = 1; args[i]; i++) {
        *command = strcat(*command, " ");
        *command = strcat(*command, args[i]);
    }
}

int is_string_alias(alias_t *alias, char *args)
{
    alias_t *tmp = alias;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, args) == 0 && strncmp(
            tmp->alias, tmp->command, strlen(tmp->alias)) == 0)
            return 0;
        tmp = tmp->next;
    }
    return 1;
}

static int get_nb_words(char *command)
{
    int nb_words = 0;
    int len = 0;

    if (command == NULL)
        return 0;
    len = strlen(command);
    for (int i = 0; i < len; i++) {
        if (command[i] == ' ')
            nb_words++;
    }
    return nb_words + 1;
}

static char **split_command(char *command)
{
    char **new_args = malloc(sizeof(char *) * ((get_nb_words(command)) + 1));
    int i = 0;

    if (new_args == NULL)
        return NULL;
    new_args[i] = strtok(command, " ");
    while (new_args[i] != NULL) {
        i++;
        new_args[i] = strtok(NULL, " ");
    }
    return new_args;
}

bool detect_loop(alias_t *alias, char *alias_name, int depth)
{
    alias_t *tmp = alias;

    if (depth >= 1000)
        return true;
    while (tmp != NULL) {
        if (strcmp(tmp->alias, alias_name) == 0 &&
            strcmp(tmp->command, alias_name) == 0)
            return true;
        if (strcmp(tmp->alias, alias_name) == 0 &&
            detect_loop(alias, tmp->command, depth + 1))
            return true;
        tmp = tmp->next;
    }
    return false;
}

int exec_alias(alias_t *alias, char **args, info_t *infos)
{
    alias_t *tmp = alias;
    char **new_args = NULL;
    char *command = NULL;

    if (detect_loop(alias, args[0], 0) == true) {
        my_puterror("Alias loop.\n");
        return 1;
    }
    if (is_string_alias(infos->alias, args[0]) == 0)
        infos->exec_alias = false;
    while (tmp != NULL) {
        if (strcmp(tmp->alias, args[0]) == 0) {
            command = strdup(tmp->command);
            cat_command(&command, args);
            new_args = split_command(command);
            return sys_or_builtin(infos, infos->env, new_args, 0);
        }
        tmp = tmp->next;
    }
    return 1;
}
