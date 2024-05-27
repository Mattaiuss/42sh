/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** my_put_nbr
*/

#include <limits.h>
#include "../../includes/clib.h"

static int my_put_alt(long int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb > 9) {
        my_putnbr(nb / 10);
    }
    my_putchar('0' + (nb % 10));
    return 0;
}

int my_putnbr(int nb)
{
    return my_put_alt(nb);
}
