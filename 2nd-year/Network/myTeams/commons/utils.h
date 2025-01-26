/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

typedef enum {
    SETTER = 0,
    GETTER
} globalmod_t;

void remove_formatting(char *str);
char *format_string(char *str);
int get_tab_length(char **tab);
char *remove_crlf(char *str);
size_t get_len_crlf(char *buff);
char **str_to_word_array(char *str, char delimiter);
void print_arr(char **arr);

#endif /* !UTILS_H_ */
