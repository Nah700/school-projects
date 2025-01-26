/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** utils
*/

#include "../../../include/myteams_cli.h"

client_t *global_client(client_t *client, globalmod_t mode)
{
    static client_t *global_client = NULL;

    if (mode == SETTER) {
        global_client = client;
        return NULL;
    } else
        return global_client;
}

void signal_handler(int signum)
{
    if (signum == SIGINT || signum == 0xb) {
        printf("\nKeyboardInterrupt: Closing connection...\n");
        close(global_client(NULL, GETTER)->sock);
        exit(0);
    }
}

time_t convert_to_time(char *time_str)
{
    struct tm tm;

    memset(&tm, 0, sizeof(struct tm));
    strptime(time_str, "%Y-%m-%d %H:%M:%S", &tm);
    return mktime(&tm);
}

size_t tab_len(char **tab)
{
    size_t i = 0;

    for (; tab[i]; i++);
    return i;
}
