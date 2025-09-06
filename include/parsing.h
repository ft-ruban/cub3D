#ifndef PARSING_H
# define PARSING_H

#include <unistd.h> //write
#include "utils.h" //our tools ft_X
#include "cub3D.h"


//parsing_file.c
int open_and_parse_file(char *file);

//parsing.c
int parsing(int argc, char *argv[]);

#endif