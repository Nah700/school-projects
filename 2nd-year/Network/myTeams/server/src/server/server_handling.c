/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** srverHandling
*/

#include "../../include/myteams_server.h"

server_t *init_server(int port)
{
    server_t *server = malloc(sizeof(server_t));

    server->clients = NULL;
    server->port = port;
    server->running = true;
    server->max_fd = 0;
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);
    server->address_length = sizeof(server->address);
    bind(server->socket, (struct sockaddr *)&server->address,
    server->address_length);
    listen(server->socket, 30);
    return server;
}

void free_client(server_t *server)
{
    client_t *client = server->clients;
    client_t *next = NULL;

    while (client) {
        next = client->next;
        free(client);
        client = next;
    }
}

void free_server(server_t *server)
{
    free_client(server);
    close(server->socket);
    free(server);
}

void free_users(user_t *users)
{
    user_t *user = users;
    user_t *next = NULL;

    while (user) {
        next = user->next;
        free(user);
        user = next;
    }
}

int get_max_fd(client_t *clients)
{
    int max = 0;

    for (client_t *client = clients; client; client = client->next) {
        if (client->socket > max)
            max = client->socket;
    }
    return max;
}
