/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** myteams_cli
*/

#ifndef MYTEAMS_CLI_H_
    #define MYTEAMS_CLI_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <regex.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <stdbool.h>
    #include <signal.h>
    #include <sys/select.h>
    #define __USE_XOPEN
    #include <time.h>

    #include "../../libs/myteams/logging_client.h"
    #include "../../commons/utils.h"

typedef struct {
    int sock;
    struct sockaddr_in server;
    char *message;
    size_t message_size;
    char *server_reply;
    fd_set readfds, writefds;
    int max_fd;
    bool is_logout;
} client_t;

// Client functions
int main(int ac, char **av);
int check_args(int ac, char **av);
int teams_client(char *ip, int port);

// Core functions
int communicate_with_server(client_t *client);

// Receive functions
int receive_all(client_t *client);

char *sanitize_message(char *str);
client_t *global_client(client_t *client, globalmod_t mode);
void signal_handler(int signum);
int communicate_with_server(client_t *client);

void prepare_for_communication(client_t *client, int ret);
bool handle_user_input(client_t *client, int *ret);
bool handle_server_reply(client_t *client);
int send_message_to_server(client_t *client);

time_t convert_to_time(char *time_str);
size_t tab_len(char **tab);

void print_login(char **args);
void print_logout(char **args);
void print_create(char **args);
void print_info(char **args);
void print_receive_private_msg(char **args);
void print_list(char **args);
void print_subscribe(char **args);
void print_users(char **args);
void print_subscribed(char **args);
void print_unsubscribe(char **args);
void print_messsages(char **args);
void print_user(char **args);
void print_unsubscribe(char **args);
void print_subscribed(char **args);
void print_help(char **args);

static const struct {
    char *code;
    void (*func)(char **args);
} client_print_async_handler[] = {
    {"501", &print_receive_private_msg},
    {"951", &print_create},
    {"952", &print_create},
    {"953", &print_create},
    {"954", &print_create},
    {NULL, NULL}
};

static const struct {
    char *code;
    void (*func)(char **args);
} client_print_handler[] = {
    {"create", &print_create},
    {"info", &print_info},
    {"list", &print_list},
    {"login", &print_login},
    {"logout", &print_logout},
    {"messages", &print_messsages},
    {"send", &print_receive_private_msg},
    {"subscribe", &print_subscribe},
    {"subscribed", &print_subscribed},
    {"unsubscribe", &print_unsubscribe},
    {"user", &print_user},
    {"users", &print_users},
    {"help", &print_help},
    {NULL, NULL}
};

#endif /* !MYTEAMS_CLI_H_ */
