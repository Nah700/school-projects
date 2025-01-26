/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** manageDatabase
*/

#include "../../../include/myteams_server.h"

void add_user(user_t **users, user_t *user, int socket, myteams_t *teams)
{
    user_t *current;

    if (user->username == NULL) {
        get_user_by_uuid(teams, get_uuid_by_name(teams, socket))->is_connected
            = 1;
        return;
    }
    if (*users == NULL) {
        *users = user;
    } else {
        current = *users;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = user;
    }
}

static int check_username(regmatch_t *pmatch, char *line, char *username)
{
    int len = pmatch[1].rm_eo - pmatch[1].rm_so;

    if (strncmp(username, line + pmatch[1].rm_so, len) == 0 &&
        (int)strlen(username) == len) {
        return 1;
    }
    return 0;
}

static int process_line(regex_t *regex, regmatch_t *pmatch, char *line,
    char *username)
{
    if (!regexec(regex, line, 3, pmatch, 0)) {
        return check_username(pmatch, line, username);
    }
    return 0;
}

static void assign_new_user(user_t *client, char *username)
{
    FILE *file = fopen("server/database/users.db", "a+");
    char *uuid = create_uuid();

    if (file == NULL) {
        perror("Unable to open file");
        return;
    }
    fprintf(file, "%s %s\n", username, uuid);
    client->username = strdup(username);
    client->uuid = uuid;
    client->next = NULL;
    client->password = NULL;
    client->is_connected = 1;
    server_event_user_created(uuid, username);
    fclose(file);
}

static void assign_existing_user(user_t *client, char *username, char *line)
{
    client->username = NULL;
    client->uuid = (line + strlen(username) + 1);
    client->next = NULL;
    client->password = NULL;
    client->is_connected = 1;
}

static int process_lines(regex_t *regex, regmatch_t *pmatch, char **line,
    char *username)
{
    FILE *file = fopen("server/database/users.db", "a+");
    int found = 0;
    ssize_t read;
    size_t size = 0;

    if (file == NULL)
        return found;
    *line = NULL;
    while (read != -1) {
        read = getline(line, &size, file);
        if (read > 0)
            (*line)[read - 1] = '\0';
        found = process_line(regex, pmatch, *line, username);
        if (found)
            break;
        *line = NULL;
    }
    fclose(file);
    return found;
}

static int process_file(regmatch_t *pmatch, char **line,
    char *username)
{
    int found = 0;
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^([a-zA-Z0-9_]+) ([a-f0-9\\-]+)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 84;
    }
    found = process_lines(&regex, pmatch, line, username);
    regfree(&regex);
    return found;
}

void check_user(user_t *client, char *username)
{
    char *line = malloc(sizeof(char) * 257);
    regmatch_t pmatch[3];
    int result = 0;

    result = process_file(pmatch, &line, username);
    if (result)
        assign_existing_user(client, username, line);
    else if (result == 84)
        return;
    else
        assign_new_user(client, username);
    free(line);
}

char *get_uuid_by_name(myteams_t *teams, int socket)
{
    client_t *tmp = get_client_by_socket(&teams->server->clients, socket);
    user_t *current = teams->users;

    while (current != NULL) {
        if (strcmp(current->username, tmp->name) == 0)
            return current->uuid;
        current = current->next;
    }
    return NULL;
}

char *get_username_by_uuid(myteams_t *teams, char *uuid)
{
    for (user_t *current = teams->users; current != NULL;
        current = current->next) {
        if (strcmp(current->uuid, uuid) == 0)
            return current->username;
    }
    return NULL;
}
