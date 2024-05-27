/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** linked_lists.h, includes for linked lists and hash library
*/

#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef struct linked_list_s {
    unsigned int id;
    char *key;
    char *value;
    struct linked_list_s *next;
    struct linked_list_s *prev;
} linked_list_t;

typedef struct table_s {
    unsigned int (*func)(char const *);
    unsigned int size;
    linked_list_t *head;
    linked_list_t *tail;
} table_t;

int update(linked_list_t **head, linked_list_t **tail,
    unsigned int id, char const *value);
char *get_name(char *str);
char *get_value(char *str);
void free_values(char *initial, char *name, char *value);
unsigned int djb2_hash(const char *str);
table_t *create_table(unsigned int (*func)(char const *));
void delete_table(table_t *table);
int table_add_back(table_t *ht, char *value);
int table_add_front(table_t *ht, char *value);
int table_delete_node(table_t *ht, char *value);
int table_dump(table_t *ht);
char *table_search(table_t *ht, char *value);
