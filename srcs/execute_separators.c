/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** execute_seperators.c
*/

#include "../includes/shell.h"
#include "../includes/linked_lists.h"
#include "../includes/clib.h"
#include "../includes/tree.h"

static void handle_child_process(info_t *infos, tree_t *tree, int pipe_end)
{
    if (pipe_end == 1)
        dup2(infos->fd[pipe_end], STDOUT_FILENO);
    else
        dup2(infos->fd[pipe_end], STDIN_FILENO);
    close(infos->fd[0]);
    close(infos->fd[1]);
    if (tree->data && strcmp(tree->data, "|") == 0) {
        process_pipe(infos, tree);
    } else
        exec_tree(infos, tree);
    exit(0);
}

void process_pipe(info_t *infos, tree_t *tree)
{
    pid_t pid;

    if (pipe(infos->fd) == -1)
        return;
    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0)
        handle_child_process(infos, tree->left, 1);
    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0)
        handle_child_process(infos, tree->right, 0);
    close(infos->fd[0]);
    close(infos->fd[1]);
    wait(NULL);
    wait(NULL);
}

static void exec_redirection(info_t *infos, tree_t *tree, redirect_t *fd_infos)
{
    char **command = NULL;
    char *file_dup = strdup(tree->right->data);
    char *file_path = strtok(file_dup, " \t\n");
    int fd = open(file_path, fd_infos->flags, fd_infos->mode);

    if (fd == -1)
        exit(84);
    dup2(fd, fd_infos->int_or_out);
    close(fd);
    command = split_string_tok(tree->left->data, " \t\n");
    for (int i = 0; command[i]; i++)
        replace_local_variable_in_str(infos, command[i]);
    infos->return_value = sys_or_builtin(infos, infos->env, command,
        infos->return_value);
    free_2d_array(command);
    free(file_dup);
    exit(0);
}

void process_output_redirection(info_t *infos, tree_t *tree)
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        return;
    }
    if (pid == 0)
        exec_redirection(infos, tree, &(struct redirect_s){
            O_CREAT | O_WRONLY | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            STDOUT_FILENO
        });
    wait(NULL);
}

void process_input_redirection(info_t *infos, tree_t *tree)
{
    int fd;
    pid_t pid;
    char **command = NULL;

    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0)
        exec_redirection(infos, tree, &(struct redirect_s) {
            O_RDONLY,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            STDIN_FILENO
        });
    wait(NULL);
}

void process_add_output_redirection(info_t *infos, tree_t *tree)
{
    int fd;
    pid_t pid;
    char **command = NULL;

    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0)
        exec_redirection(infos, tree, &(struct redirect_s) {
            O_CREAT | O_WRONLY | O_APPEND,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            STDOUT_FILENO
        });
    wait(NULL);
}

void process_add_input_redirection(info_t *infos, tree_t *tree)
{
    int fd;
    pid_t pid;
    char **command = NULL;

    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0)
        exec_redirection(infos, tree, &(struct redirect_s) {
            O_RDONLY,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            STDIN_FILENO
        });
    wait(NULL);
}
