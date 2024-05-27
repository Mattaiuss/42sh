/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** main
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"
#include "../includes/tree.h"
#include "../includes/history.h"

table_t *create_table_from_env(char **env)
{
    table_t *env_listed = create_table(&djb2_hash);

    for (int i = 0; env[i]; ++i)
        table_add_back(env_listed, strdup(env[i]));
    return env_listed;
}

void init_infos(info_t *infos, char **env)
{
    history_t *history = init_history();

    infos->env = env;
    infos->alias = NULL;
    infos->env_listed = create_table_from_env(env);
    infos->fd = malloc(sizeof(int) * 2);
    infos->return_value = 0;
    infos->history = history;
    infos->local_variables = NULL;
}

int main(int ac, char **av, char **env)
{
    char *input = NULL;
    info_t *infos = malloc(sizeof(info_t));
    tree_t *tree = NULL;

    init_infos(infos, env);
    for (; true; delete_tree(tree)) {
        tree = malloc(sizeof(tree_t));
        input = strndup(get_inputs(infos, tree), 512);
        create_tree(tree, input, NULL);
        free(input);
        if (valid_tree(tree) == false){
            my_puterror("Invalid null command.\n");
            continue;
        }
        infos->exec_alias = true;
        exec_tree(infos, tree);
        chdir(table_search(infos->env_listed, "PWD"));
    }
    return 0;
}
