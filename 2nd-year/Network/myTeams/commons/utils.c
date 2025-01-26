/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** utils
*/

#include "utils.h"

size_t get_len_crlf(char *buff)
{
    size_t i = 0;

    while (buff[i] != '\0' && buff[i + 1] != '\0') {
        if (buff[i] == '\r' && buff[i + 1] == '\n') {
            break;
        }
        ++i;
    }
    return i;
}

char *remove_crlf(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\r' && str[i + 1] == '\n') {
            str[i] = '\0';
            str[i + 1] = '\0';
        }
    }
    return str;
}

int get_tab_length(char **tab)
{
    int i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}

char *format_string(char *str)
{
    char *str_copy = malloc(sizeof(char) * strlen(str) + 3);
    int len = strlen(str);

    strcpy(str_copy, str);
    str_copy[len] = '\r';
    str_copy[len + 1] = '\n';
    str_copy[len + 2] = '\0';
    return str_copy;
}

void remove_formatting(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\r') {
            str[i] = '\0';
            str[i + 1] = '\0';
        }
    }
}
