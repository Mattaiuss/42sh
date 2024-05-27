/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** shell.h, all the command needed for the minishell
*/

#pragma once
#include "linked_lists.h"
#include "tree.h"
#include "clib.h"
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

#define CD 5863276
#define EXIT 2090237503
#define ENV 193490734
#define SETENV 461719610
#define UNSETENV 2633364285
#define PWD 193502992
#define ECHO 2090214596
#define BACK 5861473
#define BACK_W_SLASH 193428656
#define CURR 177619
#define CURR_W_SLASH 5861474
#define HOME_W_TILDE 177699
#define HOME_W_SLASH 1181875317
#define HOME_W_DASHES 5861439
#define DASH 177618
#define ALIAS 253185423
#define UNALIAS 969745458
#define HISTORY 1186495255
#define HISTORY_EXCLAMATION 177606
#define SET 193505681
#define UNSET 276986740

char **split_string_tok(char *arg, char *delimiters);
void free_2d_array(char **array);
char **table_to_array(table_t *env);
int execute_program(char **env, table_t *env_listed, char **arg);
int my_cd(char **args, table_t *env_listed);
int my_echo(char **args, table_t *env_listed, char **env, int r_value);
int my_env(table_t *env);
int my_setenv(table_t *env, char **args, char **envp);
int my_unsetenv(table_t *env, char **args);
int sys_or_builtin(info_t *info, char **env, char **args, int r_value);
table_t *create_table_from_env(char **env);
char *concat_env(char *key, char *value);
int print_pwd(table_t *env_listed);
void execute_command(char **env, table_t *env_listed, char **arg, int status);
