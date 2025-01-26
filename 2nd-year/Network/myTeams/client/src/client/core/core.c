/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** core
*/

#include "../../../include/myteams_cli.h"

static int get_user_input(client_t *client)
{
    if (getline(&client->message, &client->message_size, stdin) == -1) {
        perror("Failed to read input");
        return 1;
    }
    client->message[strlen(client->message) - 1] = '\0';
    if (*client->message == '\0')
        return 2;
    return 0;
}

static int receive_server_reply(client_t *client)
{
    int recv_size = receive_all(client);

    if (recv_size) {
        perror("Failed to receive server reply");
        return 1;
    }
    client->server_reply = remove_crlf(client->server_reply);
    return 0;
}

static void process_reply(char **reply_back, char *cmd_sent)
{
    print_arr(reply_back);
    if (reply_back == NULL
    || reply_back[0] == NULL
    || strlen(reply_back[0]) == 0)
        return;
    for (int i = 0; client_print_async_handler[i].code; i++) {
        if (!strcmp(client_print_async_handler[i].code, reply_back[0])) {
            client_print_async_handler[i].func(reply_back);
            return;
        }
    }
    for (int j = 0; client_print_handler[j].code; j++) {
        if (!strcmp(client_print_handler[j].code, cmd_sent + 1)) {
            client_print_handler[j].func(reply_back);
            break;
        }
    }
}

static int handle_server_reply_bis(client_t *client)
{
    char **splitted = str_to_word_array(remove_crlf(client->message), ';');
    char **reply_backn = str_to_word_array(client->server_reply, '\n');

    puts("Server reply :");
    for (int i = 0; reply_backn[i]; i++)
        process_reply(str_to_word_array(reply_backn[i], ';'), splitted[0]);
    if (strcmp(splitted[0], "/logout") == 0) {
        client->is_logout = true;
        return 1;
    }
    return 0;
}

void prepare_for_communication(client_t *client, int ret)
{
    char *str = (ret == 2) ? ">>> " : "\n>>> ";

    write(1, str, strlen(str));
    FD_ZERO(&client->readfds);
    FD_ZERO(&client->writefds);
    FD_SET(client->sock, &client->readfds);
    FD_SET(STDIN_FILENO, &client->readfds);
    client->max_fd = (STDIN_FILENO > client->sock ?
        STDIN_FILENO : client->sock) + 1;
}

bool handle_user_input(client_t *client, int *ret)
{
    if (FD_ISSET(STDIN_FILENO, &client->readfds)) {
        *ret = get_user_input(client);
        if (*ret == 2)
            return false;
        if (*ret) {
            return true;
        }
        FD_SET(STDIN_FILENO, &client->writefds);
    }
    return false;
}

int send_message_to_server(client_t *client)
{
    char *temp;

    sanitize_message(client->message);
    temp = realloc(client->message,
        strlen(client->message) + 3);
    if (temp == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    client->message = temp;
    client->message_size = strlen(client->message) + 3;
    strcat(client->message, "\r\n");
    if (send(client->sock, client->message, strlen(client->message), 0) < 0) {
        perror("Send failed");
        return 1;
    }
    return 0;
}

bool handle_server_reply(client_t *client)
{
    if (FD_ISSET(client->sock, &client->readfds)) {
        if (receive_server_reply(client)){
            return true;
        }
        if (handle_server_reply_bis(client) != 0)
            return true;
    }
    return false;
}
