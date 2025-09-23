#ifndef UTILS_H
# define UTILS_H
#include <stdlib.h> //size_t

# include <fcntl.h> //GNL (TOCHECKBCS OLD)
# include <stdlib.h> //GNL (TOCHECKBCS OLD)
# include <unistd.h> //GNL (TOCHECKBCS OLD)
# include <stdio.h> //GNL
# include "cub3D.h"

//PARSING_NBR_ARGC_MSG
//PARSING_FILE_EXTENSION_MSG

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

# define MSG_1 "error during malloc of set structure\n"
# define MSG_2 "invalid argc value, cub3D require a single and only arg\n"
# define MSG_3 "invalid file's extension cub3d only support .cub files as arg\n"
# define MSG_4 "Error while opening file be sure the file exist in scene_descriptions folder\n"
# define MSG_5 "Malloc error during buff setup\n"
# define MSG_6 "a read function failed, it may be because of incorrect format or reaching EOF during element collects\n"
# define MSG_7 "Invalid content in your .cub, make sure it follow the expected form\n"
# define MSG_8 "The RGB value of C or/and F seem to be bigger than 255. each color can receive a value between 0 and 255. Check .cub entries.\n"
# define MSG_9 "Error during get_next_line, could be related to a failed malloc\n"
# define MSG_10 "Error during a ft_strjoin, probably related to a failed malloc\n"
# define MSG_11 "Error during a ft_strdup, probably related to a failed malloc\n"
# define MSG_12 "Found another map separeted by an 'end of line' character\n"
# define MSG_13 "Found another player position\n"
# define MSG_14 "One of the map character or more is not valid\n"
# define MSG_15 "Map is not closed\n"

//error.c
int 	error_handler(t_settings *set, int error_type, char *emplacement_error_msg, char *err_msg);

//free_map.c
void    free_map(char **map, int line_max);

// ft_atoi.c
int		ft_atoi(const char *nptr);

// ft_strdup.c
char	*ft_strdup(const char *s);

// ft_isnum.c
int		ft_isnum(int c);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// ft_strlen.c
size_t	ft_strlen(const char *s);

//get_next_line.c
char	*get_next_line(int fd);
void	*ft_calloc(size_t element_count, size_t element_size);
char	*ft_strchr(const char *s, int c);

# endif