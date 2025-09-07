#ifndef PARSING_H
# define PARSING_H

#include <unistd.h> //write
#include "utils.h" //our tools ft_X
#include "cub3D.h"

//parsing_elements.c
int collect_elements(int fd_sd, t_settings *set);

//parsing_file.c
int open_and_parse_file(char *file, t_settings *set);

//parsing.c
int parsing(int argc, char *argv[], t_settings *set);

#endif