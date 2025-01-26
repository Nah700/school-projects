/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** print_a
*/

#include "../../../../include/myteams_cli.h"

void print_login(char **args)
{
    int code = 0;

    if (tab_len(args) < 1)
        return;
    code = atoi(args[0]);
    if (code == 250)
        client_event_logged_in(args[2], args[3]);
}

void print_logout(char **args)
{
    int code = 0;

    if (tab_len(args) < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (code == 300)
        client_event_logged_out(args[2], args[3]);
}

static void print_sub_create_sec(char **args, int code)
{
    if (code == 949)
        client_print_thread_created(args[2], args[3],
            convert_to_time(args[4]), args[5], args[6]);
    if (code == 953)
        client_event_thread_created(args[2], args[3], convert_to_time(args[4]),
            args[5], args[6]);
}

static void print_sub_create(char **args, int code, int len)
{
    if (len < 5)
        return;
    if (code == 947)
        client_print_team_created(args[2], args[3], args[4]);
    if (code == 948)
        client_print_channel_created(args[2], args[3], args[4]);
    if (code == 951)
        client_event_team_created(args[2], args[3], args[4]);
    if (code == 952)
        client_event_channel_created(args[2], args[3], args[4]);
    if (len < 6)
        return;
    if (code == 950)
        client_print_reply_created(args[2], args[3],
            convert_to_time(args[4]), args[5]);
    if (code == 954)
        client_event_thread_reply_received(args[2], args[3], args[4], args[5]);
    if (len < 7)
        return;
    print_sub_create_sec(args, code);
}

void print_create(char **args)
{
    int code = 0;
    int len = tab_len(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (code == 705)
        client_error_already_exist();
    if (len < 3)
        return;
    if (code == 702)
        client_error_unknown_team(args[2]);
    if (code == 703)
        client_error_unknown_channel(args[2]);
    if (code == 704)
        client_error_unknown_thread(args[2]);
    print_sub_create(args, code, len);
}

static void print_sub_info(char **args, int code, int len)
{
    if (code == 704)
        client_error_unknown_thread(args[2]);
    if (len < 5)
        return;
    if (code == 370)
        client_print_user(args[2], args[3], atoi(args[4]));
    if (code == 1050)
        client_print_team(args[2], args[3], args[4]);
    if (code == 1051)
        client_print_channel(args[2], args[3], args[4]);
    if (len < 7)
        return;
    if (code == 1052)
        client_print_thread(args[2], args[3],
            convert_to_time(args[4]), args[5], args[6]);
}

void print_info(char **args)
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
    if (code == 702)
        client_error_unknown_team(args[2]);
    if (code == 703)
        client_error_unknown_channel(args[2]);
    print_sub_info(args, code, len);
}

static void print_sub_list(char **args, int code, int len)
{
    if (len < 5)
        return;
    if (code == 995)
        client_print_users(args[2], args[3], convert_to_time(args[4]));
    if (code == 997)
        client_print_teams(args[2], args[3], args[4]);
    if (code == 998)
        client_team_print_channels(args[2], args[3], args[4]);
    if (len < 6)
        return;
    if (code == 1000)
        client_thread_print_replies(args[2], args[3],
            convert_to_time(args[4]), args[5]);
    if (len < 7)
        return;
    if (code == 999)
        client_channel_print_threads(args[2], args[3],
            convert_to_time(args[4]), args[5], args[6]);
}

void print_list(char **args)
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
    if (code == 702)
        client_error_unknown_team(args[2]);
    if (code == 703)
        client_error_unknown_channel(args[2]);
    if (code == 704)
        client_error_unknown_thread(args[2]);
    print_sub_list(args, code, len);
}
