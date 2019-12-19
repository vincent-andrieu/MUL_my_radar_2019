/*
** EPITECH PROJECT, 2019
** my_radar
** File description:
** my_radar usage
*/

#include "my.h"

int usage(int exit_value, char *binary_name)
{
    my_putstr("Air traffic simulation panel\n\nUSAGE\n\t");
    my_putstr(binary_name);
    my_putstr(" [OPTIONS] path_to_string\n\tpath_to_string\tThe path to the "
            "script file.\n\nOPTIONS\n\t-h\tprint the usage and quit.\n\nUSER "
            "INTERACTIONS\n\t'L' key\tenable/disable hitboxes and areas.\n"
            "\t'S' key\tenable/disable sprites.\n");
    return exit_value;
}