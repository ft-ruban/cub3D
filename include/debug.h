#ifndef DEBUG_H
# define DEBUG_H

# include "cub3D.h"
# include "parsing.h"

typedef struct s_parsing	t_parsing; //declaration anticipe
typedef struct s_map	t_map;
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1

void	print_struct_parsing(t_parsing *parsing);
void						print_map(t_map *map_info);

#endif