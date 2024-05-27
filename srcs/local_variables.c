/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** local variables
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"
#include "../includes/tree.h"
#include "../includes/history.h"

static int count_before_equal(char *str)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != '=')
        i++;
    return i;
}

static int count_after_equal(char *str)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != '=')
        i++;
    return i;
}

int local_env_switch(info_t *infos, char *str, int id)
{
    char *name = NULL;
    char *value = NULL;
    int name_size = count_before_equal(str);
    int value_size = count_after_equal(str);

    if (name_size == 0 || value_size == 0)
        return 1;
    name = strndup(str, name_size);
    value = strdup(str + name_size + 1);
    if (id == SET)
        add_local_variable(infos, name, value);
    else if (id == UNSET)
        delete_local_variable(infos, name);
}

int add_local_variable(info_t *infos, char *name, char *value)
{
    local_t *new = malloc(sizeof(local_t));
    local_t *tmp = infos->local_variables;

    new->name = strdup(name);
    new->value = strdup(value);
    new->next = NULL;
    if (infos->local_variables == NULL) {
        infos->local_variables = new;
        return 0;
    }
    while (tmp->next != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    if (strcmp(tmp->name, name) == 0) {
        tmp->value = strdup(value);
        return 0;
    }
    tmp->next = new;
    return 0;
}

static int free_deleted(local_t *tmp)
{
    free(tmp->name);
    free(tmp->value);
    free(tmp);
    return 0;
}

int delete_local_variable(info_t *infos, char *name)
{
    local_t *tmp = infos->local_variables;
    local_t *prev = NULL;

    if (tmp != NULL && strcmp(tmp->name, name) == 0) {
        infos->local_variables = tmp->next;
        return free_deleted(tmp);
    }
    while (tmp != NULL && strcmp(tmp->name, name) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return 0;
    prev->next = tmp->next;
    return free_deleted(tmp);
}

char *get_local_variable(info_t *infos, char *name)
{
    local_t *tmp = infos->local_variables;

    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return NULL;
}

void replace_local_variable_in_str(info_t *infos, char *str)
{
    char *value;

    if (str == NULL)
        return;
    if (str[0] == '$') {
        value = get_local_variable(infos, str + 1);
        if (value != NULL) {
            free(str);
            str = strdup(value);
        }
    }
}
