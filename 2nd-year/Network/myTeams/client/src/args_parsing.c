/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** argsParsing
*/

#include "../include/myteams_cli.h"

static void help_message(void)
{
    printf("USAGE: ./myteams_cli ip port\n"
    "\tip\tis the server ip address on which the server socket listens\n"
    "\tport\tis the port number on which the server socket listens\n");
}

static int check_port(char *port)
{
    for (int i = 0; port[i] != '\0'; i++) {
        if (port[i] < '0' || port[i] > '9')
            return 84;
    }
    return 0;
}

static int check_ip(char *ip)
{
    regex_t regex;
    int rc;

    rc = regcomp(&regex, "^([0-9]{1,3}\\.){3}[0-9]{1,3}$", REG_EXTENDED);
    rc = regexec(&regex, ip, 0, NULL, 0);
    if (rc != 0){
        regfree(&regex);
        return 84;
    }
    regfree(&regex);
    return 0;
}

int check_args(int ac, char **av)
{
    int port = 0;

    if (ac < 2 || ac > 3)
        return 84;
    if (ac == 2) {
        if (strcmp(av[1], "-help") == 0){
            help_message();
            return 0;
        }
        return 84;
    }
    if (check_port(av[2]) == 84 || check_ip(av[1]) == 84)
        return 84;
    port = atoi(av[2]);
    if (port < 1024 || port > 65535)
        return 84;
    return 0;
}
