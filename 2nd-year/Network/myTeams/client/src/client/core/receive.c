/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** receive
*/

#include "../../../include/myteams_cli.h"

static int receive_and_check(client_t *client, int total_received,
    int buffer_size)
{
    int received = recv(client->sock, client->server_reply
        + total_received, buffer_size - total_received, 0);

    if (received < 0) {
        perror("recv failed");
        exit(0);
    } else if (received == 0)
        exit(0);
    total_received += received;
    client->server_reply[total_received] = '\0';
    if (strstr(client->server_reply, "\r\n") != NULL)
        return 0;
    return total_received;
}

static int expand_buffer_if_needed(client_t *client, int total_received,
    int *buffer_size)
{
    char *new_ptr;

    if (total_received == *buffer_size) {
        *buffer_size *= 2;
        new_ptr = realloc(client->server_reply, *buffer_size
            * sizeof(char));
        if (new_ptr == NULL) {
            perror("realloc failed");
            return 1;
        }
        client->server_reply = new_ptr;
    }
    return 0;
}

static int receive_data(client_t *client, int buffer_size)
{
    int total_received = 0;

    while (1) {
        total_received =
            receive_and_check(client, total_received, buffer_size);
        if (total_received <= 0)
            return total_received;
        if (expand_buffer_if_needed(client, total_received, &buffer_size)
            != 0)
            return 1;
    }
    return 0;
}

static int allocate_memory(client_t *client, int buffer_size)
{
    client->server_reply = malloc(buffer_size * sizeof(char));
    if (client->server_reply == NULL) {
        perror("malloc failed");
        return 1;
    }
    return 0;
}

int receive_all(client_t *client)
{
    int buffer_size = 2000;

    if (allocate_memory(client, buffer_size)
        || receive_data(client, buffer_size))
        return 1;
    return 0;
}
