#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h> //bool exit_loop
#include <unistd.h> //write
#include "utils.h" //our tools ft_X
#include "cub3D.h"

#define OPEN_FAILED -1
#define FLOOR 0
#define CELL 1

//check_the_map.c
int enclosed_check(char **map);
int element_check(char **map);
int map_nbr_check(t_settings *set, int fd);

//get_the_map.c
int cpy_the_map(t_settings *set, char **map, int height, int fd);
int read_until_map_start(char *file, t_settings *set, int fd);
int malloc_map(t_settings *set, int w, int h, char ***map);
int find_map_size(t_settings *set, int *map_width_max, int *map_height, int fd);

//parsing_elements.c
int collect_elements(int fd_sd, t_settings *set);

//parsing_file.c
int open_file_collect_elements(char *file, t_settings *set, int *fd);

//parsing_map.c
int get_and_check_map(char *file, t_settings *set, int fd);

//parsing_rgb.c
int rgb_thing(int fd_sd, t_settings *set, char first_letter,  bool exit_loop);

//parsing_texture.c
int is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter);

//parsing.c
int parsing(int argc, char *argv[], t_settings *set);

#endif