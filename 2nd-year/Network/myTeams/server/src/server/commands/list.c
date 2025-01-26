/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** list
*/

#include "../../../include/myteams_server.h"

static void display_teams(team_t *team, int client_socket)
{
    char answer[256] = {0};

    if (!team)
        clean_answer(997, "", client_socket, false);
    else {
        while (team->next != NULL) {
            sprintf(answer, "%s;%s;%s", team->uuid, team->name,
            team->description);
            clean_answer(997, answer, client_socket, true);
            team = team->next;
        }
        sprintf(answer, "%s;%s;%s", team->uuid, team->name,
        team->description);
        clean_answer(997, answer, client_socket, false);
    }
}

static void display_channels(myteams_t *teams, int socket,
    client_t *client)
{
    char answer[256] = {0};
    team_t *team = check_and_retrieve_team(teams, client->team_uuid, socket);
    channel_t *channel;

    if (team == NULL)
        return;
    channel = team->channels;
    if (!channel)
        clean_answer(998, "", socket, false);
    else {
        while (channel->next != NULL) {
            sprintf(answer, "%s;%s;%s", channel->uuid, channel->name,
            channel->description);
            clean_answer(998, answer, socket, true);
            channel = channel->next;
        }
        sprintf(answer, "%s;%s;%s", channel->uuid, channel->name,
        channel->description);
        clean_answer(998, answer, socket, false);
    }
}

static channel_t *get_channel_style(myteams_t *teams, int socket,
    client_t *client)
{
    team_t *team = check_and_retrieve_team(teams, client->team_uuid, socket);
    channel_t *channel = check_and_retrieve_channel(teams, team,
    client->channel_uuid, socket);

    if (team == NULL || channel == NULL)
        return NULL;
    return channel;
}

static void display_threads(myteams_t *teams, int socket,
    client_t *client)
{
    char answer[256] = {0};
    channel_t *channel = get_channel_style(teams, socket, client);
    char *user = get_uuid_by_name(teams, socket);
    thread_t *thread;

    if (channel == NULL)
        return;
    thread = channel->threads;
    if (!thread)
        clean_answer(999, "", socket, false);
    else {
        for (; thread->next != NULL; thread = thread->next) {
            sprintf(answer, "%s;%s;%s;%s;%s", thread->uuid, user,
            thread->timestamp, thread->name, thread->description);
            clean_answer(999, answer, socket, true);
        }
        sprintf(answer, "%s;%s;%s;%s;%s", thread->uuid, user,
        thread->timestamp, thread->name, thread->description);
        clean_answer(999, answer, socket, false);
    }
}

static thread_t *get_thread_style(myteams_t *teams, int socket,
    client_t *client)
{
    team_t *team = check_and_retrieve_team(teams, client->team_uuid, socket);
    channel_t *channel = check_and_retrieve_channel(teams, team,
    client->channel_uuid, socket);
    thread_t *thread = check_and_retrieve_thread(channel, client->thread_uuid,
    socket);

    if (team == NULL || channel == NULL || thread == NULL)
        return NULL;
    return thread;
}

static void display_comments(myteams_t *teams, int socket,
    client_t *client)
{
    char answer[256] = {0};
    thread_t *thread = get_thread_style(teams, socket, client);
    char *user = get_uuid_by_name(teams, socket);
    comment_t *comment;

    if (thread == NULL)
        return;
    comment = thread->comments;
    if (!comment)
        clean_answer(1000, "", socket, false);
    else {
        for (; comment->next != NULL; comment = comment->next) {
            sprintf(answer, "%s;%s;%s;%s", thread->uuid, user,
            comment->timestamp, comment->message);
            clean_answer(1000, answer, socket, true);
        }
        sprintf(answer, "%s;%s;%s", comment->uuid, comment->message,
        comment->timestamp);
        clean_answer(1000, answer, socket, false);
    }
}

void list(myteams_t *myteams, int client_socket, char **args)
{
    int tablen = get_tab_length(args);
    client_t *tmp = get_client_by_socket(&myteams->server->clients,
    client_socket);

    if (tablen != 1 || tmp == NULL)
        clean_answer(401, "", client_socket, false);
    if (tmp->team_uuid == NULL)
        display_teams(myteams->teams, client_socket);
    if (tmp->channel_uuid == NULL && tmp->team_uuid != NULL)
        display_channels(myteams, client_socket, tmp);
    if (tmp->thread_uuid == NULL && tmp->channel_uuid != NULL
        && tmp->team_uuid != NULL)
        display_threads(myteams, client_socket, tmp);
    if (tmp->thread_uuid != NULL && tmp->channel_uuid != NULL
        && tmp->team_uuid != NULL)
        display_comments(myteams, client_socket, tmp);
}
