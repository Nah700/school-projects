/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** subscribe
*/

#include "../../../include/myteams_server.h"

static int add_user_to_team(team_t *team, user_t *user)
{
    user_register_channel_t *n_user;
    user_register_channel_t *tmp = team->users;

    for (user_register_channel_t *tmp = team->users; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, user->uuid) == 0) {
            return 1;
        }
    }
    n_user = init_team_user(user);
    if (tmp == NULL) {
        team->users = n_user;
        return 0;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = n_user;
    return 0;
}

int team_found(team_t *copy, myteams_t *teams, int client_socket, char *teamu)
{
    char answer[256] = {0};
    user_t *copy_user = get_user_by_uuid(teams, get_uuid_by_name(teams,
        client_socket));

    if (strcmp(copy->uuid, teamu) == 0) {
        if (add_user_to_team(copy, copy_user)) {
            clean_answer(705, "", client_socket, false);
            return 1;
        }
        sprintf(answer, "%s;%s", get_uuid_by_name(teams, client_socket),
            copy->uuid);
        clean_answer(600, answer, client_socket, false);
        server_event_user_subscribed(copy->uuid, get_uuid_by_name(teams,
            client_socket));
        return 1;
    }
    return 0;
}

void subscribe(myteams_t *teams, int client_socket, char **args)
{
    char answer[256] = {0};

    if (get_len(args) != 2) {
        clean_answer(401, "", client_socket, false);
        return;
    }
    for (team_t *copy = teams->teams; copy; copy = copy->next) {
        if (team_found(copy, teams, client_socket, args[1]))
            return;
    }
    sprintf(answer, "%s", args[1]);
    clean_answer(702, answer, client_socket, false);
}

int is_user_in_team(team_t *team, myteams_t *teams, int client_socket)
{
    if (team->users == NULL)
        return 0;
    for (user_register_channel_t *tmp = team->users; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, get_uuid_by_name(teams, client_socket)) == 0)
            return 1;
    }
    return 0;
}

static void subscribed_basic(myteams_t *teams, int client_socket)
{
    char answer[256] = {0};

    if (teams->teams == NULL) {
        clean_answer(997, "", client_socket, false);
        return;
    }
    for (team_t *co = teams->teams; co; co = co->next) {
        if (is_user_in_team(co, teams, client_socket) == 1) {
            sprintf(answer, "%s;%s;%s", co->uuid, co->name, co->description);
            clean_answer(997, answer, client_socket, true);
        }
    }
    clean_answer(997, "", client_socket, false);
}

static void print_all_team_users(int client_socket, team_t *copy)
{
    char answer[256] = {0};

    for (user_register_channel_t *tmp = copy->users; tmp; tmp = tmp->next) {
        sprintf(answer, "%s;%s;%d", tmp->uuid, tmp->name, tmp->is_connected);
        clean_answer(995, answer, client_socket, true);
    }
}

static void subscribed_one(myteams_t *teams, int client_socket, team_t *team)
{
    if (team == NULL) {
        clean_answer(702, "", client_socket, false);
        return;
    }
    for (team_t *copy = teams->teams; copy; copy = copy->next) {
        if (strcmp(copy->uuid, team->uuid) == 0) {
            print_all_team_users(client_socket, copy);
            clean_answer(995, "", client_socket, false);
            return;
        }
    }
    return;
}

void subscribed(myteams_t *teams, int client_socket, char **args)
{
    if (get_len(args) > 2 || get_len(args) < 1) {
        clean_answer(401, "", client_socket, false);
        return;
    }
    if (get_len(args) == 1) {
        subscribed_basic(teams, client_socket);
    }
    if (get_len(args) == 2) {
        subscribed_one(teams, client_socket, get_team_by_uuid(teams, args[1]));
    }
}

static void remove_user_from_team(team_t *team, user_t *user)
{
    user_register_channel_t *tmp = team->users;
    user_register_channel_t *prev = NULL;

    if (team == NULL || user == NULL)
        return;
    if (tmp != NULL && strcmp(tmp->uuid, user->uuid) == 0) {
        team->users = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && strcmp(tmp->uuid, user->uuid) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

void unsubscribe(myteams_t *teams, int client_socket, char **args)
{
    char answer[256] = {0};

    if (get_len(args) != 2) {
        clean_answer(401, "", client_socket, false);
        return;
    }
    for (team_t *copy = teams->teams; copy; copy = copy->next) {
        if (strcmp(copy->uuid, args[1]) == 0)
            remove_user_from_team(copy, teams->users);
    }
    sprintf(answer, "%s;%s", get_uuid_by_name(teams, client_socket), args[1]);
    clean_answer(650, answer, client_socket, false);
}
