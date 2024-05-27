/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** fuer
*/

#include <unistd.h>
#include <stdio.h>

int my_putchar(char const c)
{
    return write(1, &c, 1) == -1 ? 84 : 0;
}
