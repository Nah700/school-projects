/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** thread
*/

#include "../../include/myteams_server.h"

thread_t *init_thread(char *name, char *description)
{
    thread_t *thread = malloc(sizeof(thread_t));

    thread->uuid = create_uuid();
    thread->description = strdup(description);
    thread->comments = NULL;
    thread->name = strdup(name);
    thread->timestamp = get_timestamp();
    thread->next = NULL;
    return thread;
}

void free_thread(thread_t *thread)
{
    free(thread->name);
    free(thread->description);
    free(thread);
}

void add_thread(channel_t *channel, thread_t *thread)
{
    thread_t *tmp;

    if (channel->threads == NULL) {
        channel->threads = thread;
        return;
    }
    tmp = channel->threads;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = thread;
}

thread_t *get_thread_by_uuid(channel_t *channel, char *uuid)
{
    thread_t *tmp = channel->threads;

    if (uuid == NULL)
        return NULL;
    while (tmp != NULL) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

thread_t *check_and_retrieve_thread(channel_t *channel, char *uuid_thread,
    int client_socket)
{
    thread_t *thread;

    if (!channel)
        return NULL;
    thread = get_thread_by_uuid(channel, uuid_thread);
    if (thread == NULL) {
        clean_answer(704, uuid_thread, client_socket, false);
        return NULL;
    }
    return thread;
}
