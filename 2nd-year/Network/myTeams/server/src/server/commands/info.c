/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** info
*/

#include "../../../include/myteams_server.h"

static void display_user(myteams_t *teams, int client_socket)
{
    char a[256] = {0};

    for (user_t *tm = teams->users; tm; tm = tm->next) {
        if (strcmp(get_uuid_by_name(teams, client_socket), tm->uuid) == 0) {
            sprintf(a, "%s;%s;%d", tm->uuid, tm->username, tm->is_connected);
            clean_answer(370, a, client_socket, false);
        }
    }
}

static void display_teams(myteams_t *teams, int client_socket,
    client_t *client)
{
    char answer[256] = {0};
    team_t *team = check_and_retrieve_team(teams, client->team_uuid,
    client_socket);

    if (!team)
        return;
    else {
        sprintf(answer, "%s;%s;%s", team->uuid, team->name,
        team->description);
        clean_answer(1050, answer, client_socket, false);
    }
}

static void display_channels(myteams_t *teams, int client_socket,
    client_t *client)
{
    char answer[256] = {0};
    team_t *team = check_and_retrieve_team(teams, client->team_uuid,
    client_socket);
    channel_t *channel;

    if (team == NULL)
        return;
    channel = team->channels;
    if (!channel)
        clean_answer(1051, "", client_socket, false);
    else {
        sprintf(answer, "%s;%s;%s", channel->uuid, channel->name,
        channel->description);
        clean_answer(1051, answer, client_socket, false);
    }
}

static void display_threads(myteams_t *teams, int client_socket,
    client_t *client)
{
    char answer[256] = {0};
    team_t *team = check_and_retrieve_team(teams, client->team_uuid,
    client_socket);
    channel_t *channel = check_and_retrieve_channel(teams, team,
    client->channel_uuid, client_socket);
    thread_t *thread;

    if (team == NULL || channel == NULL)
        return;
    thread = channel->threads;
    if (!thread)
        clean_answer(1052, "", client_socket, false);
    else {
        sprintf(answer, "%s;%s;%s;%s;%s", thread->uuid, get_uuid_by_name(teams,
            client_socket), thread->timestamp, thread->name,
                thread->description);
        clean_answer(1052, answer, client_socket, false);
    }
}

void info(myteams_t *myteams, int client_socket, char **args)
{
    int tablen = get_tab_length(args);
    client_t *tmp = get_client_by_socket(&myteams->server->clients,
    client_socket);

    if (tablen != 1 || tmp == NULL)
        clean_answer(401, "", client_socket, false);
    if (tmp->team_uuid == NULL)
        display_user(myteams, client_socket);
    if (tmp->team_uuid != NULL && tmp->channel_uuid == NULL
    && tmp->thread_uuid == NULL)
        display_teams(myteams, client_socket, tmp);
    if (tmp->channel_uuid != NULL && tmp->team_uuid != NULL
    && tmp->thread_uuid == NULL)
        display_channels(myteams, client_socket, tmp);
    if (tmp->thread_uuid != NULL && tmp->channel_uuid != NULL
        && tmp->team_uuid != NULL)
        display_threads(myteams, client_socket, tmp);
}
