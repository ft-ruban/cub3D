#ifndef PARSING_H
# define PARSING_H

# include "utils.h"
# include <stdbool.h>

typedef struct s_settings	t_settings; //declaration anticipe

# define OPEN_FAILED -1
# define MALLOC_ERR -1
# define READ_FAILED -1
# define END_OF_FILE 0
# define READ_OR_MALLOC_ERR -1
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

//map_check.c
bool map_check(t_settings *set, int fd);

//map_collect.c
bool 	map_collect(t_settings *set, char *file, int fd);

//parsing_map.c
bool		get_and_check_map(char *file, t_settings *set, int fd);

// parsing.c
int		parsing(int argc, char *argv[], t_settings *set);

#endif