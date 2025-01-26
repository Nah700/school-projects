/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** commands
*/

#include "../../include/myteams_server.h"

void help(myteams_t *teams, int client_socket, char **args)
{
    teams = teams;
    args = args;
    dprintf(client_socket, "%s", format_string("200\n/login [\"username\"]\n"
    "/logout\n/users\n"
    "/user [\"username\"]\n/send [\"username\"] [\"message\"]\n"
    "/messages [\"username\"]\n/subscribe [\"team_uuid\"]\n/subscribed\n"
    "/unsubscribe [\"team_uuid\"]\n/use [\"team_uuid\"]\n"
    "/create [\"team_name\"] [\"team_description\"]\n/list\n"
    "/info [\"team_uuid\"]"));
}

void users(myteams_t *teams, int client_socket, char **args)
{
    char answer[256] = {0};
    user_t *copy = teams->users;

    if (get_len(args) != 1) {
        clean_answer(401, "", client_socket, false);
        return;
    }
    if (copy == NULL)
        clean_answer(995, "", client_socket, false);
    else {
        for (; copy->next; copy = copy->next){
            sprintf(answer, "%s;%s;%d", copy->uuid, copy->username,
                copy->is_connected);
            clean_answer(995, answer, client_socket, true);
        }
        sprintf(answer, "%s;%s;%d", copy->uuid, copy->username,
            copy->is_connected);
        clean_answer(995, answer, client_socket, false);
    }
}

void user(myteams_t *teams, int client_socket, char **args)
{
    char answer[256] = {0};

    if (get_len(args) != 2) {
        clean_answer(401, "", client_socket, false);
        return;
    }
    for (user_t *copy = teams->users; copy; copy = copy->next) {
        if (strcmp(copy->uuid, args[1]) == 0) {
            sprintf(answer, "%s;%s;%d", copy->uuid, copy->username,
                copy->is_connected);
            clean_answer(370, answer, client_socket, false);
            return;
        }
    }
    clean_answer(701, "", client_socket, false);
}

void messages(myteams_t *teams, int client_socket, char **args)
{
    private_message_t *tmp = teams->private_messages;
    char *user = get_uuid_by_name(teams, client_socket);

    if (get_len(args) != 2) {
        clean_answer(401, "", client_socket, false);
        return;
    }
    while (tmp) {
        if ((strcmp(tmp->receiver_uuid, args[1]) == 0 ||
            strcmp(tmp->receiver_uuid, user) == 0)
        && (strcmp(tmp->sender_uuid, args[1]) == 0 ||
            strcmp(tmp->sender_uuid, user) == 0)) {
            clean_answer(502, tmp->message, client_socket, true);
        }
        tmp = tmp->next;
    }
    clean_answer(502, "", client_socket, false);
}

static void remove_double_quottes(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++){
        if (tab[i] == NULL || strlen(tab[i]) == 0)
            continue;
        if (tab[i][0] == '\"' && tab[i][strlen(tab[i]) - 1] == '\"'){
            tab[i] = tab[i] + 1;
            tab[i][strlen(tab[i]) - 1] = '\0';
        }
    }
}

static int entirely_empty(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return false;
    return true;
}

static bool empty_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++){
        if (strlen(args[i]) == 0)
            return true;
        if (entirely_empty(args[i]) == true)
            return true;
    }
    return false;
}

static bool quit_handler(char **args, myteams_t *teams, int client_soc)
{
    if (strcmp(args[0], "/login") != 0 && !is_user_logged(teams, client_soc)) {
        clean_answer(403, "", client_soc, false);
        return true;
    }
    if (empty_args(args)) {
        clean_answer(402, "", client_soc, false);
        return true;
    }
    return false;
}

void handle_command(char *command, myteams_t *teams, int client_soc)
{
    bool found = false;
    char **args = str_to_word_array(command, ';');

    if (args[0] == NULL)
        return;
    remove_formatting(args[get_tab_length(args) - 1]);
    remove_double_quottes(args);
    if (quit_handler(args, teams, client_soc) == true)
        return;
    for (int i = 0; handlers[i].command != NULL && args[0] != NULL; i++)
        if (strcmp(args[0], handlers[i].command) == 0) {
            handlers[i].function(teams, client_soc, args);
            found = true;
            break;
        }
    if (!found)
        clean_answer(400, "", client_soc, false);
    free(args);
}
