/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** create
*/

#include "../../../include/myteams_server.h"

static void print_create_team(team_t *new_team, int socket, client_t *client,
    myteams_t *teams)
{
    char answer[256] = {0};

    sprintf(answer, "%s;%s;%s", new_team->uuid, new_team->name,
    new_team->description);
    clean_answer(947, answer, socket, true);
    for (client_t *tmp = client; tmp != NULL; tmp = tmp->next) {
        if (is_user_logged(teams, tmp->socket) == false)
            continue;
        sprintf(answer, "%s;%s;%s", new_team->uuid, new_team->name,
        new_team->description);
        clean_answer(951, answer, tmp->socket, false);
    }
}

static void create_team(myteams_t *teams, int socket, char **args)
{
    team_t *new_team;
    char *user = get_uuid_by_name(teams, socket);

    if (team_exist(teams, args[1]) == true) {
        clean_answer(705, "", socket, false);
        return;
    }
    new_team = init_team(args[1], args[2]);
    add_team(teams, new_team);
    print_create_team(new_team, socket, teams->server->clients, teams);
    server_event_team_created(new_team->uuid, new_team->name, user);
}

static void print_create_channel(channel_t *new_channel, int socket,
    team_t *team, myteams_t *teams)
{
    char answer[256] = {0};

    sprintf(answer, "%s;%s;%s", new_channel->uuid, new_channel->name,
    new_channel->description);
    clean_answer(948, answer, socket, true);
    for (client_t *tmp = teams->server->clients; tmp; tmp = tmp->next) {
        if (is_user_logged(teams, tmp->socket) == false)
            continue;
        if (is_user_in_team(get_team_by_uuid(teams, team->uuid), teams,
        tmp->socket) == 0)
            continue;
        sprintf(answer, "%s;%s;%s", new_channel->uuid, new_channel->name,
        new_channel->description);
        clean_answer(952, answer, tmp->socket, false);
    }
}

static void create_channel(myteams_t *teams, int socket, char **args,
    client_t *client)
{
    team_t *team = check_and_retrieve_team(teams, client->team_uuid, socket);
    channel_t *new_channel;

    if (team == NULL)
        return;
    if (channel_exist(team, args[1]) == true) {
        clean_answer(705, "", socket, false);
        return;
    }
    new_channel = init_channel(args[1], args[2]);
    add_channel(team, new_channel);
    print_create_channel(new_channel, socket, team, teams);
    server_event_channel_created(team->uuid, new_channel->uuid,
    new_channel->name);
}

static void print_create_thread(thread_t *new_thread, int socket,
    team_t *team, myteams_t *teams)
{
    char answer[256] = {0};

    sprintf(answer, "%s;%s;%s;%s;%s", new_thread->uuid,
        get_uuid_by_name(teams, socket), new_thread->timestamp,
        new_thread->name, new_thread->description);
    clean_answer(949, answer, socket, true);
    for (client_t *tmp = teams->server->clients; tmp; tmp = tmp->next) {
        if (is_user_logged(teams, tmp->socket) == false)
            continue;
        if (is_user_in_team(get_team_by_uuid(teams, team->uuid),
        teams, tmp->socket) == 0)
            continue;
        sprintf(answer, "%s;%s;%s;%s;%s", new_thread->uuid,
            get_uuid_by_name(teams, socket), new_thread->timestamp,
            new_thread->name, new_thread->description);
        clean_answer(953, answer, tmp->socket, false);
    }
}

static void create_thread(myteams_t *teams, int socket, char **args,
    client_t *client)
{
    team_t *team = check_and_retrieve_team(teams, client->team_uuid, socket);
    channel_t *channel = check_and_retrieve_channel(teams, team,
    client->channel_uuid, socket);
    char *user = get_uuid_by_name(teams, socket);
    thread_t *new_thread;

    if (team == NULL || channel == NULL || user == NULL)
        return;
    if (thread_exist(channel, args[1]) == true) {
        clean_answer(705, "", socket, false);
        return;
    }
    new_thread = init_thread(args[1], args[2]);
    add_thread(channel, new_thread);
    print_create_thread(new_thread, socket, team, teams);
    server_event_thread_created(channel->uuid, new_thread->uuid, user,
    new_thread->name, new_thread->description);
}

static thread_t *create_comment_style(myteams_t *teams, int socket,
    client_t *client)
{
    team_t *team = check_and_retrieve_team(teams, client->team_uuid, socket);
    channel_t *channel = check_and_retrieve_channel(teams, team,
    client->channel_uuid, socket);
    thread_t *thread = check_and_retrieve_thread(channel,
    client->thread_uuid, socket);

    if (!team || !channel || !thread){
        return NULL;
    }
    if (is_user_in_team(team, teams, socket) == 0) {
        clean_answer(403, "", socket, false);
        return NULL;
    }
    return thread;
}

static void create_comment(myteams_t *teams, int socket, char **args,
    client_t *client)
{
    thread_t *thread = create_comment_style(teams, socket, client);
    char *user = get_uuid_by_name(teams, socket);
    comment_t *new_comment;

    if (thread == NULL)
        return;
    new_comment = init_comment(args[1]);
    add_comment(thread, new_comment);
    print_create_reply(thread, new_comment, client, teams);
    server_event_reply_created(thread->uuid, user, new_comment->message);
}

static void sub_create_team(client_t *tmp, myteams_t *teams, int socket,
    char **args)
{
    if (tmp->team_uuid == NULL)
        create_team(teams, socket, args);
    if (tmp->team_uuid != NULL && tmp->channel_uuid == NULL)
        create_channel(teams, socket, args, tmp);
    if (tmp->team_uuid != NULL && tmp->channel_uuid != NULL
    && tmp->thread_uuid == NULL)
        create_thread(teams, socket, args, tmp);
}

void create(myteams_t *teams, int socket, char **args)
{
    int tablen = get_tab_length(args);
    client_t *tmp = get_client_by_socket(&teams->server->clients, socket);

    if (tablen < 2 || tablen > 3 || strlen(args[1]) > 32 || tmp == NULL) {
        clean_answer(401, "", socket, false);
        return;
    }
    if (tablen == 3)
        sub_create_team(tmp, teams, socket, args);
    else {
        if (tmp->team_uuid != NULL && tmp->channel_uuid != NULL
        && tmp->thread_uuid != NULL)
            create_comment(teams, socket, args, tmp);
        else
            clean_answer(401, "", socket, false);
    }
}
