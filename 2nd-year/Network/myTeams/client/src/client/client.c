/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** client
*/

#include "../../include/myteams_cli.h"

static void cleanup_client(client_t *client)
{
    free(client->server_reply);
    free(client->message);
    close(client->sock);
}

static int setup_socket(client_t *client, char *ip, int port)
{
    client->is_logout = false;
    client->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sock == -1) {
        perror("socket failed");
        return 1;
    }
    client->server.sin_addr.s_addr = inet_addr(ip);
    client->server.sin_family = AF_INET;
    client->server.sin_port = htons(port);
    return 0;
}

static int connect_to_server(client_t *client)
{
    if (connect(client->sock, (struct sockaddr *)&client->server,
        sizeof(client->server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
    global_client(client, SETTER);
    signal(SIGINT, signal_handler);
    signal(0xb, signal_handler);
    return 0;
}

static int initialize_server_reply(client_t *client)
{
    if (receive_all(client)) {
        perror("Failed to receive server reply");
        return 1;
    }
    puts("Trying to connect to server...");
    for (size_t i = 0; i < get_len_crlf(client->server_reply); ++i) {
        if (client->server_reply[i] == ';')
            client->server_reply[i] = ' ';
        write(STDOUT_FILENO, &client->server_reply[i], 1);
    }
    client->message = NULL;
    client->message_size = 0;
    return 0;
}

static int initialize_client(client_t *client, char *ip, int port)
{
    if (setup_socket(client, ip, port) ||
        connect_to_server(client) ||
        initialize_server_reply(client))
        return 1;
    return 0;
}

int teams_client(char *ip, int port)
{
    client_t client;
    int result;

    if (initialize_client(&client, ip, port) != 0)
        return 84;
    result = communicate_with_server(&client);
    cleanup_client(&client);
    return result;
}
