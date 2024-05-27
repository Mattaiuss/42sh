/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** valid_tree.c
*/

#include "../includes/tree.h"
#include "../includes/clib.h"

bool check_valid_operator(char *str)
{
    if (strcmp(str, ";") || strcmp(str, "|") ||
        strcmp(str, ">>") || strcmp(str, "<<") ||
        strcmp(str, ">") || strcmp(str, "<") ||
        strcmp(str, "&&") || strcmp(str, "||"))
        return true;
    return false;
}

bool valid_tree(tree_t *tree)
{
    if (tree->is_operator == true && check_valid_operator(tree->data)) {
        if (strcmp(tree->data, ";") != 0 &&
            ((tree->left == NULL || tree->right == NULL) ||
            (tree->left->data == NULL || tree->right->data == NULL) ||
            (tree->left->data[0] == '\0' || tree->right->data[0] == '\0')))
            return false;
        if (valid_tree(tree->left) == false)
            return false;
        if (valid_tree(tree->right) == false)
            return false;
    }
    return true;
}
