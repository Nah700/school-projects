/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** clientHandling
*/

#include "../../include/myteams_server.h"

void create_new_client(server_t *server, int client_socket)
{
    client_t *new_client = malloc(sizeof(client_t));
    client_t *tmp;

    new_client->socket = client_socket;
    new_client->name = NULL;
    new_client->connected = false;
    new_client->next = NULL;
    new_client->team_uuid = NULL;
    new_client->channel_uuid = NULL;
    new_client->thread_uuid = NULL;
    if (server->clients == NULL)
        server->clients = new_client;
    else {
        tmp = server->clients;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new_client;
    }
}

void remove_client(client_t **clients, int socket)
{
    client_t *tmp = *clients;
    client_t *prev = NULL;

    if (tmp != NULL && tmp->socket == socket) {
        *clients = tmp->next;
        free(tmp->name);
        return;
    }
    while (tmp != NULL && tmp->socket != socket) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp->name);
}

client_t *get_client_by_socket(client_t **clients, int socket)
{
    client_t *tmp = *clients;

    while (tmp != NULL) {
        if (tmp->socket == socket){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}
