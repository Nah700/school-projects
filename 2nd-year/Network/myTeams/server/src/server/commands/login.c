/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** commands_sec
*/

#include "../../../include/myteams_server.h"

void login(myteams_t *teams, int cli_s, char **args)
{
    user_t *tmp = {0};
    char answer[256] = {0};

    if (get_len(args) != 2) {
        clean_answer(401, "", cli_s, false);
        return;
    }
    if (args[1] == NULL){
        clean_answer(402, "", cli_s, false);
        return;
    }
    tmp = malloc(sizeof(user_t));
    check_user(tmp, args[1]);
    get_client_by_socket(&teams->server->clients, cli_s)->name
    = strdup(args[1]);
    get_client_by_socket(&teams->server->clients, cli_s)->connected = true;
    add_user(&teams->users, tmp, cli_s, teams);
    sprintf(answer, "%s;%s", get_uuid_by_name(teams, cli_s), args[1]);
    clean_answer(250, answer, cli_s, false);
    server_event_user_logged_in(get_uuid_by_name(teams, cli_s));
}

void logout(myteams_t *teams, int client_sock, char **args)
{
    char answer[256] = {0};
    client_t *tmp = get_client_by_socket(&teams->server->clients, client_sock);

    if (get_len(args) != 1) {
        clean_answer(401, "", client_sock, false);
        return;
    }
    if (tmp == NULL)
        return;
    get_user_by_uuid(teams, get_uuid_by_name(teams, client_sock))->is_connected
        = 0;
    disconnect_user_by_uuid(teams, get_uuid_by_name(teams, client_sock),
        client_sock);
    sprintf(answer, "%s;%s", get_uuid_by_name(teams, client_sock), tmp->name);
    clean_answer(300, answer, client_sock, false);
    server_event_user_logged_out(get_uuid_by_name(teams, client_sock));
    remove_client(&teams->server->clients, client_sock);
    close(client_sock);
}
