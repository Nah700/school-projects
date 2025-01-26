/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** myteams
*/

#ifndef MYTEAMS_H_
    #define MYTEAMS_H_

typedef struct user_s {
    char *uuid;
    char *username;
    char *password;
    bool is_connected;
    struct user_s *next;
} user_t;

typedef struct private_message_s {
    char *uuid;
    char *sender_uuid;
    char *receiver_uuid;
    char *timestamp;
    char *message;
    struct private_message_s *next;
} private_message_t;

typedef struct user_register_channel_s {
    char *uuid;
    char *name;
    bool is_connected;
    struct user_register_channel_s *next;
} user_register_channel_t;

typedef struct comment_s {
    char *uuid;
    char *message;
    char *timestamp;
    struct comment_s *next;
} comment_t;

typedef struct thread_s {
    char *uuid;
    char *name;
    char *description;
    char *timestamp;
    struct comment_s *comments;
    struct thread_s *next;
} thread_t;

typedef struct channel_s {
    char *uuid;
    char *name;
    char *description;
    struct thread_s *threads;
    struct channel_s *next;
} channel_t;

typedef struct team_s {
    char *uuid;
    char *name;
    char *description;
    struct user_register_channel_s *users;
    struct channel_s *channels;
    struct team_s *next;
} team_t;

typedef struct client_s {
    int socket;
    char *name;
    bool connected;
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
    struct client_s *next;
} client_t;

typedef struct server_s {
    int port;
    int socket;
    int address_length;
    int max_fd;
    struct sockaddr_in address;
    fd_set read_fds;
    fd_set write_fds;
    client_t *clients;
    bool running;
} server_t;

typedef struct myteams_s {
    struct user_s *users;
    struct private_message_s *private_messages;
    struct team_s *teams;
    struct server_s *server;
} myteams_t;

#endif /* !MYTEAMS_H_ */
