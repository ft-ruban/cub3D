/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:38:09 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 15:59:33 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "cub3D.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_parsing	t_parsing;
typedef struct s_cub3d		t_cub3d;
typedef struct s_map		t_map;

# define BUFFER_SIZE 1

# define MSG_1 "error during malloc of cub3d structure\n"
# define MSG_2 "invalid argc value, cub3D require a single arg that is the .cub\
 file.\n"
# define MSG_3 "invalid file's extension cub3d only support .cub files as arg\n"
# define MSG_4 "Error while opening file be sure the file \
exist in scene_descriptions folder\n"
# define MSG_5 "Malloc error during buff setup\n"
# define MSG_6 "a read function failed while collecting elements, it may be because of incorrect \
format or reaching EOF during element collects\n"
# define MSG_7 "Invalid content in your .cub, \
make sure it follow the expected form\n"
# define MSG_8 "The RGB value of C or/and F seem to be incorrect. OR/AND \
your file may be incorrect, (could be that there is no given values in the file\
 right after a C or a F.\nsetup your .cub in a way that F and C receive three value\
each separated by ',' between 000 and 255 a map also need to be right below \
your SO WE EA NO C and F. Check your .cub entries and retry.\n"
# define MSG_9 "Error during get_next_line, \
could be related to a failed malloc\n"
# define MSG_10 "Error during a ft_strjoin, \
probably related to a failed malloc\n"
# define MSG_11 "Error during a ft_strdup, probably related \
to a failed malloc\n"
# define MSG_12 "Invalid map\n"
# define MSG_13 "Found another player position\n"
# define MSG_14 "One of the map character or more is not valid\n"
# define MSG_15 "Map is not closed\n"
# define MSG_16 "No player position found\n"
# define MSG_17 "Malloc failure during init of parsing struct\n"
# define MSG_18 "Malloc failure during init of texture struct\n"
# define MSG_19 "Invalid content in your .cub file, \
make sure you are using NO, EA, SO, WE for the wall textures\n"
# define MSG_20 "error during malloc of our t_map structure\n"
# define MSG_21 "error during the opening of our file while collecting the map \
 datas\n"
# define MSG_22 "read failed during the collect of map size. make sure map \
 respect the right format\n"
# define MSG_23 "error during malloc of our map double array.\n"
# define MSG_24 "error while trying to copy the content of our map while \
 collection \n"
# define MSG_25 "error while reading our file during the map checking\n"
# define MSG_26 "Map check failed, make sure you are respecting \
 the right format (map seem to be cutdown or more than 1 map is present\n"
# define MSG_27 "cub3d doesn't handle multiple players, please make sure there \
is only 1 player token (N,E,S,W)"
# define MSG_28 "Invalid character detected inside of the map it only accept \
the following :\n0 for floors, 1 for walls\n(N,E,S,W) for player position + \
initial direction\nplease check the content of your file and try again."
# define MSG_29 "No player token (N,E,S,W) have been found on the map, check \
your .cub file and make sure to have one of those token on your map to start \
cub3d\n"
# define MSG_30 "The map you provided is open, it should be enclosed. Make \
sure 1(walls) close the map properly and restart the program."
# define MSG_31 "Texture structure failed during memory allocation. \n"
# define MSG_32 "MLX structure failed during memory allocation. \n"
# define MSG_33 "An error happened while trying to allocate memory for \
	the img structures of our textures."
# define MSG_34 "An error occured while trying to initialize the NORTH texture \
it may be because the path sent does not exist, or the texture file is invalid\
 or memory related issues. Make sure your texture is a .xpm and does exist.\n"
# define MSG_35 "An error occured while trying to initialize the SOUTH texture \
it may be because the path sent does not exist, or the texture file is invalid\
 or memory related issues. Make sure your texture is a .xpm and does exist.\n"
# define MSG_36 "An error occured while trying to initialize the WEST texture \
it may be because the path sent does not exist, or the texture file is invalid\
 or memory related issues. Make sure your texture is a .xpm and does exist.\n"
# define MSG_37 "An error occured while trying to initialize the EAST texture \
it may be because the path sent does not exist, or the texture file is invalid\
 or memory related issues. Make sure your texture is a .xpm and does exist.\n"
# define MSG_38 "new_line_remover failed may be because of a malloc error \
inside of the used ft_strdup."

// element_check_utils.c
bool	character_is_invalid(char c);
bool	player_update_check(bool *player);

// error.c
int		error_handler(t_cub3d *cub3d, int error_type,
			char *emplacement_error_msg, char *err_msg);
void	*error_handler_void(t_cub3d *cub3d, int error_type,
			char *emplacement_error_msg, char *err_msg);

//find_map_size_utils.c
bool	is_all_map_copied(t_cub3d *cub3d,
			size_t line_index, size_t map_height, int fd);
bool	find_map_start(t_parsing *parsing, int fd);

// free.c
int		clean_and_exit(t_cub3d *cub3d);

//free_map.c
bool	free_map_cpmap_failed(size_t line_index, t_map *map_info);
void	free_map(t_map *map_info);

// ft_atoi.c
int		ft_atoi(const char *nptr);

// ft_strdup.c
char	*ft_strdup(const char *s);

// ft_bzero.c
void	ft_bzero(void *s, size_t n);

// ft_isnum.c
int		ft_isnum(int c);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// ft_strlen.c
size_t	ft_strlen(const char *s);

// get_next_line.c
char	*get_next_line(int fd);
void	*ft_calloc(size_t element_count, size_t element_size);
char	*ft_strchr(const char *s, int c);

//get_the_map_utils.c
bool	skip_elements(t_parsing *parsing, int new_fd, t_cub3d *cub3d);
bool	parse_map_line(t_parsing *parsing, int fd, bool *in_map);
bool	find_map_first_line(char **line, int fd);

#endif