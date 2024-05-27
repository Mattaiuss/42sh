/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** tree.h, all the command needed for the trees
*/

#pragma once

#include "linked_lists.h"
#include "history.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct tree_s {
    char *data;
    bool is_operator;
    struct tree_s *parent;
    struct tree_s *left;
    struct tree_s *right;
} tree_t;

typedef struct local_variable_s {
    char *name;
    char *value;
    struct local_variable_s *next;
} local_t;

typedef struct info_s {
    int *fd;
    char **env;
    table_t *env_listed;
    alias_t *alias;
    history_t *history;
    local_t *local_variables;
    int return_value;

    bool exec_alias;
} info_t;

typedef struct redirect_s {
    int flags;
    int mode;
    int int_or_out;
} redirect_t;

char *get_inputs(info_t *infos, tree_t *tree);
void create_tree(tree_t *node, char *data, tree_t *tree);
void delete_tree(tree_t *tree);
bool valid_tree(tree_t *tree);
void exec_tree(info_t *infos, tree_t *tree);
void delete_info(info_t *infos);
void process_pipe(info_t *infos, tree_t *tree);
void process_output_redirection(info_t *infos, tree_t *tree);
void process_input_redirection(info_t *infos, tree_t *tree);
void process_add_output_redirection(info_t *infos, tree_t *tree);
void process_add_input_redirection(info_t *infos, tree_t *tree);
void add_back_alias(alias_t **alias, char *alias_name, char *command,
    info_t *infos);

void find_and_replace_local_variables(info_t *infos, tree_t *tree);
int add_local_variable(info_t *infos, char *name, char *value);
int delete_local_variable(info_t *infos, char *name);
char *get_local_variable(info_t *infos, char *name);
int local_env_switch(info_t *infos, char *str, int id);
void replace_local_variable_in_str(info_t *infos, char *str);
