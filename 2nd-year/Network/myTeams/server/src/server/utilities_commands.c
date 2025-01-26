/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** utilities_commands
*/

#include "../../include/myteams_server.h"

int get_len(char **tab)
{
    int i = 0;

    for (; tab[i]; i++);
    return i;
}

int is_user_logged(myteams_t *teams, int client_socket)
{
    for (client_t *tmp = teams->server->clients; tmp; tmp = tmp->next) {
        if (tmp->socket == client_socket && tmp->connected == true) {
            return 1;
        }
    }
    return 0;
}

user_t *get_user_by_uuid(myteams_t *teams, char *uuid)
{
    user_t *tmp = teams->users;

    while (tmp) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

user_register_channel_t *init_team_user(user_t *user)
{
    user_register_channel_t *n_user = malloc(sizeof(user_register_channel_t));

    n_user->uuid = strdup(user->uuid);
    n_user->name = strdup(user->username);
    n_user->is_connected = user->is_connected;
    n_user->next = NULL;
    return n_user;
}

static bool is_user_registered(user_register_channel_t *user, char *uuid)
{
    if (strcmp(user->uuid, uuid) == 0)
        return false;
    return true;
}

void disconnect_user_by_uuid(myteams_t *teams, char *uuid, int socket)
{
    for (team_t *tmp = teams->teams; tmp; tmp = tmp->next) {
        if (!is_user_in_team(tmp, teams, socket))
            continue;
        for (user_register_channel_t *tmp2 = tmp->users; tmp2
        || tmp2->is_connected == false; tmp2 = tmp2->next) {
            tmp2->is_connected = is_user_registered(tmp2, uuid);
        }
    }
}
