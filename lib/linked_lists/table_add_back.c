/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** table_add_back.c, add a node at the end of the list
*/

#include "linked_lists.h"

int push_back(table_t *ht, unsigned int id, char *name, char *value)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (new_node == NULL)
        return 84;
    new_node->id = id;
    new_node->key = strdup(name);
    new_node->value = strdup(value);
    new_node->next = NULL;
    if (ht->head == NULL) {
        new_node->prev = NULL;
        ht->head = new_node;
        ht->tail = new_node;
    } else {
        new_node->prev = ht->tail;
        ht->tail->next = new_node;
        ht->tail = new_node;
    }
    return 0;
}

int table_add_back(table_t *ht, char *value)
{
    unsigned int id;
    int return_value;
    char *value_name = NULL;
    char *value_value = NULL;

    if (ht == NULL || value == NULL)
        return 84;
    value_name = get_name(value);
    value_value = get_value(value);
    id = ht->func(value_name);
    if (update(&ht->head, &ht->tail, id, value_value) == 0) {
        free_values(value, value_name, value_value);
        return 0;
    }
    return_value = push_back(ht, id, value_name, value_value);
    if (return_value == 0)
        ++(ht->size);
    free_values(value, value_name, value_value);
    return return_value;
}
