/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** execute_tree.c
*/

#include "../includes/shell.h"
#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/tree.h"

bool check_redirections(info_t *infos, tree_t *tree)
{
    if (strcmp(tree->data, ">>") == 0) {
        process_add_output_redirection(infos, tree);
        return true;
    }
    if (strcmp(tree->data, "<<") == 0) {
        process_add_input_redirection(infos, tree);
        return true;
    }
    if (strcmp(tree->data, ">") == 0) {
        process_output_redirection(infos, tree);
        return true;
    }
    if (strcmp(tree->data, "<") == 0) {
        process_input_redirection(infos, tree);
        return true;
    }
    return false;
}

bool check_pipe_semicolon(info_t *infos, tree_t *tree)
{
    if (strcmp(tree->data, "|") == 0) {
        process_pipe(infos, tree);
        return true;
    }
    if (strcmp(tree->data, ";") == 0) {
        exec_tree(infos, tree->left);
        exec_tree(infos, tree->right);
        return true;
    }
    return false;
}

bool check_and_or_operators(info_t *infos, tree_t *tree)
{
    if (strcmp(tree->data, "&&") == 0) {
        exec_tree(infos, tree->left);
        if (infos->return_value == 0)
            exec_tree(infos, tree->right);
        return true;
    }
    if (strcmp(tree->data, "||") == 0) {
        exec_tree(infos, tree->left);
        if (infos->return_value != 0)
            exec_tree(infos, tree->right);
        return true;
    }
    return false;
}

bool check_separators(info_t *infos, tree_t *tree)
{
    if (check_and_or_operators(infos, tree))
        return true;
    if (check_pipe_semicolon(infos, tree))
        return true;
    return check_redirections(infos, tree);
}

void exec_tree(info_t *infos, tree_t *tree)
{
    char **command = NULL;

    if (check_separators(infos, tree))
        return;
    command = split_string_tok(tree->data, " \t\n");
    for (int i = 0; command[i]; i++)
        replace_local_variable_in_str(infos, command[i]);
    infos->return_value = sys_or_builtin(infos,
        infos->env, command, infos->return_value);
    free_2d_array(command);
    infos->exec_alias = true;
}
