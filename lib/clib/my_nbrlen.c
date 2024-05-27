/*
** EPITECH PROJECT, 2024
** my_nbrlen
** File description:
** my_nbrlen -> give the length of a number
*/

#include "../../includes/clib.h"

int my_nbrlen(int nb)
{
    int cpt = 0;

    if (nb < 0) {
        nb = -nb;
        cpt++;
    }
    for (; nb > 9; cpt++)
        nb = nb / 10;
    return cpt;
}
