#ifndef DEBUG_H
# define DEBUG_H

# include "cub3D.h"
# include "parsing.h"

typedef struct s_settings	t_settings; //declaration anticipe

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1

void						print_struct_set(t_settings *set);
void						print_map(t_settings *set);

#endif