/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** print_c
*/

#include "../../../../include/myteams_cli.h"

void print_subscribed(char **args)
{
    int code = 0;
    int len = get_tab_length(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (len < 3)
        return;
    if (code == 702)
        client_error_unknown_team(args[2]);
    if (len < 5)
        return;
    if (code == 997)
        client_print_teams(args[2], args[3], args[4]);
    if (code == 995)
        client_print_users(args[2], args[3], atoi(args[4]));
}

void print_unsubscribe(char **args)
{
    int code = 0;
    int len = get_tab_length(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (len < 3)
        return;
    if (code == 702)
        client_error_unknown_team(args[2]);
    if (len < 4)
        return;
    if (code == 650)
        client_print_unsubscribed(args[2], args[3]);
}

void print_subscribe(char **args)
{
    int code = 0;
    int len = get_tab_length(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (code == 702)
        client_error_unknown_team(args[2]);
    if (len < 4)
        return;
    if (code == 600)
        client_print_subscribed(args[2], args[3]);
}

void print_receive_private_msg(char **args)
{
    int code = 0;
    int len = tab_len(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (len < 3)
        return;
    if (code == 701)
        client_error_unknown_user(args[2]);
    if (len < 4)
        return;
    if (code == 501)
        client_event_private_message_received(args[2], args[3]);
}

void print_help(char **args)
{
    int code = 0;
    int len = get_tab_length(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
}
