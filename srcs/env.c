/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** env.c
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"

char **table_to_array(table_t *env)
{
    char **array = malloc(sizeof(char *) * (env->size + 1));
    unsigned int i = 0;

    for (linked_list_t *fw = env->head; i < env->size; ++i) {
        array[i] = concat_env(fw->key, fw->value);
        fw = fw->next;
    }
    array[i] = NULL;
    return array;
}

int my_env(table_t *env)
{
    if (env == NULL)
        return 84;
    if (env->size == 0)
        return 0;
    table_dump(env);
    return 0;
}

int my_setenv(table_t *env, char **args, char **envp)
{
    char *new_env = NULL;
    char **new_envp = NULL;

    if (args == NULL || env == NULL)
        return 84;
    if (args[1] == NULL)
        return my_env(env);
    if (str_is_alphanum(args[1]) == 0){
        my_puterror("setenv: ");
        my_puterror("Variable name must contain alphanumeric characters.\n");
        return 1;
    }
    if (args[2] != NULL && args[3] != NULL)
        return my_puterror("setenv: Too many arguments.\n") + 1;
    new_env = concat_env(args[1], (args[2] != NULL ? args[2] : NULL));
    table_add_back(env, strdup(new_env));
    return 0;
}

int my_unsetenv(table_t *env, char **args)
{
    if (args[1] == NULL) {
        my_puterror("unsetenv: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i] != NULL; i++)
        table_delete_node(env, args[i]);
    return 0;
}
