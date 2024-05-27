/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_change_directory.c, cd command
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"

static int back_to_previous_directory(table_t *env_listed)
{
    char *old_PWD = strdup(table_search(env_listed, "OLDPWD"));

    if (old_PWD == NULL) {
        my_putstr("cd: OLDPWD not defined.\n");
        free(old_PWD);
        return 1;
    }
    table_add_back(env_listed, concat_env("OLDPWD",
        table_search(env_listed, "PWD")));
    table_add_back(env_listed, concat_env("PWD", old_PWD));
    chdir(table_search(env_listed, "PWD"));
    free(old_PWD);
    return 1;
}

static int go_to_current(table_t *env_listed, char *current_PWD)
{
    table_add_back(env_listed, concat_env("OLDPWD", current_PWD));
    table_add_back(env_listed, concat_env("PWD", current_PWD));
    chdir(table_search(env_listed, "PWD"));
    return 1;
}

static int go_to_home(table_t *env_listed)
{
    char *current = getcwd(NULL, 0);

    table_add_back(env_listed, concat_env("OLDPWD", current));
    table_add_back(env_listed, concat_env("PWD",
        table_search(env_listed, "HOME")));
    chdir(table_search(env_listed, "PWD"));
    free(current);
    return 1;
}

static int check_cd_flags(int path, table_t *env_listed, char *current_PWD)
{
    switch (path) {
        case CURR:
        case CURR_W_SLASH:
            return go_to_current(env_listed, current_PWD);
        case HOME_W_TILDE:
        case HOME_W_SLASH:
        case HOME_W_DASHES:
            return go_to_home(env_listed);
        case DASH:
            return back_to_previous_directory(env_listed);
        default:
            return 0;
    }
}

int verify_existing_path(char *path)
{
    struct stat stats;

    if (stat(path, &stats) == -1){
        my_puterror(path);
        my_puterror(": No such file or directory.\n");
        return 1;
    }
    if (access(path, R_OK) == -1){
        my_puterror(path);
        my_puterror(": Permission denied.\n");
        return 1;
    }
    if ((!S_ISDIR(stats.st_mode) && !S_ISLNK(stats.st_mode)) ||
        (access(path, X_OK) == -1)){
        my_puterror(path);
        my_puterror(": Not a directory.\n");
        return 1;
    }
    return 0;
}

int change_to_a_directory(char *path, table_t *env_listed)
{
    char *current_PWD = strdup(table_search(env_listed, "PWD"));

    if (check_cd_flags(djb2_hash(path), env_listed, current_PWD)){
        free(current_PWD);
        return 0;
    }
    table_add_back(env_listed, concat_env("OLDPWD", current_PWD));
    if (verify_existing_path(path)){
        free(current_PWD);
        return 1;
    }
    chdir(path);
    free(current_PWD);
    return 0;
}

int execute_change(char **args, table_t *env_listed)
{
    if (env_listed == NULL){
        my_puterror("TERM environment variable not set.\n");
        return 84;
    }
    if (args[1] == NULL) {
        table_add_back(env_listed, concat_env("OLDPWD",
            table_search(env_listed, "PWD")));
        chdir(table_search(env_listed, "HOME"));
        return 0;
    }
    if (args[2] != NULL) {
        my_puterror("cd: Too many arguments.\n");
        return 1;
    }
    if (args[1][0] == '~')
        args[1] = strnrep(args[1], "~", table_search(env_listed, "HOME"), 1);
    return change_to_a_directory(args[1], env_listed);
}

int my_cd(char **args, table_t *env_listed)
{
    int return_value = execute_change(args, env_listed);
    char *current_location = getcwd(NULL, 0);
    char *current_PWD = concat_env("PWD", current_location);

    if (env_listed == NULL){
        my_puterror("TERM environment variable not set.\n");
        free(current_PWD);
        return 84;
    }
    table_add_back(env_listed, current_PWD);
    free(current_location);
    return return_value;
}
