/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** get the file next line
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

static char *read_file(int fd);
static char *too_much = NULL;

static char *check_line(int fd, char *buffer, int much_len)
{
    char *temp = too_much;
    int i = much_len;

    for (; buffer[i] != '\n' && buffer[i] != '\0' && i + 1 < READ_SIZE + much_len;
    i++);
    if (buffer[i] == '\n') {
        buffer[i] = '\0';
        too_much = my_strndup(buffer + i + 1, my_strlen(buffer + i + 1));
        free(temp);
    } else if (buffer[i] != '\0') {
        buffer[i + 1] = '\0';
        free(too_much);
        too_much = buffer;
        return read_file(fd);
    }
    return buffer;
}

static char *read_file(int fd)
{
    int much_len = my_strlen(too_much);
    char *buffer = malloc(sizeof(char) * (much_len + READ_SIZE + 1));
    int size = buffer != NULL ?
                        read(fd, buffer + much_len, READ_SIZE) : -1;

    if (buffer == NULL || size <= 0)
        return NULL;
    for (int k = 0; too_much != NULL && too_much[k] != '\0'; k++)
        buffer[k] = too_much[k];
    return check_line(fd, buffer, much_len);
}

char *get_next_line(int fd)
{
    int i = 0;
    char *result = NULL;
    char *temp = too_much;

    for (; too_much != NULL && too_much[i] != '\n' && too_much[i] != '\0'; i++);
    if (too_much != NULL && too_much[i] == '\n') {
        result = my_strndup(too_much, i + 1);
        result[i] = '\0';
        too_much = my_strndup(too_much + i + 1, my_strlen(too_much + i + 1));
        free(temp);
    }
    if (result != NULL)
        return result;
    return read_file(fd);
}