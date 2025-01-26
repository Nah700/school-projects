/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** channel
*/

#include "../../include/myteams_server.h"

channel_t *init_channel(char *name, char *description)
{
    channel_t *channel = malloc(sizeof(channel_t));

    channel->uuid = create_uuid();
    channel->name = strdup(name);
    channel->description = strdup(description);
    channel->threads = NULL;
    channel->next = NULL;
    return channel;
}

void free_channel(channel_t *channel)
{
    free(channel->name);
    free(channel);
}

void add_channel(team_t *team, channel_t *channel)
{
    channel_t *tmp;

    if (team->channels == NULL) {
        team->channels = channel;
        return;
    }
    tmp = team->channels;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = channel;
}

channel_t *get_channel_by_uuid(team_t *team, char *uuid)
{
    channel_t *tmp = team->channels;

    if (uuid == NULL)
        return NULL;
    while (tmp != NULL) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

channel_t *check_and_retrieve_channel(myteams_t *teams, team_t *team,
    char *uuid_channel, int client_socket)
{
    channel_t *channel;

    if (!team)
        return NULL;
    channel = get_channel_by_uuid(team, uuid_channel);
    if (channel == NULL) {
        clean_answer(703, uuid_channel, client_socket, false);
        return NULL;
    }
    if (is_user_in_team(team, teams, client_socket) == 0) {
        clean_answer(403, "", client_socket, false);
        return NULL;
    }
    return channel;
}
