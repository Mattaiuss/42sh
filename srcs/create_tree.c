/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** create_tree.c
*/

#include "../includes/tree.h"
#include "../includes/clib.h"

static bool is_or_operator(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '|' && data[i + 1] == '|') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup("||");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 2);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

static bool is_and_operator(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '&' && data[i + 1] == '&') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup("&&");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 2);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

bool is_semi_column(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == ';') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup(";");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 1);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

bool is_pipe(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '|') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup("|");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 1);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

bool is_redirection_file(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '>') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup(">");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 1);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

bool is_redirection_stdin(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;
    size_t k = 1;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '<') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup("<");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 1);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

static bool is_double_redirection_file(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '>' && data[i + 1] == '>') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup(">>");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 2);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

static bool is_double_redirection_stdin(tree_t *tree, char *data)
{
    char *left = NULL;
    char *right = NULL;
    size_t k = 2;

    for (size_t i = 0; data[i] != '\0'; ++i) {
        if (data[i] == '<' && data[i + 1] == '<') {
            tree->left = malloc(sizeof(tree_t));
            tree->right = malloc(sizeof(tree_t));
            tree->parent = NULL;
            tree->data = strdup("<<");
            tree->is_operator = true;
            left = strndup(data, i);
            right = strdup(data + i + 2);
            create_tree(tree->left, left, tree);
            create_tree(tree->right, right, tree);
            return (true);
        }
    }
    return (false);
}

void create_tree(tree_t *node, char *data, tree_t *tree)
{
    if (is_or_operator(node, data))
        return;
    if (is_and_operator(node, data))
        return;
    if (is_pipe(node, data))
        return;
    if (is_semi_column(node, data))
        return;
    if (is_double_redirection_file(node, data))
        return;
    if (is_double_redirection_stdin(node, data))
        return;
    if (is_redirection_file(node, data) || is_redirection_stdin(node, data))
        return;
    node->data = strdup(data);
    node->is_operator = (false);
    node->left = NULL;
    node->right = NULL;
    node->parent = tree;
}
