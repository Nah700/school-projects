/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** private_message
*/

#include "../../../include/myteams_server.h"

static private_message_t *create_private_message(char **tab)
{
    private_message_t *new = malloc(sizeof(private_message_t));

    if (!new)
        return NULL;
    new->sender_uuid = !strcmp(tab[0], "NULL") ? NULL : strdup(tab[0]);
    new->receiver_uuid = !strcmp(tab[1], "NULL") ? NULL : strdup(tab[1]);
    new->timestamp = !strcmp(tab[2], "NULL") ? NULL : strdup(tab[2]);
    new->message = NULL;
    new->next = NULL;
    return new;
}

static private_message_t *process_line(char *buffer)
{
    private_message_t *new;
    char **tab;

    tab = str_to_word_array(buffer, ';');
    if (!tab)
        return NULL;
    new = create_private_message(tab);
    if (!new) {
        free_tab(tab);
        return NULL;
    }
    for (int i = 3; tab[i]; i++) {
        if (i == 3 && !strcmp(tab[i], "NULL"))
            break;
        new->message = !new->message ? strdup(tab[i])
            : realloc_strcat(new->message, tab[i]);
    }
    free_tab(tab);
    return new;
}

unsigned int load_private_msgs(char *path,
    private_message_t **private_msgs)
{
    size_t len = 0;
    char *buffer = NULL;
    private_message_t *new;
    FILE *fd = fopen(path, "r");
    int check = check_file(fd);

    if (check)
        return check;
    while (getline(&buffer, &len, fd) != -1) {
        buffer[strlen(buffer) - 1] = '\0';
        new = process_line(buffer);
        if (!new) {
            free(buffer);
            return 84;
        }
        add_msg(private_msgs, new);
    }
    free(buffer);
    fclose(fd);
    return 0;
}

unsigned int save_private_msgs(char *path,
    private_message_t *private_msgs)
{
    private_message_t *tmp = private_msgs;
    FILE *fd = fopen(path, "w+");

    if (!fd)
        return 84;
    while (tmp) {
        fprintf(fd, "%s;%s;%s;%s\n",
            tmp->sender_uuid ? tmp->sender_uuid : "NULL",
            tmp->receiver_uuid ? tmp->receiver_uuid : "NULL",
            tmp->timestamp ? tmp->timestamp : "NULL",
            tmp->message ? tmp->message : "NULL"
        );
        tmp = tmp->next;
    }
    fclose(fd);
    return 0;
}
