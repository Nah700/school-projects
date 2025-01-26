/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** main
*/

#include "../include/myteams_server.h"

int main(int ac, char **av)
{
    if (check_args(ac, av) == 84)
        return 84;
    my_teams_server(atoi(av[1]));
    return 0;
}
