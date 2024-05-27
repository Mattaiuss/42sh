/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** table_add_front.c, add a node at the beginning of the list
*/

#include "linked_lists.h"

int push_front(table_t *ht, unsigned int id, char const *name,
    char const *value)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (new_node == NULL)
        return (84);
    new_node->id = id;
    new_node->key = strdup(name);
    new_node->value = strdup(value);
    new_node->prev = NULL;
    new_node->next = ht->head;
    if (ht->head != NULL)
        ht->head->prev = new_node;
    else
        ht->tail = new_node;
    ht->head = new_node;
    return 0;
}

int table_add_front(table_t *ht, char *value)
{
    unsigned int id = 0;
    int return_value = 0;
    char *value_name = NULL;
    char *value_value = NULL;

    if (ht == NULL || value == NULL)
        return 84;
    value_name = get_name(value);
    value_value = get_value(value);
    id = ht->func(value_name);
    if (update(&ht->head, &ht->tail, id, value_value) == 0){
        free_values(value, value_name, value_value);
        return 0;
    }
    return_value = push_front(ht, id, value_name, value_value);
    if (return_value == 0)
        ++(ht->size);
    free_values(value, value_name, value_value);
    return return_value;
}
