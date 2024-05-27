/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** linked_lists.h, includes for linked lists and hash library
*/

#pragma once

typedef struct alias_s {
    char *alias;
    char *command;
    struct alias_s *next;
} alias_t;

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

unsigned int djb2_hash(const char *str);
table_t *create_table(unsigned int (*func)(char const *));
void delete_table(table_t *table);
int table_add_back(table_t *ht, char *value);
int table_add_front(table_t *ht, char *value);
int table_delete_node(table_t *ht, char *value);
int table_dump(table_t *ht);
char *table_search(table_t *ht, char *value);

typedef struct info_s info_t;

int my_alias(alias_t *alias, char **args, info_t *infos);
int my_unalias(alias_t *alias, char **args, info_t *infos);
int exec_alias(alias_t *alias, char **args, info_t *infos);
int is_alias(alias_t *alias, char **args, info_t *infos);
void print_alias(alias_t **alias);
void add_back_alias(alias_t **alias, char *alias_name, char *command,
    info_t *infos);
