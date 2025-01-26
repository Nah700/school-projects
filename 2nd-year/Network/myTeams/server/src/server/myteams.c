/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** myteams
*/

#include "../../include/myteams_server.h"

static void reload_server(server_t *server)
{
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_SET(server->socket, &server->read_fds);
    server->max_fd = server->socket;
    for (client_t *client = server->clients; client; client = client->next) {
        if (client->socket > 0) {
            FD_SET(client->socket, &server->read_fds);
        }
        if (client->socket > server->max_fd)
            server->max_fd = client->socket;
    }
}

static void manage_select(server_t *server)
{
    if (select(server->max_fd + 1, &server->read_fds,
        &server->write_fds, NULL, NULL) == -1) {
        perror("select");
        server->running = false;
    }
}

static bool client_exists(server_t *server, int client_socket)
{
    for (client_t *client = server->clients; client; client = client->next) {
        if (client->socket == client_socket)
            return true;
    }
    return false;
}

static void handle_client_connect(server_t *server)
{
    int client_soc;

    if (!FD_ISSET(server->socket, &server->read_fds))
        return;
    client_soc = accept(server->socket,
        (struct sockaddr *)&server->address,
        (socklen_t *)&server->address_length);
    if (client_soc == -1) {
        perror("accept");
        server->running = false;
        return;
    }
    if (client_exists(server, client_soc))
        close(client_soc);
    else {
        create_new_client(server, client_soc);
        dprintf(client_soc, "%s", format_string(get_protocol_answer(200)));
    }
}

static void handle_client_input(myteams_t *teams)
{
    int read_size;
    char buffer[1024] = {0};

    for (client_t *client = teams->server->clients; client;
    client = client->next) {
        if (client->socket <= 0
        || !FD_ISSET(client->socket, &teams->server->read_fds))
            continue;
        memset(buffer, 0, sizeof(buffer));
        read_size = read(client->socket, buffer, 1024);
        if (read_size == -1) {
            perror("read");
            teams->server->running = false;
        }
        if (read_size != 0) {
            handle_command(buffer, teams, client->socket);
        }
    }
}

static void handle_client_output(server_t *server)
{
    char buffer[1024] = {0};

    for (client_t *client = server->clients; client; client = client->next) {
        if (client->socket > 0
        && FD_ISSET(client->socket, &server->write_fds)) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "Hello from server\r\n");
            write(client->socket, buffer, strlen(buffer));
        }
    }
}

static void manage_server(myteams_t *teams)
{
    while (teams->server->running) {
        reload_server(teams->server);
        manage_select(teams->server);
        handle_client_connect(teams->server);
        handle_client_input(teams);
        handle_client_output(teams->server);
    }
}

int my_teams_server(int port)
{
    myteams_t *teams = init_myteams(port);

    global_server(teams, SETTER);
    signal(SIGINT, signal_handler);
    signal(0xb, signal_handler);
    manage_server(teams);
    free_myteams(teams);
    return 0;
}
