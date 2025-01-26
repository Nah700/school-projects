/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** exist_handler
*/

#include "myteams_server.h"

bool team_exist(myteams_t *teams, char *name)
{
    team_t *tmp = teams->teams;

    while (tmp){
        if (strcmp(tmp->name, name) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}

bool channel_exist(team_t *team, char *name)
{
    channel_t *tmp = team->channels;

    while (tmp){
        if (strcmp(tmp->name, name) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}

bool thread_exist(channel_t *channel, char *name)
{
    thread_t *tmp = channel->threads;

    while (tmp){
        if (strcmp(tmp->name, name) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}
