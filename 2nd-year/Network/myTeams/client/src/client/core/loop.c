/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** loop
*/

#include "../../../include/myteams_cli.h"

static bool handle_client_message(client_t *client)
{
    if (FD_ISSET(STDIN_FILENO, &client->writefds) && client->message) {
        if (send_message_to_server(client)) {
            return true;
        }
    }
    return false;
}

static int handle_shit(client_t *client, int ret, bool *error)
{
    if (handle_user_input(client, &ret) || handle_server_reply(client)
        || handle_client_message(client)) {
        if (!client->is_logout)
            *error = true;
        return true;
    }
    return false;
}

int communicate_with_server(client_t *client)
{
    bool error = false;
    int ret = 0;

    while (1) {
        prepare_for_communication(client, ret);
        if (select(client->max_fd, &client->readfds, &client->writefds,
            NULL, NULL) < 0) {
            perror("Select error");
            break;
        }
        if (handle_shit(client, ret, &error))
            break;
    }
    return error ? 84 : 0;
}
