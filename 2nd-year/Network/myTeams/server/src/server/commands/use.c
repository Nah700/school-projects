/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** use
*/

#include "../../../include/myteams_server.h"

static void reset_use(myteams_t *teams, int socket)
{
    get_client_by_socket(&teams->server->clients, socket)->team_uuid = NULL;
    get_client_by_socket(&teams->server->clients, socket)->channel_uuid = NULL;
    get_client_by_socket(&teams->server->clients, socket)->thread_uuid = NULL;
    clean_answer(803, "", socket, false);
}

static void use_team(myteams_t *teams, int socket, char **args)
{
    get_client_by_socket(&teams->server->clients, socket)->team_uuid
    = strdup(args[1]);
    clean_answer(800, "", socket, false);
    get_client_by_socket(&teams->server->clients, socket)->channel_uuid = NULL;
    get_client_by_socket(&teams->server->clients, socket)->thread_uuid = NULL;
}

static void use_channel(myteams_t *teams, int socket, char **args)
{
    get_client_by_socket(&teams->server->clients, socket)->team_uuid
    = strdup(args[1]);
    get_client_by_socket(&teams->server->clients, socket)->channel_uuid
    = strdup(args[2]);
    clean_answer(801, "", socket, false);
    get_client_by_socket(&teams->server->clients, socket)->thread_uuid = NULL;
}

static void use_thread(myteams_t *teams, int socket, char **args)
{
    get_client_by_socket(&teams->server->clients, socket)->team_uuid
    = strdup(args[1]);
    get_client_by_socket(&teams->server->clients, socket)->channel_uuid
    = strdup(args[2]);
    get_client_by_socket(&teams->server->clients, socket)->thread_uuid
    = strdup(args[3]);
    clean_answer(802, "", socket, false);
}

void use(myteams_t *teams, int socket, char **args)
{
    int tablen = get_tab_length(args);

    if (tablen < 1 || tablen > 4) {
        clean_answer(401, "", socket, false);
        return;
    }
    if (tablen == 1)
        reset_use(teams, socket);
    if (tablen == 2)
        use_team(teams, socket, args);
    if (tablen == 3)
        use_channel(teams, socket, args);
    if (tablen == 4)
        use_thread(teams, socket, args);
}
