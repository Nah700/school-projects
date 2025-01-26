/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** teams
*/

#include "../../include/myteams_server.h"

void load_users(user_t **users, int socket, myteams_t *teams)
{
    FILE *file = fopen("server/database/users.db", "r");
    char line[256];
    char username[256];
    char uuid[37];
    user_t *new_user = NULL;

    if (file == NULL)
        return;
    while (fgets(line, sizeof(line), file))
        if (sscanf(line, "%255s %36s", username, uuid) == 2) {
            new_user = malloc(sizeof(user_t));
            new_user->username = strdup(username);
            new_user->uuid = strdup(uuid);
            new_user->password = NULL;
            new_user->is_connected = 0;
            new_user->next = NULL;
            add_user(users, new_user, socket, teams);
            server_event_user_loaded(new_user->uuid, new_user->username);
        }
    fclose(file);
}

myteams_t *init_myteams(int port)
{
    myteams_t *myteams = malloc(sizeof(myteams_t));

    myteams->users = NULL;
    load_users(&myteams->users, 0, myteams);
    myteams->teams = NULL;
    myteams->private_messages = NULL;
    myteams->server = init_server(port);
    return myteams;
}

void free_myteams(myteams_t *myteams)
{
    free_server(myteams->server);
    free_team(myteams->teams);
    free_users(myteams->users);
    free(myteams);
}

char *get_protocol_answer(int code)
{
    FILE *file = fopen("docs/protocol.txt", "r");
    char line[256];
    int line_code;

    if (file == NULL) {
        perror("Unable to open file");
        return NULL;
    }
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d", &line_code) == 1 && line_code == code) {
            fclose(file);
            line[strcspn(line, "\n")] = 0;
            return strdup(line);
        }
    }
    fclose(file);
    return NULL;
}
