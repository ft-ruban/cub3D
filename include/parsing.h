/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:42:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 20:43:56 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3D.h"
# include <stdbool.h>

typedef struct s_cub3d	t_cub3d;
typedef struct s_map	t_map;

# define NONE_ASSIGNED -1
# define OPEN_FAILED -1
# define MALLOC_ERR -1
# define READ_FAILED -1
# define END_OF_FILE 0
# define READ_OR_MALLOC_ERR -1
# define TYPE_RGB 0
# define TYPE_TEXTURE 1
# define TYPE_EMPTY_LINE 2
# define INVALID -42
# define ELEMENT_NBR 6
# define CEIL 1
# define FLOOR 0
# define MAP_FOLDER_PATH "scene_descriptions/"

# define FILE_ERR_2 "element_texture_parsing.c:107  "
# define FILE_ERR_3 "element_texture_parsing.c:57 "
# define FILE_ERR_4 "element_texture_parsing.c:60 "
# define FILE_ERR_5 "element_texture_parsing.c:63 "
# define FILE_ERR_6 "element_rgb_parsing.c:40 "
# define FILE_ERR_7 "element_rgb_parsing.c:130 "
# define FILE_ERR_8 "element_rgb_parsing.c:28 "
# define FILE_ERR_9 "element_rgb_parsing.c:46 "
# define FILE_ERR_10 "element_rgb_parsing.c:113 "

typedef struct s_parsing
{
	char	*buff;
	char	*rp_no;
	char	*rp_so;
	char	*rp_we;
	char	*rp_ea;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
}			t_parsing;

// element_collect_parsing.c
bool		prepare_collect_elements(char *cub_file, t_cub3d *cub3d, int *fd_sd,
				char **read_buff);

// element_collect_utils.c
bool		an_element_is_missing(t_parsing *parsing);
int			which_element_type(char letter, t_parsing *parsing);
int			open_sd_file_give_fd(char *file);

// element_rgb_parsing.c
bool		is_rgb_valid(int fd_sd, t_cub3d *cub3d, char first_letter,
				bool received_rgb_completed);

// element_texture_parsing.c
bool		is_texture_valid(int fd_sd, t_cub3d *cub3d, char fl, char sl);

// map_check.c
bool		map_check(t_cub3d *cub3d, int fd, t_map *map_info);

// map_collect.c
bool		map_collect(t_cub3d *cub3d, t_map *map, char *file, int fd);

// parsing_map.c
bool		get_and_check_map(char *file, t_cub3d *cub3d, int fd);

// parsing.c
int			parsing(int argc, char *argv[], t_cub3d *cub3d);

// parsing_utils.c
bool		is_file_cub_extension(char *file);
bool		init_parsing_struct(t_cub3d *cub3d);

// texture.c
bool		texture_struct_setup(t_cub3d *cub3d);

#endif