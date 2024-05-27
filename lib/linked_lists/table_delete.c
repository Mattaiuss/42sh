/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** delete_functions.c, delete functions for linked lists
*/

#include "linked_lists.h"

void delete_element(linked_list_t **head, linked_list_t **tail,
    linked_list_t *copy)
{
    if (copy->prev != NULL) {
        copy->prev->next = copy->next;
    } else
        *head = copy->next;
    if (copy->next != NULL) {
        copy->next->prev = copy->prev;
    } else
        *tail = copy->prev;
    free(copy);
}

int del_list(linked_list_t **head, linked_list_t **tail, unsigned int id)
{
    linked_list_t *fw = *head;
    linked_list_t *bw = *tail;

    if (*head == NULL || *tail == NULL)
        return 84;
    do {
        if (fw->id == id) {
            delete_element(head, tail, fw);
            return 0;
        }
        if (bw->id == id) {
            delete_element(head, tail, bw);
            return 0;
        }
        fw = fw->next;
        bw = bw->prev;
    } while (fw != NULL && bw != NULL && fw->id != bw->id);
    return 84;
}

int table_delete_node(table_t *ht, char *value)
{
    unsigned int id;
    int return_value;

    if (ht == NULL || value == NULL)
        return 84;
    id = ht->func(value);
    return_value = del_list(&ht->head, &ht->tail, id);
    if (return_value == 0)
        --(ht->size);
    return return_value;
}
