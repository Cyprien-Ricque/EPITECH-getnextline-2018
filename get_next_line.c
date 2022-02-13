/*
** EPITECH PROJECT, 2018
** file_read
** File description:
** file_read
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_strlen(char *str, char c)
{
    int i = 0;

    while (str[i] != c && str[i] != '\0')
        i++;
    return (i);
}

char *re_alloc(char *str, int size)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(str, '\0') + size));
    if (new_str ==  NULL)
        return (NULL);
    int i = 0;

    while (str[i] != '\0') {
        new_str[i] = str[i];
        ++i;
    }
    new_str[i] = '\0';
    free(str);
    return (new_str);
}

void my_strncat(char *dest, char *src, int nb)
{
    int i = my_strlen(dest, '\0');

    for (int j = 0; j < nb; j++) {
        dest[i] = src[j];
        i++;
    }
    dest[i] = '\0';
    for (int j = 0; src[j] != '\0'; ++j) {
        if (src[j + nb + 1])
            src[j] = src[j + nb + 1];
        else
            src[j] = 0;
    }
}

char *get_next_line(int fd)
{
    static char buffer[READ_SIZE + 1] = "";
    int al_read = READ_SIZE;
    char *str = malloc(sizeof(char) * (READ_SIZE * 2));

    if (str == NULL)
        return (NULL);
    str[0] = 0;
    while (my_strlen(buffer, '\n') == my_strlen(buffer, '\0') &&
        (al_read > 0)) {
        al_read = -1;
        str = re_alloc(str, READ_SIZE * 2);
        my_strncat(str, buffer, READ_SIZE);
        al_read = read(fd, buffer, READ_SIZE);
    }
    my_strncat(str, buffer, my_strlen(buffer, '\n'));
    if (my_strlen(str, '\0') || my_strlen(buffer, '\0') ||
        my_strlen(str, '\0') < al_read) {
        return (re_alloc(str, 1));
    }
    return (NULL);
}