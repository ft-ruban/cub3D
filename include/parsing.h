#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h> //bool exit_loop
#include <unistd.h> //write
#include "utils.h" //our tools ft_X
#include "cub3D.h"

#define OPEN_FAILED -1
#define FLOOR 0
#define CEIL 1
#define MAP_FOLDER_PATH "scene_descriptions/"

//parsing_collect_elements.c
bool	prepare_collect_elements(char *file, t_settings *set, int *fd);

//parsing_rgb.c
bool is_rgb_valid(int fd_sd, t_settings *set, char first_letter,  bool received_rgb_completed);

//parsing_texture.c
bool is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter);

//parsing.c
int parsing(int argc, char *argv[], t_settings *set);

#endif