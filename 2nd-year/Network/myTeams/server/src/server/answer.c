/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** answer
*/

#include "../../include/myteams_server.h"

void clean_answer(int code, char *info, int socket, bool in_loop)
{
    char *code_str = get_protocol_answer(code);
    char *answer = malloc(sizeof(char) * (strlen(info)
    + strlen(code_str) + 1));

    strcpy(answer, code_str);
    answer[strlen(code_str)] = '\0';
    strcat(answer, info);
    if (in_loop == false)
        dprintf(socket, "%s", format_string(answer));
    else
        dprintf(socket, "%s\n", answer);
}
