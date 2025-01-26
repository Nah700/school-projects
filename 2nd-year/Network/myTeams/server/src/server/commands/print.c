/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** print
*/

#include "myteams_server.h"

void print_create_reply(thread_t *thread, comment_t *new_comment,
    client_t *client, myteams_t *teams)
{
    char answer[256] = {0};
    team_t *team = check_and_retrieve_team(teams, client->team_uuid,
    client->socket);

    sprintf(answer, "%s;%s;%s;%s", thread->uuid,
    get_uuid_by_name(teams, client->socket), new_comment->timestamp,
    new_comment->message);
    clean_answer(950, answer, client->socket, true);
    for (client_t *tmp = teams->server->clients; tmp; tmp = tmp->next) {
        if (is_user_logged(teams, tmp->socket) == false)
            continue;
        if (is_user_in_team(get_team_by_uuid(teams, team->uuid),
        teams, tmp->socket) == 0)
            continue;
        sprintf(answer, "%s;%s;%s;%s", team->uuid, thread->uuid,
        get_uuid_by_name(teams, client->socket), new_comment->message);
        clean_answer(954, answer, tmp->socket, false);
    }
}
