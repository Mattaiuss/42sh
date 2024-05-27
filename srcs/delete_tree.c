/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** create_tree.c
*/

#include "../includes/shell.h"
#include "../includes/tree.h"
#include "../includes/clib.h"
#include "../includes/linked_lists.h"

void delete_info(info_t *infos)
{
    if (infos->fd)
        free(infos->fd);
    if (infos->env)
        free_2d_array(infos->env);
    if (infos->env_listed)
        delete_table(infos->env_listed);
    free(infos);
}

void delete_tree(tree_t *tree)
{
    if (tree->left)
        delete_tree(tree->left);
    if (tree->right)
        delete_tree(tree->right);
    free(tree->data);
    free(tree);
}
