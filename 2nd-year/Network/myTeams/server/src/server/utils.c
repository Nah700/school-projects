/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** utils
*/

#include "../../include/myteams_server.h"

myteams_t *global_server(myteams_t *server, globalmod_t mode)
{
    static myteams_t *global_server = NULL;

    if (mode == SETTER) {
        global_server = server;
        return NULL;
    } else
        return global_server;
}

void signal_handler(int signum)
{
    myteams_t *myteams = NULL;

    if (signum == SIGINT || signum == 0xb) {
        printf("\nKeyboardInterrupt: Closing listening...\n");
        myteams = global_server(NULL, GETTER);
        free_users(myteams->users);
        free_server(myteams->server);
        free(myteams);
        exit(0);
    }
}
