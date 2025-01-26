/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-julien.dufaur
** File description:
** utils
*/

#include "../../../include/myteams_server.h"

char *realloc_strcat(char *dest, char *src)
{
    char *new = malloc(strlen(dest) + strlen(src) + 1);

    if (!new)
        return NULL;
    strcpy(new, dest);
    strcat(new, src);
    free(dest);
    return new;
}

int check_file(FILE *fd)
{
    if (!fd)
        return 84;
    if (fseek(fd, 0, SEEK_END) == -1)
        return 84;
    if (ftell(fd) == 0) {
        fclose(fd);
        return 1;
    }
    rewind(fd);
    return 0;
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

char *create_uuid(void)
{
    uuid_t binuuid;
    char uuid[37];

    uuid_generate_random(binuuid);
    uuid_unparse_lower(binuuid, uuid);
    return strdup(uuid);
}
