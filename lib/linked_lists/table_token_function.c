/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** hash_function
*/

unsigned int djb2_hash(const char *str)
{
    unsigned int hash = 5381;

    for (unsigned int i = 0; str[i]; ++i)
        hash = ((hash << 5) + hash) + str[i];
    return hash;
}
