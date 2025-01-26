/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** myteams_server
*/

#ifndef MYTEAMS_SERVER_H_
    #define MYTEAMS_SERVER_H_

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <regex.h>
    #include <uuid/uuid.h>
    #include <signal.h>
    #include "../../libs/myteams/logging_server.h"
    #include "./myteams_struct.h"
    #include "../../commons/utils.h"

int main(int ac, char **av);
int check_args(int ac, char **av);
server_t *init_server(int port);
void free_server(server_t *server);
int my_teams_server(int port);
void create_new_client(server_t *server, int client_socket);
int get_max_fd(client_t *clients);
void handle_command(char *command, myteams_t *teams, int client_socket);
myteams_t *init_myteams(int port);
void free_myteams(myteams_t *myteams);
void remove_client(client_t **clients, int socket);
client_t *get_client_by_socket(client_t **clients, int socket);
void list(myteams_t *myteams, int client_socket, char **args);
void add_team(myteams_t *teams, team_t *team);
void free_team(team_t *team);
team_t *init_team(char *name, char *description);
void create(myteams_t *myteams, int client_socket, char **args);
void info(myteams_t *myteams, int client_socket, char **args);
char *get_protocol_answer(int code);
int is_user_logged(myteams_t *teams, int client_socket);
int get_len(char **tab);
void free_users(user_t *users);
char *create_uuid(void);
void check_user(user_t *client, char *username);
char *get_uuid_by_name(myteams_t *teams, int socket);
char *get_username_by_uuid(myteams_t *teams, char *uuid);
void use(myteams_t *teams, int socket, char **args);
team_t *get_team_by_uuid(myteams_t *teams, char *uuid);
channel_t *init_channel(char *name, char *description);
void add_channel(team_t *team, channel_t *channel);
void free_channel(channel_t *channel);
channel_t *get_channel_by_uuid(team_t *team, char *uuid);
thread_t *init_thread(char *name, char *description);
void free_thread(thread_t *thread);
void add_thread(channel_t *channel, thread_t *thread);
thread_t *get_thread_by_uuid(channel_t *channel, char *uuid);
comment_t *init_comment(char *body);
void free_comment(comment_t *comment);
void add_comment(thread_t *thread, comment_t *comment);
comment_t *get_comment_by_uuid(thread_t *thread, char *uuid);
void add_user(user_t **users, user_t *user, int socket, myteams_t *teams);
void add_msg(private_message_t **msgs, private_message_t *msg);
int check_file(FILE *fd);
char *realloc_strcat(char *dest, char *src);
void free_tab(char **tab);
unsigned int load_user_register_chans(char *path, team_t *teams);
unsigned int save_user_register_chans(char *path, team_t *teams);
unsigned int save_private_msgs(char *path,
    private_message_t *private_msgs);
unsigned int load_private_msgs(char *path,
    private_message_t **private_msgs);
void clean_answer(int code, char *info, int socket, bool in_loop);
void subscribe(myteams_t *teams, int client_socket, char **args);
void subscribed(myteams_t *teams, int client_socket, char **args);
void unsubscribe(myteams_t *teams, int client_socket, char **args);
int is_user_in_team(team_t *team, myteams_t *teams, int client_socket);
void send_message(myteams_t *teams, int client_socket, char **args);
char *get_name_from_socket(myteams_t *teams, int socket);
char *create_uuid(void);
void help(myteams_t *teams, int client_socket, char **args);
void login(myteams_t *teams, int cli_s, char **args);
void logout(myteams_t *teams, int client_sock, char **args);
void users(myteams_t *teams, int client_socket, char **args);
void user(myteams_t *teams, int client_socket, char **args);
void messages(myteams_t *teams, int client_socket, char **args);
team_t *check_and_retrieve_team(myteams_t *teams, char *uuid_team,
    int client_socket);
channel_t *check_and_retrieve_channel(myteams_t *teams, team_t *team,
    char *uuid_channel, int client_socket);
thread_t *check_and_retrieve_thread(channel_t *channel, char *uuid_thread,
    int client_socket);
bool team_exist(myteams_t *teams, char *name);
bool channel_exist(team_t *team, char *name);
bool thread_exist(channel_t *channel, char *name);
char *get_timestamp(void);
user_t *get_user_by_uuid(myteams_t *teams, char *uuid);
void signal_handler(int signum);
myteams_t *global_server(myteams_t *server, globalmod_t mode);
user_register_channel_t *init_team_user(user_t *user);
void disconnect_user_by_uuid(myteams_t *teams, char *uuid, int socket);
void free_client(server_t *server);
void print_create_reply(thread_t *thread, comment_t *new_comment,
    client_t *client, myteams_t *teams);

static const struct {
    char *command;
    void (*function)(myteams_t *teams, int client_socket, char **args);
} handlers[] = {
    {"/login", &login},
    {"/logout", &logout},
    {"/users", &users},
    {"/user", &user},
    {"/send", &send_message},
    {"/messages", &messages},
    {"/subscribe", &subscribe},
    {"/subscribed", &subscribed},
    {"/unsubscribe", &unsubscribe},
    {"/use", &use},
    {"/create", &create},
    {"/list", &list},
    {"/info", &info},
    {"/help", &help},
    {NULL, NULL}
};

#endif /* !MYTEAMS_SERVER_H_ */
