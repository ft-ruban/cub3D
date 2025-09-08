#ifndef PARSING_H
# define PARSING_H

#include <unistd.h> //write
#include "utils.h" //our tools ft_X
#include "cub3D.h"

//parsing_elements.c
int collect_elements(int fd_sd, t_settings *set);

//parsing_file.c
int open_and_parse_file(char *file, t_settings *set);

//parsing_rgb.c
int rgb_thing(int fd_sd, t_settings *set, char first_letter, char second_letter);

//parsing_texture.c
int is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter);

//parsing.c
int parsing(int argc, char *argv[], t_settings *set);

#endif