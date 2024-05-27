/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** display sentence
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>

int my_putstr(char const *str)
{
    if (str == NULL)
        return 84;
    if (write(STDOUT_FILENO, str, strlen(str)) == -1)
        return 84;
    return 0;
}
