/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** execute_prog
*/

#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/shell.h"

static int is_error(char *path, int status)
{
    my_puterror(path);
    my_puterror(": ");
    if (status == -1 && errno == ENOEXEC)
        return my_puterror("Exec format error. Wrong Architecture.\n") + 126;
    if (errno == ENOENT)
        return my_puterror("Command not found.\n") + 127;
    if (errno == EACCES)
        return my_puterror("Permission denied.\n") + 126;
    if (WIFSIGNALED(status))
        return my_puterror(strsignal(WTERMSIG(status))) + 128;
    return my_puterror(strerror(errno)) + 1;
}

static int switch_error(int status)
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (SIGFPE == (WTERMSIG(status)))
        my_putstr("Floating exception");
    else
        my_putstr(strsignal(WTERMSIG(status)));
    my_putstr(__WCOREDUMP(status) ? " (core dumped)\n" : "\n");
    return (128 + WTERMSIG(status));
}

static char *concat_command(char *path, char *command)
{
    int len1 = strlen(path);
    int len2 = strlen(command);
    char *new = malloc(sizeof(char) * (len1 + len2 + 2));
    int i = 0;

    for (; path[i]; ++i)
        new[i] = path[i];
    new[i] = '/';
    ++i;
    for (int j = 0; command[j]; ++j){
        new[i] = command[j];
        ++i;
    }
    new[i] = '\0';
    return new;
}

char *find_in_env(char **env, char *to_find)
{
    for (int i = 0; env[i]; ++i){
        if (strncmp(env[i], to_find, strlen(to_find)) == 0)
            return (&env[i][+ strlen(to_find) + 1]);
    }
    return NULL;
}

char *verify_each_path(char *command, char *path)
{
    char *new = NULL;

    new = concat_command(path, command);
    if (access(new, F_OK) == 0)
        return new;
    else
        free(new);
    return NULL;
}

char *verify_command(char *command, char **env, table_t *env_listed)
{
    char *copy_path = strdup(table_search(env_listed, "PATH"));
    char **path;
    char *commandfullpath = NULL;

    if (copy_path == NULL)
        copy_path = strdup(find_in_env(env, "PATH"));
    path = split_string_tok(copy_path, ":");
    free(copy_path);
    for (int i = 0; path[i] != NULL; ++i) {
        commandfullpath = verify_each_path(command, path[i]);
        if (commandfullpath != NULL)
            return commandfullpath;
        free(commandfullpath);
    }
    return NULL;
}

void execute_command(char **env, table_t *env_listed, char **arg, int status)
{
    char *path = verify_command(arg[0], env, env_listed);

    if (strchr(arg[0], '/') != NULL)
        path = arg[0];
    if (arg[0][0] == '.' && arg[0][1] == '/' || arg[0][0] == '/') {
        status = execve(arg[0], arg, env);
        exit(is_error(arg[0], status));
    }
    if (path == NULL) {
        my_puterror(arg[0]);
        my_puterror(": Command not found.\n");
        exit(127);
    }
    status = execve(path, arg, env);
    exit(is_error(path, status));
}

int execute_program(char **env, table_t *env_listed, char **arg)
{
    pid_t child_pid = fork();
    int status = 0;

    if (child_pid == 0) {
        execute_command(env, env_listed, arg, status);
    } else {
        waitpid(child_pid, &status, 0);
        return switch_error(status);
    }
}
