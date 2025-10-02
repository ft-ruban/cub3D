#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "set_mlx.h"

typedef struct s_player_pos
{
	float pos_x;
	float pos_y;
	float delta;
	
} t_player_pos;

//draw.c
int	    draw(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif