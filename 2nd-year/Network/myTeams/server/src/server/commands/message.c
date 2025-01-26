/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** message
*/

#include "../../../include/myteams_server.h"

static int send_message_error(myteams_t *teams, int client_socket, char **args)
{
    char answer[256] = {0};

    if (!is_user_logged(teams, client_socket)) {
        clean_answer(403, "", client_socket, false);
        return 84;
    }
    if (get_len(args) != 3) {
        clean_answer(401, "", client_socket, false);
        return 84;
    }
    for (client_t *copy = teams->server->clients; copy; copy = copy->next) {
        if (strcmp(copy->name, get_username_by_uuid(teams, args[1])) == 0) {
            return (copy->connected ? 1 : 2);
        }
    }
    sprintf(answer, "%s", get_uuid_by_name(teams, client_socket));
    clean_answer(701, answer, client_socket, false);
    return 84;
}

char *get_timestamp(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *timestamp = malloc(sizeof(char) * 20);

    sprintf(timestamp, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
        tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return timestamp;
}

void add_msg(private_message_t **msgs, private_message_t *msg)
{
    private_message_t *tmp = *msgs;

    if (tmp == NULL) {
        *msgs = msg;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = msg;
}

char *get_name_from_socket(myteams_t *teams, int socket)
{
    for (client_t *tmp = teams->server->clients; tmp; tmp = tmp->next)
        if (tmp->socket == socket)
            return tmp->name;
    return NULL;
}

static int get_reciver_socket(myteams_t *teams, char *receiver_name)
{
    for (client_t *tmp = teams->server->clients; tmp; tmp = tmp->next)
        if (strcmp(tmp->name, receiver_name) == 0)
            return tmp->socket;
    return -1;
}

static void recived_message(myteams_t *teams, char *sender_uuid,
    char *receiver_name, char *message)
{
    char answer[256] = {0};

    sprintf(answer, "%s;%s", sender_uuid, message);
    clean_answer(501, answer, get_reciver_socket(teams, receiver_name), false);
}

static private_message_t *init_msg(char *sender_uuid, char *receiver_uuid,
    char *msgs)
{
    private_message_t *msg = malloc(sizeof(private_message_t));

    msg->receiver_uuid = strdup(receiver_uuid);
    msg->sender_uuid = strdup(sender_uuid);
    msg->message = strdup(msgs);
    msg->uuid = create_uuid();
    msg->timestamp = get_timestamp();
    msg->next = NULL;
    return msg;
}

void send_message(myteams_t *teams, int client_socket, char **args)
{
    char answer[256] = {0};
    int error = send_message_error(teams, client_socket, args);
    private_message_t *msg;

    if (error == 84)
        return;
    msg = init_msg(get_uuid_by_name(teams, client_socket), args[1], args[2]);
    add_msg(&teams->private_messages, msg);
    sprintf(answer, "%s;%s;%s;%s", msg->uuid, msg->sender_uuid,
        msg->receiver_uuid, msg->message);
    clean_answer(500, answer, client_socket, false);
    server_event_private_message_sended(msg->sender_uuid, msg->receiver_uuid,
        msg->message);
    if (error)
        recived_message(teams, get_uuid_by_name(teams, client_socket),
            get_username_by_uuid(teams, args[1]), args[2]);
}
