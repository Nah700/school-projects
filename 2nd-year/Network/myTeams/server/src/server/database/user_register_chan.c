/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** user_register_chan
*/

#include "../../../include/myteams_server.h"

static void add_user_register_chans(user_register_channel_t **list,
    user_register_channel_t *new)
{
    user_register_channel_t *tmp = *list;

    if (!tmp) {
        *list = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

int process_line(char *line, user_register_channel_t **new_ptr)
{
    char **tab = str_to_word_array(line, ';');

    if (!tab)
        return -1;
    *new_ptr = malloc(sizeof(user_register_channel_t));
    if (!*new_ptr) {
        free_tab(tab);
        return -1;
    }
    (*new_ptr)->uuid = !strcmp(tab[1], "NULL") ? NULL : strdup(tab[1]);
    (*new_ptr)->name = !strcmp(tab[2], "NULL") ? NULL : strdup(tab[2]);
    (*new_ptr)->next = NULL;
    free_tab(tab);
    return 0;
}

int process_buffer(char *buffer, user_register_channel_t **new, team_t *teams)
{
    team_t *team = teams;
    int ret = process_line(buffer, new);

    if (ret == -1)
        return ret;
    while (team) {
        if (!strcmp(buffer, team->uuid)) {
            add_user_register_chans(&team->users, *new);
            break;
        }
        team = team->next;
    }
    return 0;
}

unsigned int load_user_register_chans(char *path, team_t *teams)
{
    FILE *fd = fopen(path, "r");
    size_t len = 0;
    char *buffer = NULL;
    user_register_channel_t *new;
    int ret = 0;

    if (!fd)
        return 84;
    while (getline(&buffer, &len, fd) != -1) {
        buffer[strlen(buffer) - 1] = '\0';
        ret = process_buffer(buffer, &new, teams);
        if (ret == -1)
            continue;
    }
    free(buffer);
    fclose(fd);
    return 0;
}

unsigned int save_user_register_chans(char *path, team_t *teams)
{
    user_register_channel_t *tmp;
    FILE *fd = fopen(path, "w+");

    if (!fd)
        return 84;
    while (teams) {
        tmp = teams->users;
        while (tmp) {
            fprintf(fd, "%s;%s;%s\n",
                teams->uuid ? teams->uuid : "NULL",
                tmp->uuid ? tmp->uuid : "NULL",
                tmp->name ? tmp->name : "NULL"
            );
            tmp = tmp->next;
        }
        teams = teams->next;
    }
    fclose(fd);
    return 0;
}
