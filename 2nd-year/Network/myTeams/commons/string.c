/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** string
*/

#include <stdbool.h>
#include "utils.h"

static int handle_word_counting(int *count, int *in_word)
{
    if (!(*in_word)) {
        *in_word = 1;
        (*count)++;
    }
    return *count;
}

static int count_nb_words(char *str, char delimiter)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delimiter) {
            in_word = 0;
        } else {
            count = handle_word_counting(&count, &in_word);
        }
    }
    return count;
}

char **str_to_word_array(char *str, char delimiter)
{
    char *str_copy = strdup(str);
    int count = count_nb_words(str_copy, delimiter);
    char **words = malloc((count + 1) * sizeof(char *));
    char delim[2] = {delimiter, '\0'};
    char *token;
    int i = 0;

    token = strtok(str_copy, delim);
    while (token != NULL) {
        words[i] = strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    words[count] = NULL;
    if (words[count - 1][0] == '\n' || words[count - 1][0] == '\r')
        words[count - 1] = NULL;
    free(str_copy);
    return words;
}

static void add_pts_komma(char *str)
{
    int in_quotes = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '"')
            in_quotes = !in_quotes;
        if ((str[i] == ' ' || str[i] == '\t') && !in_quotes)
            str[i] = ';';
    }
    return;
}

static int count_quotes(char *str)
{
    int quote_count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == '"')
            quote_count++;
    return quote_count;
}

static void inc_and_assign(char *output, char *input)
{
    *output = ';';
    output++;
    input++;
}

char *sanitize_message(char *str)
{
    int in_quotes = 0;
    char *output = str;
    char *input = str;

    if (count_quotes(str) == 1)
        in_quotes = 1;
    while (*input) {
        if (*input == '"')
            in_quotes = !in_quotes;
        if ((*input == ' ' || *input == '\t') && !in_quotes) {
            inc_and_assign(output, input);
            continue;
        }
        *output = *input;
        output++;
        input++;
    }
    *output = '\0';
    add_pts_komma(str);
    return str;
}

void print_arr(char **arr)
{
    for (int i = 0; arr[i]; i++) {
        write(STDOUT_FILENO, arr[i], strlen(arr[i]));
        write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
}
