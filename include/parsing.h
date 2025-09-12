#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h> //bool exit_loop
#include <unistd.h> //write
#include "utils.h" //our tools ft_X
#include "cub3D.h"

#define OPEN_FAILED -1

//parsing_elements.c
int collect_elements(char *file, int fd_sd, t_settings *set);
int collect_check_map(char *file, t_settings *set, int fd);

//parsing_file.c
int open_file_collect_elements(char *file, t_settings *set);

//parsing_rgb.c
int rgb_thing(int fd_sd, t_settings *set, char first_letter,  bool exit_loop);

//parsing_texture.c
int is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter);

//parsing.c
int parsing(int argc, char *argv[], t_settings *set);

#endif