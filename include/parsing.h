#ifndef PARSING_H
# define PARSING_H

# include "utils.h"
# include <stdbool.h>

typedef struct s_settings	t_settings; //declaration anticipe

# define OPEN_FAILED -1
# define READ_FAILED -1
# define TYPE_RGB 0
# define TYPE_TEXTURE 1
# define TYPE_EMPTY_LINE 2
# define INVALID -42
# define CEIL 1
# define FLOOR 0
# define MAP_FOLDER_PATH "scene_descriptions/"
# define FILE_ERR_1 "parsing_rgb.c:88 "
# define FILE_ERR_2 "parsing_texture.c:56 "
# define FILE_ERR_3 "parsing_texture.c:62 "
# define FILE_ERR_4 "parsing_texture.c:68 "
# define FILE_ERR_5 "parsing_texture.c:74 "

// element_collect_parsing.c
bool	prepare_collect_elements(char *cub_file, t_settings *set, int *fd_sd,
			char **read_buff);

// element_collect_utils.c
bool	an_element_is_missing(t_settings *set);
int		which_element_type(char letter, t_settings *set);
int		open_sd_file_give_fd(char *file);

// element_rgb_parsing.c
bool	is_rgb_valid(int fd_sd, t_settings *set, char first_letter,
			bool received_rgb_completed);

// element_texture_parsing.c
bool	is_texture_valid(int fd_sd, t_settings *set, char first_letter,
			char second_letter);

// check_the_map.c
int		enclosed_check(t_settings *set, char **map, char c);
int		element_check(t_settings *set, char **map);
int		map_nbr_check(t_settings *set, int fd);

// find_map_size_utils.c
int		find_map_start(t_settings *set, int fd);
void	update_width_height(int *map_width, int *map_width_max,
			int *map_height);

// get_the_map.c
int		cpy_the_map(t_settings *set, char **map, int height, int fd);
int		read_until_map_start(char *file, t_settings *set, int fd);
int		malloc_map(t_settings *set, int w, int h, char ***map);
int		find_map_size(t_settings *set, int *map_width_max, int *map_height,
			int fd);

// parsing_map.c
int		get_and_check_map(char *file, t_settings *set, int fd);

// parsing.c
int		parsing(int argc, char *argv[], t_settings *set);

#endif