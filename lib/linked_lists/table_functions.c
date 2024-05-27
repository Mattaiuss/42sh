/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** hash_functions.c, functions for hash table
*/

#include "linked_lists.h"

void display_in_list(linked_list_t **head)
{
    for (linked_list_t *copy = *head; copy != NULL; copy = copy->next){
        write(STDOUT_FILENO, copy->key, strlen(copy->key));
        write(STDOUT_FILENO, "=", 1);
        write(STDOUT_FILENO, copy->value, strlen(copy->value));
        write(STDOUT_FILENO, "\n", 1);
    }
}

int table_dump(table_t *ht)
{
    display_in_list(&ht->head);
    return 0;
}

char *search_list(linked_list_t **head, linked_list_t **tail, unsigned int id)
{
    linked_list_t *fw = *head;
    linked_list_t *bw = *tail;

    if (*head == NULL || *tail == NULL)
        return NULL;
    do {
        if (fw->id == id)
            return fw->value;
        if (bw->id == id)
            return bw->value;
        fw = fw->next;
        bw = bw->prev;
    } while (fw != NULL && bw != NULL);
    return NULL;
}

char *table_search(table_t *ht, char *value)
{
    unsigned int id;

    if (ht == NULL || value == NULL)
        return NULL;
    id = ht->func(value);
    return search_list(&ht->head, &ht->tail, id);
}
