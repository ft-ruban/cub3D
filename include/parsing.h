#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>
#include "utils.h"

#define OPEN_FAILED -1
#define FLOOR 0
#define CEIL 1
#define MAP_FOLDER_PATH "scene_descriptions/"
#define FILE_ERR_1 "parsing_rgb.c:88 "
#define FILE_ERR_2 "parsing_texture.c:56 "
#define FILE_ERR_3 "parsing_texture.c:62 "
#define FILE_ERR_4 "parsing_texture.c:68 "
#define FILE_ERR_5 "parsing_texture.c:74 "
#define	ELEMENT_NBR 6
#define READ_OR_MALLOC_ERR -1


//parsing_collect_elements.c
bool	prepare_collect_elements(char *file, t_settings *set, int *fd);

//parsing_rgb.c
bool is_rgb_valid(int fd_sd, t_settings *set, char first_letter,  bool received_rgb_completed);

//parsing_texture.c
bool is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter);

//check_the_map.c
int		enclosed_check(t_settings *set, char **map, char c);
int		element_check(t_settings *set, char **map);
int		map_nbr_check(t_settings *set, int fd);

//get_the_map_utils.c
bool	is_all_map_copied(t_settings *set, int line_index, int map_height, int fd);
bool	find_map_start(t_settings *set, int fd);
void	update_map_size(int *map_width, int *map_width_max, int *map_height);

//get_the_map.c
int 	get_the_map(t_settings *set, char *file, int fd);

//parsing_map.c
int		get_and_check_map(char *file, t_settings *set, int fd);

//parsing.c
int		parsing(int argc, char *argv[], t_settings *set);

#endif