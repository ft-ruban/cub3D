#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "set_mlx.h"

//draw.c
int	    draw(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif