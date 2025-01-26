/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** team
*/

#include "../../include/myteams_server.h"

team_t *init_team(char *name, char *description)
{
    team_t *team = malloc(sizeof(team_t));

    team->uuid = create_uuid();
    team->name = strdup(name);
    team->description = strdup(description);
    team->users = NULL;
    team->channels = NULL;
    team->next = NULL;
    return team;
}

void free_team(team_t *team)
{
    free(team->name);
    free(team);
}

void add_team(myteams_t *teams, team_t *team)
{
    team_t *tmp;

    if (teams->teams == NULL) {
        teams->teams = team;
        return;
    }
    tmp = teams->teams;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = team;
}

team_t *get_team_by_uuid(myteams_t *teams, char *uuid)
{
    team_t *tmp = teams->teams;

    if (uuid == NULL)
        return NULL;
    while (tmp != NULL) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

team_t *check_and_retrieve_team(myteams_t *teams, char *uuid_team,
    int client_socket)
{
    team_t *team = get_team_by_uuid(teams, uuid_team);

    if (!team) {
        clean_answer(702, uuid_team, client_socket, false);
        return NULL;
    }
    if (is_user_in_team(team, teams, client_socket) == 0) {
        clean_answer(403, "", client_socket, false);
        return NULL;
    }
    return team;
}
