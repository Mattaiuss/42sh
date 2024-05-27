/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** table_add_functions.c, includes for default c library
*/

#include "linked_lists.h"

int update(linked_list_t **head, linked_list_t **tail,
    unsigned int id, char const *value)
{
    linked_list_t *fw = *head;
    linked_list_t *bw = *tail;

    if (*head == NULL || *tail == NULL)
        return 84;
    do {
        if (fw->id == id) {
            free(fw->value);
            fw->value = strdup(value);
            return 0;
        }
        if (bw->id == id) {
            free(bw->value);
            bw->value = strdup(value);
            return 0;
        }
        fw = fw->next;
        bw = bw->prev;
    } while (fw != NULL && bw != NULL);
    return 84;
}

char *get_name(char *str)
{
    char *name = malloc(sizeof(char) * (strlen(str) + 1));
    int i = 0;

    for (; str[i] != '='; ++i)
        name[i] = str[i];
    name[i] = '\0';
    return name;
}

char *get_value(char *str)
{
    char *value = malloc(sizeof(char) * (strlen(str) + 1));
    int i = 0;
    int j = 0;

    for (; str[i] != '='; ++i);
    ++i;
    for (; str[i]; i++) {
        value[j] = str[i];
        ++j;
    }
    value[j] = '\0';
    return value;
}

void free_values(char *initial, char *name, char *value)
{
    free(initial);
    free(name);
    free(value);
}
