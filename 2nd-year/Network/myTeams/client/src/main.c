/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** main
*/

#include "../include/myteams_cli.h"

int main(int ac, char **av)
{
    if (check_args(ac, av) == 84)
        return 84;
    if (teams_client(av[1], atoi(av[2])) == 84)
        return 84;
    return 0;
}
