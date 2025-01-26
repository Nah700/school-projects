/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** argsParsing
*/

#include "../include/myteams_server.h"

static int check_port(char *port)
{
    for (int i = 0; port[i] != '\0'; i++) {
        if (port[i] < '0' || port[i] > '9')
            return 84;
    }
    return 0;
}

static void help_message(void)
{
    printf("USAGE: ./myteams_server port\n\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
}

int check_args(int ac, char **av)
{
    int port = 0;

    if (ac != 2)
        return 84;
    if (strcmp(av[1], "-help") == 0) {
        help_message();
        return 0;
    }
    if (check_port(av[1]) == 84)
        return 84;
    port = atoi(av[1]);
    if (port < 1024 || port > 65535)
        return 84;
    return 0;
}
