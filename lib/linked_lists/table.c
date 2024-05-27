/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Secured
** File description:
** hashtable.h
*/

#include "linked_lists.h"

table_t *create_table(unsigned int (*func)(char const *))
{
    table_t *table = malloc(sizeof(table_t));

    table->func = func;
    table->head = NULL;
    table->tail = NULL;
    return table;
}

void delete_node(linked_list_t *node)
{
    if (node == NULL)
        return;
    if (node->key != NULL)
        free(node->key);
    if (node->value != NULL)
        free(node->value);
    free(node);
}

void delete_table(table_t *table)
{
    linked_list_t *current;
    linked_list_t *next;

    if (table == NULL)
        return;
    current = table->head;
    while (current != NULL) {
        next = current->next;
        delete_node(current);
        current = next;
    }
    free(table);
}
