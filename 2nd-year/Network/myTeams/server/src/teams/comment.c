/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** comment
*/

#include "../../include/myteams_server.h"

comment_t *init_comment(char *body)
{
    comment_t *comment = malloc(sizeof(comment_t));

    comment->uuid = create_uuid();
    comment->message = strdup(body);
    comment->timestamp = get_timestamp();
    comment->next = NULL;
    return comment;
}

void free_comment(comment_t *comment)
{
    free(comment->message);
    free(comment);
}

void add_comment(thread_t *thread, comment_t *comment)
{
    comment_t *tmp;

    if (thread->comments == NULL) {
        thread->comments = comment;
        return;
    }
    tmp = thread->comments;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = comment;
}

comment_t *get_comment_by_uuid(thread_t *thread, char *uuid)
{
    comment_t *tmp = thread->comments;

    if (uuid == NULL)
        return NULL;
    while (tmp != NULL) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
