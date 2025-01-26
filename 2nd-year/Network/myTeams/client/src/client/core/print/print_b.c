/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** print_b
*/


#include "../../../../include/myteams_cli.h"

void print_users(char **args)
{
    int code = 0;
    int len = get_tab_length(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (code == 995)
        client_print_users(args[2], args[3], atoi(args[4]));
}

void print_user(char **args)
{
    int code = 0;
    int len = get_tab_length(args);

    if (len < 1)
        return;
    code = atoi(args[0]);
    if (code == 403)
        client_error_unauthorized();
    if (len < 4)
        return;
    if (code == 701)
        client_error_unknown_user(args[2]);
    if (len < 5)
        return;
    if (code == 370)
        client_print_user(args[2], args[3], atoi(args[4]));
}

void print_messsages(char **args)
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
    if (code == 701)
        client_error_unknown_user(args[2]);
    if (len < 5)
        return;
    if (code == 502)
        client_private_message_print_messages(args[2],
            convert_to_time(args[3]), args[4]);
}
